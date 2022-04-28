//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// SIMD header (assumed Intel intrinsics)
//
// see also: intel.com/content/www/us/en/docs/intrinsics-guide/index.html
//
//-----------------------------------------------------------------------------

#pragma once

#include <assert.h>
#include <immintrin.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef __mmask8 m8;
typedef __mmask16 m16;
typedef __mmask32 m32;
typedef __mmask64 m64;

typedef __m128i ri128;
typedef __m128 rf128;
typedef __m128d rd128;
typedef __m256i ri256;
typedef __m256 rf256;
typedef __m256d rd256;
typedef __m512i ri512;
typedef __m512 rf512;
typedef __m512d rd512;

// code will not work on specific architectures
_Static_assert(CHAR_BIT == 8, "Only 8-bit bytes allowed");
_Static_assert(sizeof(int) == 4, "Only 4-byte ints allowed");

// special constants
// note: 0xFF excessive for m8 if we are using ints, 
//       since there are only 4 ints in m128 so 0xF will do. 
//       But we want to account for general case.
enum {
  M8_ALLONES = 0xFFu,
  M16_ALLONES = 0xFFFFu,
  M32_ALLONES = 0xFFFFFFFFu,
  M64_ALLONES = 0xFFFFFFFFFFFFFFFFu,
};

// dumps to stdout
#define DUMP_XREG(R) print_xreg(stdout, #R, R)
#define DUMP_YREG(R) print_yreg(stdout, #R, R)
#define DUMP_ZREG(R) print_zreg(stdout, #R, R)

// dump functions
static inline void print_xreg(FILE *f, const char *const pname, ri128 r);
static inline void print_yreg(FILE *f, const char *const pname, ri256 r);
static inline void print_zreg(FILE *f, const char *const pname, ri512 r);

// sets single value to all register lanes
static inline ri128 set_xvalue(int i) { return _mm_set1_epi32(i); }
static inline ri256 set_yvalue(int i) { return _mm256_set1_epi32(i); }
static inline ri512 set_zvalue(int i) { return _mm512_set1_epi32(i); }

// sets all values (assume 4, 8, and 16 arguments)
#define set_xvalues(...) _mm_set_epi32(__VA_ARGS__)
#define set_yvalues(...) _mm256_set_epi32(__VA_ARGS__)
#define set_zvalues(...) _mm512_set_epi32(__VA_ARGS__)

// stores and loads (see alignment requirements in definition)
static inline void mask_store_xvalue(void *addr, m8 mask, ri128 val);
static inline void store_xvalue(void *addr, ri128 val);
static inline void mask_store_yvalue(void *addr, m16 mask, ri256 val);
static inline void store_yvalue(void *addr, ri256 val);
static inline void mask_store_zvalue(void *addr, m32 mask, ri512 val);
static inline void store_zvalue(void *addr, ri512 val);

static inline ri128 mask_load_xvalue(ri128 src, void *addr, m8 mask);
static inline ri128 load_xvalue(void *addr);
static inline ri256 mask_load_yvalue(ri256 src, void *addr, m8 mask);
static inline ri256 load_yvalue(void *addr);
static inline ri512 mask_load_zvalue(ri512 src, void *addr, m16 mask);
static inline ri512 load_zvalue(void *addr);

// blends and permutations
static inline ri128 blend_xvalue(m8 mask, ri128 src1, ri128 src2);
static inline ri256 blend_yvalue(m8 mask, ri256 src1, ri256 src2);
static inline ri512 blend_zvalue(m16 mask, ri512 src1, ri512 src2);

static inline ri128 permute_xvalues(ri128 idx, ri128 src);
static inline ri256 permute_yvalues(ri256 idx, ri256 src);
static inline ri512 permute_zvalues(ri512 idx, ri512 src);

// aggregate comparisons: results are 1 or 0
static inline int less_xvalue(ri128 src1, ri128 src2);
static inline int equal_xvalue(ri128 src1, ri128 src2);
static inline int less_yvalue(ri256 src1, ri256 src2);
static inline int equal_yvalue(ri256 src1, ri256 src2);
static inline int less_zvalue(ri512 src1, ri512 src2);
static inline int equal_zvalue(ri512 src1, ri512 src2);

// rotations and shifts
static inline ri512 rotate_zvalue(ri512 r0, int amt);
static inline ri512 shift_zvalue(ri512 r0, int amt);

// arithmetics (mostly 1-to-1)
#define add_zvalues(x, y) _mm512_add_epi32(x, y)
#define sub_zvalues(x, y) _mm512_sub_epi32(x, y)

//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

// dump functions

// iarray to file
static inline void print_iarray(FILE *f, const char *const pname,
                                const int *const pvals, int n) {
  if (pname)
    fprintf(f, "reg %s:\n", pname);
  for (int i = 0; i < n; ++i)
    fprintf(f, "%6d", pvals[i]);
  fprintf(f, "\n");
}

void print_xreg(FILE *f, const char *const pname, ri128 r) {
  int vals[4] __attribute__((aligned(16)));
  store_xvalue(vals, r);
  print_iarray(f, pname, vals, 4);
}

void print_yreg(FILE *f, const char *const pname, ri256 r) {
  int vals[8] __attribute__((aligned(32)));
  store_yvalue(vals, r);
  print_iarray(f, pname, vals, 8);
}

