//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Carpets collection: from simplest to interesting ones
// see also TAOCP 7.1.3 excercise 18 and more
//
//-----------------------------------------------------------------------------

#pragma once

#include <stdio.h>

typedef unsigned (*ftype_t)(unsigned, unsigned);

struct carpet_t {
  ftype_t func;
  const char *name;
};

static inline unsigned and_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = x & y;
  return res;
}

static inline unsigned or_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = x | y;
  return res;
}

static inline unsigned xor_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = x ^ y;
  return res;
}

static inline unsigned plus_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = x + y;
  return res;
}

static inline unsigned mul_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = x * y;
  return res;
}

static inline unsigned and_square_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = ((x & y) * (x & y));
  return res;
}

static inline unsigned or_square_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = ((x | y) * (x | y));
  return res;
}

static inline unsigned xor_square_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = ((x ^ y) * (x ^ y));
  return res;
}

static inline unsigned and_or_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = ((x & y) * (x | y));
  return res;
}

static inline unsigned and_xor_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = ((x & y) * (x ^ y));
  return res;
}

static inline unsigned or_xor_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = ((x ^ y) * (x | y));
  return res;
}

static inline unsigned isqr(unsigned t) { return t * t; }

static inline unsigned knuth_carpet(unsigned x, unsigned y) {
  unsigned res;
  res = isqr((x ^ ~y) & ((x - 350u) >> 3u));
  return res;
}

#define REGCARPET(c)                                                           \
  { c, #c }
