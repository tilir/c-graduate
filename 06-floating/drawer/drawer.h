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

static inline unsigned
buildcolor(unsigned a, unsigned r, unsigned g, unsigned b) {
  assert((a & 0xFF) == a && (r & 0xFF) == r && (g & 0xFF) == g && (b & 0xFF) == b);
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

enum pollres ViewPort_poll(struct ViewPort *v);
void ViewPort_dump(struct ViewPort *v, const char *name);

typedef void (*callback_t)(struct Surface *, void *);

struct ViewPort *ViewPort_query(int w, int h, callback_t c, void *state, bool resize);

double clamp(double v, double lo, double hi);