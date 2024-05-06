//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// SDL implementation (C version)
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "drawer.h"

struct Surface {
  SDL_Renderer *r;
};

void Surface_putpixel(struct Surface *s, int x, int y, unsigned c) {
  SDL_SetRenderDrawColor(s->r, cpart(c, OFF_R), cpart(c, OFF_G),
                         cpart(c, OFF_B), cpart(c, OFF_A));
  SDL_RenderDrawPoint(s->r, x, y);
}

void Surface_putlogpixel(struct Surface *s, double x, double y,
                         unsigned color) {
  int width, height;
  SDL_GetRendererOutputSize(s->r, &width, &height);
  double w = width, h = height;

  int logx = clamp(rint((x + 1.0) * width / 2.0), 0.0, w);
  int logy = clamp(rint((y + 1.0) * height / 2.0), 0.0, h);
  Surface_putpixel(s, logx, logy, color);
}

void Surface_fillwith(struct Surface *s, unsigned c) {
  SDL_SetRenderDrawColor(s->r, cpart(c, OFF_R), cpart(c, OFF_G),
                         cpart(c, OFF_B), cpart(c, OFF_A));
  SDL_RenderClear(s->r);
}

unsigned Surface_w(struct Surface *s) {
  int w;
  SDL_GetRendererOutputSize(s->r, &w, NULL);
  return w;
}

unsigned Surface_h(struct Surface *s) {
  int h;
  SDL_GetRendererOutputSize(s->r, NULL, &h);
  return h;
}

struct ViewPort {
  int width, height;
  SDL_Window *screen;
  SDL_Renderer *ren;
  SDL_Texture *texture;
  callback_t callback;
  KeyBindCall keybind;
  void *data;
};

const int MSEC_IN_SEC = 1000;

static void callKeyBind(struct ViewPort *v, SDL_Keycode kc, bool is_down,
                        void *data) {
  assert(v);
  switch (kc) {
  case SDLK_SPACE:
    v->keybind(v, Key_PutSpecial(KEY_SPACE), is_down, data);
    break;
  case SDLK_UP:
    v->keybind(v, Key_PutSpecial(KEY_UP), is_down, data);
    break;
  case SDLK_DOWN:
    v->keybind(v, Key_PutSpecial(KEY_DOWN), is_down, data);
    break;
  case SDLK_LEFT:
    v->keybind(v, Key_PutSpecial(KEY_LEFT), is_down, data);
    break;
  case SDLK_RIGHT:
    v->keybind(v, Key_PutSpecial(KEY_RIGHT), is_down, data);
    break;
  case SDLK_p:
    v->keybind(v, Key_PutRegular('p'), is_down, data);
    break;
  case SDLK_d:
    v->keybind(v, Key_PutRegular('d'), is_down, data);
    break;
  case SDLK_r:
    v->keybind(v, Key_PutRegular('r'), is_down, data);
    break;
  case SDLK_s:
    v->keybind(v, Key_PutRegular('s'), is_down, data);
    break;
  case SDLK_PLUS:
  case SDLK_KP_PLUS:
    v->keybind(v, Key_PutRegular('+'), is_down, data);
    break;
  case SDLK_MINUS:
  case SDLK_KP_MINUS:
    v->keybind(v, Key_PutRegular('-'), is_down, data);
    break;
  }
}

enum pollres ViewPort_poll(struct ViewPort *v) {
  SDL_Event event;
  Uint32 start, elapsed, estimated = MSEC_IN_SEC / FPS_ESTIMATED;
  start = SDL_GetTicks();

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      return STOP;
    if (v->keybind && (event.type == SDL_KEYDOWN))
      callKeyBind(v, event.key.keysym.sym, true, v->data);
    if (v->keybind && (event.type == SDL_KEYUP))
      callKeyBind(v, event.key.keysym.sym, false, v->data);
  }
  struct Surface s = {v->ren};
  v->callback(&s, v->data);
  SDL_RenderPresent(v->ren);

  elapsed = SDL_GetTicks() - start;
  if (elapsed < estimated)
    SDL_Delay(estimated - elapsed);
  return PROCEED;
}

void ViewPort_dump(struct ViewPort *v, const char *name) {
  SDL_SetRenderTarget(v->ren, v->texture);
  struct Surface s = {v->ren};
  v->callback(&s, v->data);
  SDL_QueryTexture(v->texture, NULL, NULL, &v->width, &v->height);
  SDL_Surface *surface =
      SDL_CreateRGBSurface(0, v->width, v->height, 32, 0, 0, 0, 0);
  SDL_RenderReadPixels(v->ren, NULL, surface->format->format, surface->pixels,
                       surface->pitch);
  SDL_SaveBMP(surface, name);
  SDL_FreeSurface(surface);
  SDL_SetRenderTarget(v->ren, NULL);
}

struct ViewPort *vg = NULL;

struct ViewPort *ViewPort_query(int w, int h, callback_t c, void *data,
                                bool resize) {
  if (vg)
    return vg;
  vg = calloc(1, sizeof(struct ViewPort));

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "sdl init error: %s\n", SDL_GetError());
    abort();
  }

  vg->width = w;
  vg->height = h;
  vg->callback = c;
  vg->data = data;
  vg->keybind = NULL;

  atexit(SDL_Quit);
  vg->screen = SDL_CreateWindow(
      "SDL window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h,
      SDL_WINDOW_SHOWN | (resize ? SDL_WINDOW_RESIZABLE : 0));
  if (!vg->screen) {
    fprintf(stderr, "create window error: %s\n", SDL_GetError());
    abort();
  }

  vg->ren = SDL_CreateRenderer(vg->screen, -1, SDL_RENDERER_ACCELERATED);
  if (!vg->ren) {
    fprintf(stderr, "create renderer error: %s\n", SDL_GetError());
    abort();
  }

  vg->texture = SDL_CreateTexture(vg->ren, SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_TARGET, w, h);

  return vg;
}

void ViewPort_bind(struct ViewPort *v, KeyBindCall bindkeys) {
  assert(v);
  v->keybind = bindkeys;
}

void ViewPort_destroy(struct ViewPort *v) {
  assert(v == vg);
  SDL_DestroyTexture(v->texture);
  SDL_DestroyRenderer(v->ren);
  SDL_DestroyWindow(v->screen);
  free(vg);
  vg = NULL;
}
