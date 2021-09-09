//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Platformer: simple physical model with red square
//
// inspired by: https://www.youtube.com/watch?v=yFLa3ln16w0
// cl platformer.c sdlutil.c /link SDL2main.lib SDL2.lib
//
//-----------------------------------------------------------------------------

#include "drawutil.h"
#include <stdbool.h>

#define WIDTH 640
#define HEIGHT 480
#define SIZE 200
#define SPEED 600
#define GRAVITY 60
#define FPS 60
#define JUMP -1200

struct Coord {
  int x, y;
};

struct LogState {
  bool jump_pressed, can_jump, left_pressed, right_pressed;
};

struct ProgramData {
  struct Coord c;
  struct Coord v;
  struct LogState ls;
  int size;
};

void keybind(struct ViewPort *vp, struct KeyPressed kp, bool is_down,
             void *data) {
  struct ProgramData *pdata = (struct ProgramData *)data;
  if (Key_IsSpecial(kp)) {
    switch (Key_GetSpecial(kp)) {
    case KEY_SPACE:
      pdata->ls.jump_pressed = is_down;
      break;
    case KEY_LEFT:
      pdata->ls.left_pressed = is_down;
      break;
    case KEY_RIGHT:
      pdata->ls.right_pressed = is_down;
      break;
    }
  }
}

static inline int clamp(int v, int lo, int hi) {
  if (v < lo)
    return lo;
  if (v > hi)
    return hi;
  return v;
}

void callback(struct Surface *s, void *data) {
  unsigned ColorBlack = buildcolor_argb(255, 0, 0, 0);
  unsigned ColorRed = buildcolor_argb(255, 255, 0, 0);

  // unpack
  struct ProgramData *pdata = (struct ProgramData *)data;
  int x = pdata->c.x, y = pdata->c.y, vx = pdata->v.x, vy = pdata->v.y,
      szx = pdata->size, szy = pdata->size;

  // logic
  vx = (pdata->ls.right_pressed - pdata->ls.left_pressed) * SPEED;
  vy += GRAVITY;
  if (pdata->ls.jump_pressed && pdata->ls.can_jump) {
    pdata->ls.can_jump = false;
    vy = JUMP;
  }
  x += vx / FPS;
  y += vy / FPS;
  x = clamp(x, 0, WIDTH - szx);
  if (y >= HEIGHT - szy) {
    vy = 0;
    if (!pdata->ls.jump_pressed)
      pdata->ls.can_jump = true;
  }
  y = clamp(y, 0, HEIGHT - szy);

  // store back
  pdata->c.x = x;
  pdata->c.y = y;
  pdata->v.x = vx;
  pdata->v.y = vy;

  Surface_fillWith(s, ColorBlack);
  Surface_putRect(s, x, y, szx, szy, ColorRed);
}

#if defined(_WIN32) || defined(WIN32)
int WinMain() {
#else
int main() {
#endif
  struct ViewPort *vp = createViewPort(WIDTH, HEIGHT, callback, false);
  struct Coord coord = {(WIDTH - SIZE) / 2, (HEIGHT - SIZE) / 2};
  struct Coord velocities = {0, 0};
  struct LogState ls = {false, true, false, false};
  struct ProgramData data = {coord, velocities, ls, SIZE};
  bindViewPortKeys(vp, keybind);
  setViewPortDelay(vp, 1000 / FPS); // 1000ms is 1 second

  while (pollViewPort(vp, &data) == POLL_PROCEED) {
  }

  freeViewPort(vp);
}
