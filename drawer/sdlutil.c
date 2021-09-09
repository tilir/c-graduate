//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Concrete drawing layer (drawutil.h implementation) based on SDL2
//
//-----------------------------------------------------------------------------

#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>

#include "drawutil.h"

struct Surface {
  SDL_Renderer *ren;
};

void Surface_putPixel(struct Surface *s, int x, int y, unsigned c) {
  assert(s);
  SDL_SetRenderDrawColor(s->ren, cpart(c, OFFSETR), cpart(c, OFFSETG),
                         cpart(c, OFFSETB), cpart(c, OFFSETA));
  SDL_RenderDrawPoint(s->ren, x, y);
}

static inline double clamp(double v, double lo, double hi) {
  if (v < lo)
    return lo;
  if (v > hi)
    return hi;
  return v;
}

void Surface_putLogPixel(struct Surface *s, double x, double y,
                         unsigned color) {
  int width, height;
  SDL_GetRendererOutputSize(s->ren, &width, &height);
  double w = width, h = height;

  int logx = clamp(rint((x + 1.0) * width / 2.0), 0.0, w);
  int logy = clamp(rint((y + 1.0) * height / 2.0), 0.0, h);
  Surface_putPixel(s, logx, logy, color);
}

void Surface_putRect(struct Surface *s, int x, int y, int szx, int szy,
                     unsigned c) {
  SDL_Rect Rect = {x, y, szx, szy};
  assert(s);
  SDL_SetRenderDrawColor(s->ren, cpart(c, OFFSETR), cpart(c, OFFSETG),
                         cpart(c, OFFSETB), cpart(c, OFFSETA));
  SDL_RenderFillRect(s->ren, &Rect);
}

void Surface_fillWith(struct Surface *s, unsigned c) {
  assert(s);
  SDL_SetRenderDrawColor(s->ren, cpart(c, OFFSETR), cpart(c, OFFSETG),
                         cpart(c, OFFSETB), cpart(c, OFFSETA));
  SDL_RenderClear(s->ren);
}

unsigned Surface_getWidth(struct Surface *s) {
  int w;
  assert(s);
  SDL_GetRendererOutputSize(s->ren, &w, NULL);
  return w;
}

unsigned Surface_getHeight(struct Surface *s) {
  int h;
  assert(s);
  SDL_GetRendererOutputSize(s->ren, NULL, &h);
  return h;
}

struct ViewPort {
  int width, height, delay;
  SDL_Window *screen;
  SDL_Renderer *ren;
  CallBack callback;
  KeyBindCall keybind;
};

static struct ViewPort *vglobal = NULL;

struct ViewPort *createViewPort(int width, int height, CallBack callback,
                                bool resizable) {
  if (vglobal != NULL)
    return vglobal;

  vglobal = malloc(sizeof(struct ViewPort));
  assert(vglobal);

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    abort();
  }

  vglobal->screen = SDL_CreateWindow(
      "SDL window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
      height, SDL_WINDOW_SHOWN | (resizable ? SDL_WINDOW_RESIZABLE : 0));

  if (!vglobal->screen) {
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    abort();
  }

  vglobal->ren =
      SDL_CreateRenderer(vglobal->screen, -1, SDL_RENDERER_ACCELERATED);
  if (!vglobal->ren) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(vglobal->screen);
    SDL_Quit();
    abort();
  }

  vglobal->callback = callback;
  vglobal->keybind = NULL;
  vglobal->width = width;
  vglobal->height = height;
  vglobal->delay = 0;

  return vglobal;
}

void setViewPortDelay(struct ViewPort *v, int delay) {
  assert(v);
  v->delay = delay;
}

void bindViewPortKeys(struct ViewPort *v, KeyBindCall bindkeys) {
  assert(v);
  v->keybind = bindkeys;
}

void setViewPortName(struct ViewPort *v, const char *name) {
  SDL_SetWindowTitle(v->screen, name);
}

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

enum Pollres pollViewPort(struct ViewPort *v, void *data) {
  SDL_Event event;
  assert(v);
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      return POLL_STOP;
    if (v->keybind && (event.type == SDL_KEYDOWN))
      callKeyBind(v, event.key.keysym.sym, true, data);
    if (v->keybind && (event.type == SDL_KEYUP))
      callKeyBind(v, event.key.keysym.sym, false, data);
  }
  struct Surface s = {v->ren};
  v->callback(&s, data);
  SDL_RenderPresent(v->ren);
  if (v->delay > 0)
    SDL_Delay(v->delay);
  return POLL_PROCEED;
}

void dumpViewPort(struct ViewPort *v, const char *name, void *data) {
  SDL_Texture *texture =
      SDL_CreateTexture(v->ren, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, v->width, v->height);
  SDL_SetRenderTarget(v->ren, texture);
  struct Surface s = {v->ren};
  v->callback(&s, data);
  SDL_QueryTexture(texture, NULL, NULL, &v->width, &v->height);
  SDL_Surface *surface =
      SDL_CreateRGBSurface(0, v->width, v->height, 32, 0, 0, 0, 0);
  SDL_RenderReadPixels(v->ren, NULL, surface->format->format, surface->pixels,
                       surface->pitch);
  SDL_SaveBMP(surface, name);
  SDL_FreeSurface(surface);
  SDL_SetRenderTarget(v->ren, NULL);
  SDL_DestroyTexture(texture);
}

void freeViewPort(struct ViewPort *v) {
  if (!vglobal || !v)
    return;
  SDL_DestroyRenderer(v->ren);
  SDL_DestroyWindow(v->screen);
  free(v);
  vglobal = NULL;
  SDL_Quit();
}