void print_zreg(FILE *f, const char *const pname, ri512 r) {
  int vals[16] __attribute__((aligned(64)));
  store_zvalue(vals, r);
  print_iarray(f, pname, vals, 16);
}

// stores and loads

// addr shall be 16-byte aligned
void mask_store_xvalue(void *addr, m8 mask, ri128 val) {
  _mm_mask_store_epi32(addr, mask, val);
}

// addr shall be 16-byte aligned
void store_xvalue(void *addr, ri128 val) {
#if defined(__clang__)
  _mm_store_epi32(addr, val);
#else
  mask_store_xvalue(addr, M8_ALLONES, val);
#endif
}

// addr shall be 32-byte aligned
void mask_store_yvalue(void *addr, m16 mask, ri256 val) {
  _mm256_mask_store_epi32(addr, mask, val);
}

// addr shall be 32-byte aligned
void store_yvalue(void *addr, ri256 val) {
#if defined(__clang__)
  _mm256_store_epi32(addr, val);
#else // no such function for gcc
  mask_store_yvalue(addr, M8_ALLONES, val);
#endif
}

// addr shall be 64-byte aligned
void mask_store_zvalue(void *addr, m32 mask, ri512 val) {
  _mm512_mask_store_epi32(addr, mask, val);
}

// addr shall be 64-byte aligned
void store_zvalue(void *addr, ri512 val) { _mm512_store_epi32(addr, val); }

// addr shall be 16-byte aligned
ri128 mask_load_xvalue(ri128 src, void *addr, m8 mask) {
  return _mm_mask_load_epi32(src, mask, addr);
}

// addr shall be 16-byte aligned
ri128 load_xvalue(void *addr) {
#if defined(__clang__)
  return _mm_load_epi32(addr);
#else
  // gcc requires trickier way
  return mask_load_xvalue(_mm_undefined_si128(), addr, M8_ALLONES);
#endif
}

// addr shall be 32-byte aligned
ri256 mask_load_yvalue(ri256 src, void *addr, m8 mask) {
  return _mm256_mask_load_epi32(src, mask, addr);
}

// addr shall be 32-byte aligned
ri256 load_yvalue(void *addr) {
#if defined(__clang__)
  return _mm256_load_epi32(addr);
#else
  // gcc requires trickier way as well
  return mask_load_yvalue(_mm256_undefined_si256(), addr, M8_ALLONES);
#endif
}

// addr shall be 64-byte aligned
ri512 mask_load_zvalue(ri512 src, void *addr, m16 mask) {
  return _mm512_mask_load_epi32(src, mask, addr);
}

// addr shall be 64-byte aligned
ri512 load_zvalue(void *addr) { return _mm512_load_epi32(addr); }

// blends
ri128 blend_xvalue(m8 mask, ri128 src1, ri128 src2) {
  return _mm_mask_blend_epi32(mask, src1, src2);
}

ri256 blend_yvalue(m8 mask, ri256 src1, ri256 src2) {
  return _mm256_mask_blend_epi32(mask, src1, src2);
}

ri512 blend_zvalue(m16 mask, ri512 src1, ri512 src2) {
  return _mm512_mask_blend_epi32(mask, src1, src2);
}

ri512 permute_zvalues(ri512 idx, ri512 src) {
  return _mm512_permutexvar_epi32(idx, src);
} 

// comparisons
int less_zvalue(ri512 src1, ri512 src2) {
  m16 mask = _mm512_cmp_epi32_mask(src1, src2, _MM_CMPINT_NLE);
  return (mask == 0);
}

int equal_zvalue(ri512 src1, ri512 src2) {
  m16 mask = _mm512_cmp_epi32_mask(src1, src2, _MM_CMPINT_NE);
  return (mask == 0);
}

// rotations and shifts
ri512 rotate_zvalue(ri512 r0, int amt) {
  ri512 idx;
  int shift, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P;
  if ((amt % 16) == 0)
    return r0;
  shift = (amt > 0) ? (16 - (amt % 16)) : -amt;  
  A = (shift + 0) % 16;
  B = (shift + 1) % 16;
  C = (shift + 2) % 16;
  D = (shift + 3) % 16;
  E = (shift + 4) % 16;
  F = (shift + 5) % 16;
  G = (shift + 6) % 16;
  H = (shift + 7) % 16;
  I = (shift + 8) % 16;
  J = (shift + 9) % 16;
  K = (shift + 10) % 16;
  L = (shift + 11) % 16;
  M = (shift + 12) % 16;
  N = (shift + 13) % 16;
  O = (shift + 14) % 16;
  P = (shift + 15) % 16;
  idx = set_zvalues(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P);
  return permute_zvalues(idx, r0);
}

// negative amount is shift_right
ri512 shift_zvalue(ri512 r0, int amt) {
  m16 shiftmask;
  if (amt == 0)
    return r0;

  if (amt < 0) {
    shiftmask = (M16_ALLONES << (unsigned)(-amt)) & M16_ALLONES;
    return blend_zvalue(shiftmask, set_zvalue(0), rotate_zvalue(r0, amt));
  }

  shiftmask = (M16_ALLONES << (unsigned)(16 - amt)) & M16_ALLONES;
  return blend_zvalue(shiftmask, rotate_zvalue(r0, amt), set_zvalue(0));
}
