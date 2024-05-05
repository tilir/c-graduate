//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// SDL: triangle
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "errm.h"

#include <SDL2/SDL.h>

struct ViewPort {
  int width, height;
  SDL_Window *screen;
  SDL_Renderer *ren;
};

void printinfo(int num, const SDL_RendererInfo *nfo) {
  printf("\n---\n");
  printf("Number: %d\n", num);
  printf("Name: %s\n", nfo->name);
  printf("SW: %x, ACC: %x, VSYNC: %x, TEXTURE: %x\n",
         nfo->flags & SDL_RENDERER_SOFTWARE,
         nfo->flags & SDL_RENDERER_ACCELERATED,
         nfo->flags & SDL_RENDERER_PRESENTVSYNC,
         nfo->flags & SDL_RENDERER_TARGETTEXTURE);
}

void driversinfo() {
  int ndrivers = SDL_GetNumRenderDrivers();
  if (ndrivers < 0)
    ERR(SDL_GetNumRenderDrivers);

  for (int i = 0; i < ndrivers; ++i) {
    int res;
    SDL_RendererInfo nfo;
    res = SDL_GetRenderDriverInfo(i, &nfo);
    if (res < 0)
      ERR(SDL_GetRenderDriverInfo);
    printinfo(i, &nfo);
  }
}

void renderTriangle(SDL_Renderer *ren) {
  int w, h;
  SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(ren);

  SDL_GetRendererOutputSize(ren, &w, &h);
  SDL_Vertex vertex_1 = {{100, 100}, {0, 0, 0xff, 0xff}};
  SDL_Vertex vertex_2 = {{w - 100, 100}, {0xff, 0xff, 0xff, 0xff}};
  SDL_Vertex vertex_3 = {{100, h - 100}, {0xff, 0, 0, 0xff}};

  SDL_Vertex vertices[] = {vertex_1, vertex_2, vertex_3};

  SDL_RenderGeometry(ren, NULL, vertices, 3, NULL, 0);
}

int main() {
  struct ViewPort v;
  SDL_RendererInfo nfo;
  int res;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    ERR(SDL_Init, true);

  v.width = 640;
  v.height = 480;

  atexit(SDL_Quit);

  v.screen = SDL_CreateWindow("First SDL triangle", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, v.width, v.height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (!v.screen)
    ERR(SDL_CreateWindow, true);

  driversinfo();

  v.ren = SDL_CreateRenderer(
      v.screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!v.ren)
    ERR(SDL_CreateRenderer, true);

  printf("\n[Selected]\n");
  res = SDL_GetRendererInfo(v.ren, &nfo);
  if (res != 0)
    ERR(SDL_GetRendererInfo);
  else
    printinfo(-1, &nfo);

  for (;;) {
    int pending;
    SDL_Event event;
    pending = SDL_PollEvent(&event);
    if (pending && event.type == SDL_QUIT)
      break;
    renderTriangle(v.ren);
    SDL_RenderPresent(v.ren);
  }

  SDL_DestroyRenderer(v.ren);
  SDL_DestroyWindow(v.screen);
  exit(0);
}
