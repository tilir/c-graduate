//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// public drawer interface (C version)
//
//-----------------------------------------------------------------------------

#pragma once

#include <assert.h>
#include <stdbool.h>

enum pollres { PROCEED, STOP };

_Static_assert(sizeof(unsigned) == 4, "unsigned type size incorrect");

enum Offset { OFF_A = 24, OFF_R = 16, OFF_G = 8, OFF_B = 0 };

static inline unsigned buildcolor(unsigned a, unsigned r, unsigned g,
                                  unsigned b) {
  assert((a & 0xFF) == a && (r & 0xFF) == r && (g & 0xFF) == g &&
         (b & 0xFF) == b);
  return (a << OFF_A) | (r << OFF_R) | (g << OFF_G) | (b << OFF_B);
}

static inline unsigned char cpart(unsigned color, enum Offset off) {
  return (color >> off);
}

struct Surface;

void Surface_putpixel(struct Surface *s, int x, int y, unsigned c);
void Surface_putlogpixel(struct Surface *s, double x, double y, unsigned color);
void Surface_fillwith(struct Surface *s, unsigned c);
unsigned Surface_w(struct Surface *s);
unsigned Surface_h(struct Surface *s);

struct ViewPort;

// try to fit in these FPS
enum { FPS_ESTIMATED = 25 };

enum pollres ViewPort_poll(struct ViewPort *v);
void ViewPort_dump(struct ViewPort *v, const char *name);

typedef void (*callback_t)(struct Surface *, void *);

struct ViewPort *ViewPort_query(int w, int h, callback_t c, void *state,
                                bool resize);
void ViewPort_destroy(struct ViewPort *v);

static double max(double x, double y) { return (x > y) ? x : y; }

static double clamp(double v, double lo, double hi) {
  if (v < lo)
    return lo;
  if (v > hi)
    return hi;
  return v;
}

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
static inline bool Key_IsRegular(struct KeyPressed kp) {
  return !kp.is_special;
}
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

void ViewPort_bind(struct ViewPort *v, KeyBindCall bindkeys);
