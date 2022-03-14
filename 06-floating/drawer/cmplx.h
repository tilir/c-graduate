//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// hack around MSVC's poor support of C complex numbers
//
//-----------------------------------------------------------------------------

#pragma once

struct cmplx {
  double re, im;
};

static inline struct cmplx cmplx_add(struct cmplx x, struct cmplx y) {
  struct cmplx res = {x.re + y.re, x.im + y.im};
  return res;
}

static inline struct cmplx cmplx_mul(struct cmplx x, struct cmplx y) {
  struct cmplx res = {x.re * y.re - x.im * y.im, x.re * y.im + x.im * y.re};
  return res;
}
