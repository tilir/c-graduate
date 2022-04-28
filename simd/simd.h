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
enum {
  M8_ALLONES = 0xFF,
  M16_ALLONES = 0xFFFF,
  M32_ALLONES = 0xFFFFFFFF,
  M64_ALLONES = 0xFFFFFFFFFFFFFFFF,
};

// sets single value to all register lanes
static inline ri128 set_xvalue(int i) { return _mm_set1_epi32(i); }
static inline ri256 set_yvalue(int i) { return _mm256_set1_epi32(i); }
static inline ri512 set_zvalue(int i) { return _mm512_set1_epi32(i); }

// stores and loads (see alignment requirements in definition)
static inline void mask_store_xvalue(void *addr, m8 mask, ri128 val);
static inline void store_xvalue(void *addr, ri128 val);
static inline void mask_store_yvalue(void *addr, m16 mask, ri256 val);
static inline void store_yvalue(void *addr, ri256 val);
static inline void mask_store_zvalue(void *addr, m32 mask, ri512 val);
static inline void store_zvalue(void *addr, ri512 val);

static inline ri128 mask_load_xvalue(ri128 src, void *addr, m8 mask);
static inline ri128 load_xvalue(void *addr);
static inline ri256 mask_load_yvalue(ri256 src, void *addr, m16 mask);
static inline ri256 load_yvalue(void *addr);
static inline ri512 mask_load_zvalue(ri512 src, void *addr, m32 mask);
static inline ri512 load_zvalue(void *addr);

// dump functions
static inline void print_xreg(FILE *f, const char *const pname, ri128 r);
static inline void print_yreg(FILE *f, const char *const pname, ri256 r);
static inline void print_zreg(FILE *f, const char *const pname, ri512 r);

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
  mask_store_yvalue(addr, M16_ALLONES, val);
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
ri256 mask_load_yvalue(ri256 src, void *addr, m16 mask) {
  return _mm256_mask_load_epi32(src, mask, addr);
}

// addr shall be 32-byte aligned
ri256 load_yvalue(void *addr) {
#if defined(__clang__)
  return _mm256_load_epi32(addr);
#else
  // gcc requires trickier way as well
  return mask_load_yvalue(_mm256_undefined_si256(), addr, M16_ALLONES);
#endif
}

// addr shall be 64-byte aligned
ri512 mask_load_zvalue(ri512 src, void *addr, m32 mask) {
  return _mm512_mask_load_epi32(src, mask, addr);
}

// addr shall be 64-byte aligned
ri512 load_zvalue(void *addr) { return _mm512_load_epi32(addr); }

// dumps to stdout
#define DUMP_XREG(R) print_xreg(stdout, #R, R)
#define DUMP_YREG(R) print_yreg(stdout, #R, R)
#define DUMP_ZREG(R) print_zreg(stdout, #R, R)

// print integer array to file
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
