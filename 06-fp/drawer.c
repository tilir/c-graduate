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

void surface_putpixel(const struct surface_t *s, int x, int y,) {
  SDL_SetRenderDrawColor(s->renderer_, cpart(ROFF, c), cpart(GOFF, c), cpart(BOFF, c), cpart(AOFF, c));
  SDL_RenderDrawPoint(s->renderer_, x, y);
}

void surface_putlogpixel(const struct surface_t *s, double x, double y, unsigned color) {
}

void surface_fillwith(const struct surface_t *s, unsigned color) {
  SDL_SetRenderDrawColor(s->renderer_, cpart(ROFF, c), cpart(GOFF, c), cpart(BOFF, c), cpart(AOFF, c));
  SDL_RenderClear(s->renderer_);    
}


