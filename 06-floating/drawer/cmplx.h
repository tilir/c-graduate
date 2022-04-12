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

static inline double cmplx_absq(struct cmplx x) {
  return x.re * x.re + x.im * x.im;
}

static inline double cmplx_abs(struct cmplx x) {
  return sqrt(cmplx_absq(x));
}

static inline struct cmplx cmplxv(double re, double im) {
  struct cmplx c = {re, im};
  return c;
}

static inline struct cmplx cmplx_add(struct cmplx x, struct cmplx y) {
  struct cmplx res = {x.re + y.re, x.im + y.im};
  return res;
}

static inline struct cmplx cmplx_sub(struct cmplx x, struct cmplx y) {
  struct cmplx res = {x.re - y.re, x.im - y.im};
  return res;
}

static inline struct cmplx cmplx_mul(struct cmplx x, struct cmplx y) {
  struct cmplx res = {x.re * y.re - x.im * y.im, x.re * y.im + x.im * y.re};
  return res;
}

static inline struct cmplx cmplx_div(struct cmplx x, struct cmplx y) {
  struct cmplx res = {x.re * y.re + x.im * y.im, x.im * y.re - x.re * y.im};
  double d = cmplx_absq(y);
  res.re /= d;
  res.im /= d;
  return res;
}

static inline struct cmplx cmplx_sqr(struct cmplx x) {
  return cmplx_mul(x, x);
}

static inline struct cmplx cmplx_cube(struct cmplx x) {
  return cmplx_mul(cmplx_sqr(x), x);
}