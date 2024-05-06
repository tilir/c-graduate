//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// SDL: texture and some animation
// gcc -O2 sdl_keydown.c -lSDL2 -lSDL2_image
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "errm.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct ViewPort {
  int width, height;
  SDL_Window *screen;
  SDL_Renderer *ren;
};

const int swidth = 256;
const int height = 256;
const int estfps = 50;
const int msec_in_sec = 1000;

static double clamp(double v, double lo, double hi) {
  if (v < lo)
    return lo;
  if (v > hi)
    return hi;
  return v;
}

static SDL_Point to_physical(SDL_Renderer *r, double x, double y) {
  int width, height;
  SDL_Point p;
  SDL_GetRendererOutputSize(r, &width, &height);
  double w = width, h = height;
  p.x = clamp(rint((x + 1.0) * w / 2.0), 0.0, w);
  p.y = clamp(rint((-y + 1.0) * h / 2.0), 0.0, h);
  return p;
}

void renderTexture(SDL_Renderer *ren, SDL_Texture *tex, double x, double y) {
  SDL_Point pos = to_physical(ren, x, y);
  SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(ren);
  SDL_Rect dst = {pos.x - swidth / 2, pos.y - height / 2, swidth, height};
  SDL_RenderCopy(ren, tex, NULL, &dst);
}

int main() {
  struct ViewPort v;
  SDL_RendererInfo nfo;
  int res;
  float xpos = 0.0;
  const float ground_level = -0.5;
  float ypos = ground_level;
  float speed = 0.0;
  float gameg = 0.5;
  const float start_speed = 0.9;
  SDL_Texture *tex = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    ERR(SDL_Init, true);

  v.width = 640;
  v.height = 480;

  atexit(SDL_Quit);

  v.screen = SDL_CreateWindow("First SDL texture", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, v.width, v.height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (!v.screen)
    ERR(SDL_CreateWindow, true);

  v.ren = SDL_CreateRenderer(
      v.screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!v.ren)
    ERR(SDL_CreateRenderer, true);

  tex = IMG_LoadTexture(v.ren, "mult-dragon.png");
  if (tex == NULL)
    ERR(IMG_LoadTexture, true);

  for (;;) {
    SDL_Event event;
    Uint32 start, elapsed, estimated = msec_in_sec / estfps;
    start = SDL_GetTicks();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        goto cleanup;
      if (event.type == SDL_KEYDOWN) {
        SDL_Keycode kc = event.key.keysym.sym;
        if (kc == SDLK_UP && ypos <= ground_level + 0.1)
          speed = start_speed;
      }
    }
    ypos += speed / estfps;
    speed -= gameg / estfps;
    if (ypos < ground_level)
      speed = 0;
    renderTexture(v.ren, tex, xpos, ypos);
    SDL_RenderPresent(v.ren);
    elapsed = SDL_GetTicks() - start;
    if (elapsed < estimated)
      SDL_Delay(estimated - elapsed);
  }

cleanup:
  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(v.ren);
  SDL_DestroyWindow(v.screen);
  exit(0);
}
