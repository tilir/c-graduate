//------------------------------------------------------------------------------
//
// C implementation for SDL-based drawer
//
//------------------------------------------------------------------------------

#include <math.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "drawer.h"

struct surface_t {
  SDL_Renderer *renderer_;
};

unsigned surface_width(const struct surface_t *s) {
  int w;
  SDL_GetRendererOutputSize(s->renderer_, &w, NULL);
  return w;
}

unsigned surface_height(const struct surface_t *s) {
  int h;
  SDL_GetRendererOutputSize(s->renderer_, NULL, &h);
  return h;
}

void surface_putpixel(const struct surface_t *s, int x, int y, unsigned c) {
  SDL_SetRenderDrawColor(s->renderer_, cpart(ROFF, c), cpart(GOFF, c), cpart(BOFF, c), cpart(AOFF, c));
  SDL_RenderDrawPoint(s->renderer_, x, y);
}

// in C++ we do have std::clamp but not in C for some reason
static double clamp(double x, double lo, double hi) {
  assert(lo < hi);
  if (x < lo) return lo;
  if (x > hi) return hi;
  return x;
}

void surface_putlogpixel(const struct surface_t *s, double x, double y, unsigned color) {
  int width, height;
  SDL_GetRendererOutputSize(s->renderer_, &width, &height);
  double w = width, h = height;

  int logx = clamp(rint((x + 1.0) * width / 2.0), 0.0, w);
  int logy = clamp(rint((y + 1.0) * height / 2.0), 0.0, h);
  surface_putpixel(s, logx, logy, color);
}

void surface_fillwith(const struct surface_t *s, unsigned c) {
  SDL_SetRenderDrawColor(s->renderer_, cpart(ROFF, c), cpart(GOFF, c), cpart(BOFF, c), cpart(AOFF, c));
  SDL_RenderClear(s->renderer_);    
}

struct viewport_t {
  int width, height;
  SDL_Window *screen;
  SDL_Renderer *ren;
  SDL_Texture *texture;
  vp_surf_cb_t callback;
  void *cbdata;
  vp_key_cb_t keybind;
  void *keydata;
};

enum pollres viewport_poll(struct viewport_t *v) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      return STOP;
    if (v->keybind && (event.type == SDL_KEYDOWN)) {      
      SDL_Keycode kc = event.key.keysym.sym;
      switch(kc) {
        case SDLK_UP:
          v->keybind(key_special(KEY_UP), v->keydata);
          break;
        case SDLK_DOWN:
          v->keybind(key_special(KEY_DOWN), v->keydata);
          break;
        case SDLK_LEFT:
          v->keybind(key_special(KEY_LEFT), v->keydata);
          break;
        case SDLK_RIGHT:
          v->keybind(key_special(KEY_RIGHT), v->keydata);
          break;
        case SDLK_p:
          v->keybind(key_regular('p'), v->keydata);
          break;
        case SDLK_d:
          v->keybind(key_regular('d'), v->keydata);
          break;
        case SDLK_r:
          v->keybind(key_regular('r'), v->keydata);
          break;
        case SDLK_s:
          v->keybind(key_regular('s'), v->keydata);
          break;
        case SDLK_PLUS:
        case SDLK_KP_PLUS:
          v->keybind(key_regular('+'), v->keydata);
          break;
        case SDLK_MINUS:
        case SDLK_KP_MINUS:
          v->keybind(key_regular('-'), v->keydata);
          break;
      }
    }
  }

  struct surface_t s = { v->ren };
  v->callback(&s, v->cbdata);
  SDL_RenderPresent(v->ren);
  return PROCEED;
}

void dump(struct viewport_t *v, const char *name) {
  SDL_SetRenderTarget(v->ren, v->texture);
  struct surface_t s = { v->ren };
  v->callback(&s, v->cbdata);
  SDL_QueryTexture(v->texture, NULL, NULL, &v->width, &v->height);
  SDL_Surface *surface = SDL_CreateRGBSurface(0, v->width, v->height, 32, 0, 0, 0, 0);
  SDL_RenderReadPixels(v->ren, NULL, surface->format->format, surface->pixels,
                       surface->pitch);
  SDL_SaveBMP(surface, name);
  SDL_FreeSurface(surface);
  SDL_SetRenderTarget(v->ren, NULL);
}

void bindkeys(struct viewport_t *v, vp_key_cb_t k, void *data) {
  v->keybind = k;
  v->keydata = data;
}

struct viewport_t *v = NULL;

struct viewport_t *query_viewport(int w, int h, vp_surf_cb_t c, void *data) {
  int res;
  bool r = true; // resizable
  
  if (v != NULL) return v;

  res = SDL_Init(SDL_INIT_VIDEO);
  if(res != 0) {
    fprintf(stderr, "%s\n", SDL_GetError());
    abort();
  }
  atexit(SDL_Quit);
 
  v = calloc(1, sizeof(struct viewport_t));
  assert(v);
  v->width = w;
  v->height = h;
  v->callback = c;
  v->cbdata = data; 
  v->screen = SDL_CreateWindow("SDL window", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, w, h,
    SDL_WINDOW_SHOWN | (r ? SDL_WINDOW_RESIZABLE : 0));
  if(!v->screen) {
    fprintf(stderr, "%s\n", SDL_GetError());
    abort();
  }

  v->ren = SDL_CreateRenderer(v->screen, -1, SDL_RENDERER_ACCELERATED);
  if(!v->ren) {
    fprintf(stderr, "%s\n", SDL_GetError());
    abort();
  }

  v->texture = SDL_CreateTexture(v->ren, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET, v->width, v->height);
  
  return v;
}

void free_viewport() {
  free(v);
  v = NULL;
}

