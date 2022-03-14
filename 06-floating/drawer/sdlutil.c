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
#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "drawer.h"

struct Surface {
  SDL_Renderer *r;
};

void Surface_putpixel(struct Surface *s, int x, int y, unsigned c) {
  SDL_SetRenderDrawColor(s->r, cpart(c, OFF_R), cpart(c, OFF_G), cpart(c, OFF_B), cpart(c, OFF_A));
  SDL_RenderDrawPoint(s->r, x, y);
}

double clamp(double v, double lo, double hi) {
  if (v < lo) return lo;
  if (v > hi) return hi;
  return v;
}

void Surface_putlogpixel(struct Surface *s, double x, double y, unsigned color) {
  int width, height;
  SDL_GetRendererOutputSize(s->r, &width, &height);
  double w = width, h = height;

  int logx = clamp(rint((x + 1.0) * width / 2.0), 0.0, w);
  int logy = clamp(rint((y + 1.0) * height / 2.0), 0.0, h);
  Surface_putpixel(s, logx, logy, color);
}

void Surface_fillwith(struct Surface *s, unsigned c) {
  SDL_SetRenderDrawColor(s->r, cpart(c, OFF_R), cpart(c, OFF_G), cpart(c, OFF_B), cpart(c, OFF_A));
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
  void *data;
};

enum pollres ViewPort_poll(struct ViewPort *v) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      return STOP;
  }
  struct Surface s = {v->ren};
  v->callback(&s, v->data);
  SDL_RenderPresent(v->ren);
  return PROCEED;
}

void ViewPort_dump(struct ViewPort *v, const char *name){
  SDL_SetRenderTarget(v->ren, v->texture);
  struct Surface s = {v->ren};
  v->callback(&s, v->data);
  SDL_QueryTexture(v->texture, NULL, NULL, &v->width, &v->height);
  SDL_Surface *surface = SDL_CreateRGBSurface(0, v->width, v->height, 32, 0, 0, 0, 0);
  SDL_RenderReadPixels(v->ren, NULL, surface->format->format, surface->pixels,
                       surface->pitch);
  SDL_SaveBMP(surface, name);
  SDL_FreeSurface(surface);
  SDL_SetRenderTarget(v->ren, NULL);
}

struct ViewPort *vg = NULL;

struct ViewPort *ViewPort_query(int w, int h, callback_t c, void *data, bool resize) {
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

  atexit(SDL_Quit);
  vg->screen = SDL_CreateWindow("SDL window", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, w, h,
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

void ViewPort_destroy(struct ViewPort *v) {
  assert(v == vg);
  SDL_DestroyTexture(v->texture);
  SDL_DestroyRenderer(v->ren);
  SDL_DestroyWindow(v->screen);
  free(vg);
  vg = NULL;
}
