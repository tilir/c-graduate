//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Draw utilities header to abstract away real drawer layer
//
//-----------------------------------------------------------------------------

#pragma once

#include <assert.h>
#include <stdbool.h>

// surface is something to draw on: from texture to screen buffer
struct Surface;

// basic drawing functions for surface
void Surface_putPixel(struct Surface *s, int x, int y, unsigned color);
void Surface_putLogPixel(struct Surface *s, double x, double y, unsigned color);
void Surface_putRect(struct Surface *s, int x, int y, int szx, int szy,
                     unsigned color);
void Surface_fillWith(struct Surface *s, unsigned color);
unsigned Surface_getWidth(struct Surface *s);
unsigned Surface_getHeight(struct Surface *s);

// viewport is something to query or poll
struct ViewPort;

// callback for poll contains surface and some data
typedef void (*CallBack)(struct Surface *s, void *data);

// possible poll result: shall we stop?
enum Pollres { POLL_PROCEED, POLL_STOP };

// special keys for bindings
enum KeySpecial { KEY_SPACE, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

// structure to express key, pressed inside viewport
struct KeyPressed {
  bool is_special;
  union {
    enum KeySpecial k;
    char s;
  } u;
};

// helper functions for function above
static inline struct KeyPressed Key_PutSpecial(enum KeySpecial k) {
  struct KeyPressed result = {true, {.k = k}};
  return result;
}
static inline struct KeyPressed Key_PutRegular(char s) {
  struct KeyPressed result = {false, {.s = s}};
  return result;
}
static inline bool Key_IsSpecial(struct KeyPressed kp) { return kp.is_special; }
static inline enum KeySpecial Key_GetSpecial(struct KeyPressed kp) {
  assert(kp.is_special);
  return kp.u.k;
}
static inline char Key_GetRegular(struct KeyPressed kp) {
  assert(!kp.is_special);
  return kp.u.s;
}

// callback for key, pressed inside viewport: data is surface state
typedef void (*KeyBindCall)(struct ViewPort *, struct KeyPressed, bool is_down,
                            void *data);

// color parts and ctor
enum { OFFSETA = 24, OFFSETR = 16, OFFSETG = 8, OFFSETB = 0 };

static inline unsigned buildcolor_argb(unsigned char a, unsigned char r,
                                       unsigned char g, unsigned char b) {
  return ((unsigned)a << OFFSETA) | ((unsigned)r << OFFSETR) |
         ((unsigned)g << OFFSETG) | ((unsigned)b << OFFSETB);
}

// color part to use
#define cpart(color, off) ((color) >> (off))

// basic support functions for viewport
struct ViewPort *createViewPort(int width, int height, CallBack callback,
                                bool resizable);
void bindViewPortKeys(struct ViewPort *v, KeyBindCall bindkeys);
void setViewPortDelay(struct ViewPort *v, int delay);
void setViewPortName(struct ViewPort *v, const char *name);
enum Pollres pollViewPort(struct ViewPort *v, void *data);
void dumpViewPort(struct ViewPort *v, const char *name, void *data);
void freeViewPort(struct ViewPort *v);