//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// funcbitmap: different bit carpets (patterns described in carpets.h)
//             see also TAOCP 7.1.3 fig. 11
//
// cl funcbitmap.c sdlutil.c /link SDL2main.lib SDL2.lib
//
//-----------------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>

#include "carpets.h"
#include "drawutil.h"

#if defined(_WIN32) || defined(WIN32)
#define ProperMain WinMain
#else
#define ProperMain main
#endif

struct carpet_t all_carpets[] = {
    REGCARPET(and_carpet),       REGCARPET(or_carpet),
    REGCARPET(xor_carpet),       REGCARPET(plus_carpet),
    REGCARPET(mul_carpet),       REGCARPET(and_square_carpet),
    REGCARPET(or_square_carpet), REGCARPET(xor_square_carpet),
    REGCARPET(and_or_carpet),    REGCARPET(and_xor_carpet),
    REGCARPET(or_xor_carpet),    REGCARPET(knuth_carpet)};

#define all_carpets_sz (sizeof(all_carpets) / sizeof(struct carpet_t))

static inline const char *get_title(struct carpet_t *carpets, int fn,
                                    int delta) {
  static char name[64];
  sprintf(name, "%s, bit: %d", carpets[fn].name, delta);
  return name;
}

struct program_state_t {
  struct carpet_t *carpets;
  unsigned maxcarpets;
  unsigned fno;
  unsigned delta;
};

void callback(struct Surface *s, void *data) {
  unsigned width = Surface_getWidth(s);
  unsigned height = Surface_getHeight(s);
  struct program_state_t *pdata = (struct program_state_t *)data;
  struct carpet_t *carpets = pdata->carpets;

  unsigned ColorWhite = buildcolor_argb(0xff, 0xff, 0xff, 0xff);
  unsigned ColorBlue = buildcolor_argb(0xff, 0x10, 0x10, 0xff);

  Surface_fillWith(s, ColorWhite);

  for (unsigned ix = 0; ix != width; ++ix)
    for (unsigned iy = 0; iy != height; ++iy) {
      unsigned res = carpets[pdata->fno].func(iy, ix);
      bool pixel = ((res >> pdata->delta) & 1);
      if (pixel)
        Surface_putPixel(s, ix, iy, ColorBlue);
    }
}

void keybind(struct ViewPort *v, struct KeyPressed kp, bool is_down,
             void *data) {
  struct program_state_t *pdata = (struct program_state_t *)data;
  int fno = pdata->fno;
  int delta = pdata->delta;
  struct carpet_t *carpets = pdata->carpets;
  unsigned maxcarpets = pdata->maxcarpets;
  assert(fno < maxcarpets);

  if (Key_IsSpecial(kp) && is_down) {
    switch (Key_GetSpecial(kp)) {
    case KEY_UP:
      if (delta < 32)
        delta += 1;
      break;
    case KEY_DOWN:
      if (delta > 0)
        delta -= 1;
      break;
    case KEY_LEFT:
      if (fno > 0)
        fno -= 1;
      break;
    case KEY_RIGHT:
      if (fno < maxcarpets - 1)
        fno += 1;
      break;
    case KEY_SPACE: {
      char name[64];
      sprintf(name, "funcmap.%s.%d.bmp", carpets[fno].name, delta);
      dumpViewPort(v, name, data);
      break;
    }
    }
  }
  setViewPortName(v, get_title(carpets, fno, delta));
  pdata->fno = fno;
  pdata->delta = delta;
}

#define WIDTH 1024
#define HEIGHT 768
#define DELTA 0
#define FUNCNO 0

int ProperMain() {
  struct ViewPort *vp = createViewPort(WIDTH, HEIGHT, callback, false);
  bindViewPortKeys(vp, keybind);
  struct program_state_t pstate = {all_carpets, all_carpets_sz, FUNCNO, DELTA};
  setViewPortName(vp, get_title(all_carpets, FUNCNO, DELTA));

  while (pollViewPort(vp, &pstate) == POLL_PROCEED) {
  }

  freeViewPort(vp);
}
