//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// SDL: texture
// gcc -O2 sdl_texture.c -lSDL2 -lSDL2_image
// cl /O2 /std:c11 sdl_texture.c /link SDL2.lib SDL2_image.lib
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "errm.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

struct ViewPort {
  int width, height;
  SDL_Window *screen;
  SDL_Renderer *ren;
};

void renderTexture(SDL_Renderer *ren, SDL_Texture *tex) {
  SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(ren);
  SDL_Rect dst = {100, 100, 256, 256};
  SDL_RenderCopy(ren, tex, NULL, &dst);
}

#if defined(_WIN32) || defined(WIN32)
int WinMain(HINSTANCE h, HINSTANCE g, LPSTR s, int n) {
#else
int main() {
#endif
  struct ViewPort v;
  SDL_RendererInfo nfo;
  int res;
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

  tex = IMG_LoadTexture(v.ren, "dragon.png");
  if (tex == NULL)
    ERR(IMG_LoadTexture, true);

  for (;;) {
    SDL_Event event;
    Uint32 start, elapsed, estimated = 1000 / 50; // estimated 50 fps
    start = SDL_GetTicks();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        goto cleanup;
    }
    renderTexture(v.ren, tex);
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
