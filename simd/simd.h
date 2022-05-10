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
// see also: github.com/BobSteagall/experimental/blob/master/simd
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

// make simple bitmasks
#define make_bitmask(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)           \
  ((A << 0) | (B << 1) | (C << 2) | (D << 3) | (E << 4) | (F << 5) |           \
   (G << 6) | (H << 7) | (I << 8) | (J << 9) | (K << 10) | (L << 11) |         \
   (M << 12) | (N << 13) | (O << 14) | (P << 15))

// dumps to stdout
#define DUMP_XREG(R) print_xreg(stdout, #R, R)
#define DUMP_YREG(R) print_yreg(stdout, #R, R)
#define DUMP_ZREG(R) print_zreg(stdout, #R, R)
#define DUMP_RZREG(R) print_rzreg(stdout, #R "rev", R)

// dump functions
static inline void print_xreg(FILE *f, const char *const pname, ri128 r);
static inline void print_yreg(FILE *f, const char *const pname, ri256 r);
static inline void print_zreg(FILE *f, const char *const pname, ri512 r);
static inline void print_rzreg(FILE *f, const char *const pname, ri512 r);

// sets single value to all register lanes
static inline ri128 set_xvalue(int i) { return _mm_set1_epi32(i); }
static inline ri256 set_yvalue(int i) { return _mm256_set1_epi32(i); }
static inline ri512 set_zvalue(int i) { return _mm512_set1_epi32(i); }

// sets all values (assume 4, 8, and 16 arguments)
#define set_xvalues(...) _mm_set_epi32(__VA_ARGS__)
#define set_yvalues(...) _mm256_set_epi32(__VA_ARGS__)
#define set_zvalues(...) _mm512_set_epi32(__VA_ARGS__)

// sets all values reverse
#define setr_xvalues(...) _mm_setr_epi32(__VA_ARGS__)
#define setr_yvalues(...) _mm256_setr_epi32(__VA_ARGS__)
#define setr_zvalues(...) _mm512_setr_epi32(__VA_ARGS__)

// stores and loads (see alignment requirements in definition)
static inline void mask_store_xvalue(void *addr, m8 mask, ri128 val);
static inline void store_xvalue(void *addr, ri128 val);
static inline void mask_store_yvalue(void *addr, m16 mask, ri256 val);
static inline void store_yvalue(void *addr, ri256 val);
static inline void store_yvalue_unaligned(void *addr, ri256 val);
static inline void mask_store_zvalue(void *addr, m32 mask, ri512 val);
static inline void store_zvalue(void *addr, ri512 val);
static inline void store_zvalue_unaligned(void *addr, ri512 val);

static inline ri128 mask_load_xvalue(ri128 src, const void *addr, m8 mask);
static inline ri128 load_xvalue(const void *addr);
static inline ri256 mask_load_yvalue(ri256 src, const void *addr, m8 mask);
static inline ri256 load_yvalue(const void *addr);
static inline ri256 load_yvalue_unaligned(const void *addr);
static inline ri512 mask_load_zvalue(ri512 src, const void *addr, m16 mask);
static inline ri512 load_zvalue(const void *addr);
static inline ri512 load_zvalue_unaligned(const void *addr);

// blends and permutations
#define blend_xvalues(mask, src1, src2) _mm_mask_blend_epi32(mask, src1, src2)
#define blend_yvalues(mask, src1, src2)                                        \
  _mm256_mask_blend_epi32(mask, src1, src2)
#define blend_zvalues(mask, src1, src2)                                        \
  _mm512_mask_blend_epi32(mask, src1, src2)

#define permute_xvalue(idx, src) _mm_permutexvar_epi32(idx, src)
#define permute_yvalue(idx, src) _mm256_permutexvar_epi32(idx, src)
#define permute_zvalue(idx, src) _mm512_permutexvar_epi32(idx, src)

// aggregate comparisons: results are 1 or 0
static inline int less_xvalue(ri128 src1, ri128 src2);
static inline int equal_xvalue(ri128 src1, ri128 src2);
static inline int less_yvalue(ri256 src1, ri256 src2);
static inline int equal_yvalue(ri256 src1, ri256 src2);
static inline int less_zvalue(ri512 src1, ri512 src2);
static inline int equal_zvalue(ri512 src1, ri512 src2);
static inline int first_equal_zvalue(ri512 src1, ri512 src2);

static inline m8 greater_yvalue_mask(ri256 src1, ri256 src2);
#define greater_zvalue_mask _mm512_cmpgt_epi32_mask
#define greater_eq_zvalue_mask _mm512_cmpge_epi32_mask

// rotations and shifts
static inline ri512 rotate_zvalue(ri512 r0, int amt);
static inline ri512 shift_zvalue(ri512 r0, int amt);
static inline ri512 shift_carry_up_zvalues(ri512 lo, ri512 hi, int amt);
static inline ri512 shift_carry_down_zvalues(ri512 lo, ri512 hi, int amt);
static inline void shift_carry_down_inplace_zvalues(ri512 *lo, ri512 *hi, int amt);

// arithmetics (mostly 1-to-1)
#define add_zvalues(x, y) _mm512_add_epi32(x, y)
#define sub_zvalues(x, y) _mm512_sub_epi32(x, y)
#define max_zvalues(x, y) _mm512_max_epi32(x, y)
#define min_zvalues(x, y) _mm512_min_epi32(x, y)

// sorting
static inline ri512 sort_pairwise(ri512 vals, ri512 perm, m32 mask);
static inline ri512 sort_two_lanes_of_8(ri512 vals);

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

void print_rzreg(FILE *f, const char *const pname, ri512 r) {
  int vals[16] __attribute__((aligned(64)));
  // inverse permutation
  ri512 perm =
      set_zvalues(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
  store_zvalue(vals, permute_zvalue(perm, r));
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

void store_yvalue_unaligned(void *addr, ri256 val) {
  _mm256_storeu_si256(addr, val);
}

// addr shall be 64-byte aligned
void mask_store_zvalue(void *addr, m32 mask, ri512 val) {
  _mm512_mask_store_epi32(addr, mask, val);
}

// addr shall be 64-byte aligned
void store_zvalue(void *addr, ri512 val) { _mm512_store_epi32(addr, val); }

void store_zvalue_unaligned(void *addr, ri512 val) {
  _mm512_storeu_si512(addr, val);
}

// addr shall be 16-byte aligned
ri128 mask_load_xvalue(ri128 src, const void *addr, m8 mask) {
  return _mm_mask_load_epi32(src, mask, addr);
}

// addr shall be 16-byte aligned
ri128 load_xvalue(const void *addr) {
#if defined(__clang__)
  return _mm_load_epi32(addr);
#else
  // gcc requires trickier way
  return mask_load_xvalue(_mm_undefined_si128(), addr, M8_ALLONES);
#endif
}

// addr shall be 32-byte aligned
ri256 mask_load_yvalue(ri256 src, const void *addr, m8 mask) {
  return _mm256_mask_load_epi32(src, mask, addr);
}

// addr shall be 32-byte aligned
ri256 load_yvalue(const void *addr) {
#if defined(__clang__)
  return _mm256_load_epi32(addr);
#else
  // gcc requires trickier way as well
  return mask_load_yvalue(_mm256_undefined_si256(), addr, M8_ALLONES);
#endif
}

ri256 load_yvalue_unaligned(const void *addr) {
  return _mm256_loadu_si256(addr);
}

// addr shall be 64-byte aligned
ri512 mask_load_zvalue(ri512 src, const void *addr, m16 mask) {
  return _mm512_mask_load_epi32(src, mask, addr);
}

// addr shall be 64-byte aligned
ri512 load_zvalue(const void *addr) { return _mm512_load_epi32(addr); }

ri512 load_zvalue_unaligned(const void *addr) {
  return _mm512_loadu_si512(addr);
}

// comparisons

int less_xvalue(ri128 src1, ri128 src2) {
  m8 mask = _mm_cmp_epi32_mask(src1, src2, _MM_CMPINT_NLE);
  return (mask == 0);
}

int equal_xvalue(ri128 src1, ri128 src2) {
  m8 mask = _mm_cmp_epi32_mask(src1, src2, _MM_CMPINT_NE);
  return (mask == 0);
}

int less_yvalue(ri256 src1, ri256 src2) {
  m8 mask = _mm256_cmp_epi32_mask(src1, src2, _MM_CMPINT_NLE);
  return (mask == 0);
}

int equal_yvalue(ri256 src1, ri256 src2) {
  m8 mask = _mm256_cmp_epi32_mask(src1, src2, _MM_CMPINT_NE);
  return (mask == 0);
}

m8 greater_yvalue_mask(ri256 src1, ri256 src2) {
  m8 mask;
  ri256 m = _mm256_cmpgt_epi32(src1, src2);
  mask = _mm256_movemask_ps((rf256)m); // ugly hack
  return mask;
}

int less_zvalue(ri512 src1, ri512 src2) {
  m16 mask = _mm512_cmp_epi32_mask(src1, src2, _MM_CMPINT_NLE);
  return (mask == 0);
}

int equal_zvalue(ri512 src1, ri512 src2) {
  m16 mask = _mm512_cmp_epi32_mask(src1, src2, _MM_CMPINT_NE);
  return (mask == 0);
}

// return equal position or -1 if no equal
int first_equal_zvalue(ri512 src1, ri512 src2) {
  m16 mask = _mm512_cmp_epi32_mask(src1, src2, _MM_CMPINT_EQ);
  if (mask != 0)
    return __builtin_ctz(mask);
  return -1;
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
  idx = setr_zvalues(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P);
  return permute_zvalue(idx, r0);
}

// negative amount is shift_right (or down if you want)
static inline int shiftmask16(int amt) {
  if (amt > 0) 
    return (M16_ALLONES << (unsigned)amt) & M16_ALLONES;
  return ~(M16_ALLONES << (unsigned)(16 + amt)) & M16_ALLONES;
}

ri512 shift_zvalue(ri512 r0, int amt) {
  ri512 rot, blend;
  if (amt == 0)
    return r0;
  rot = rotate_zvalue(r0, amt);
  blend = blend_zvalues(shiftmask16(amt), set_zvalue(0), rot);
  return blend;
}

static inline ri512 shift_carry_zvalues(ri512 lo, ri512 hi, int amt) {
  assert(amt != 0);
  ri512 carry = (amt > 0) ? lo : hi;
  ri512 reg = (amt > 0) ? hi : lo;
  ri512 carry_rot = rotate_zvalue(carry, amt);
  ri512 reg_rot = rotate_zvalue(reg, amt);
  return blend_zvalues(shiftmask16(amt), carry_rot, reg_rot);
}

ri512 shift_carry_up_zvalues(ri512 lo, ri512 hi, int amt) {
  if (amt == 0) return hi;
  return shift_carry_zvalues(lo, hi, amt);
}

ri512 shift_carry_down_zvalues(ri512 lo, ri512 hi, int amt) {
  if (amt == 0) return lo;
  return shift_carry_zvalues(lo, hi, -amt);
}

void shift_carry_down_inplace_zvalues(ri512 *lo, ri512 *hi, int amt) {
  *lo = shift_carry_down_zvalues(*lo, *hi, amt);
  *hi = shift_zvalue(*hi, -amt);
}

// sorting

// pairwise sort: mask is smth like: 0 1 0 1 0 1 ...
//                permutation is like 14, 15, 12, 13 ....
//                outputs min(v0, v1) max(v0, v1) ....
ri512 sort_pairwise(ri512 vals, ri512 perm, m32 mask) {
  ri512 exch = permute_zvalue(perm, vals);
  ri512 vmin = min_zvalues(vals, exch);
  ri512 vmax = max_zvalues(vals, exch);
  return blend_zvalues(mask, vmin, vmax);
}

// sort two lanes
ri512 sort_two_lanes_of_8(ri512 vals) {
  ri512 perm0, perm1, perm2, perm3, perm4, perm5;
  m32 mask0, mask1, mask2, mask3, mask4, mask5;

  perm0 = setr_zvalues(1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14);
  mask0 = make_bitmask(0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1);

  perm1 = setr_zvalues(3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12);
  mask1 = make_bitmask(0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1);

  perm2 = setr_zvalues(1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14);
  mask2 = make_bitmask(0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1);

  perm3 = setr_zvalues(7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8);
  mask3 = make_bitmask(0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1);

  perm4 = setr_zvalues(2, 3, 0, 1, 6, 7, 4, 5, 10, 11, 8, 9, 14, 15, 12, 13);
  mask4 = make_bitmask(0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1);

  perm5 = setr_zvalues(1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14);
  mask5 = make_bitmask(0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1);

  vals = sort_pairwise(vals, perm0, mask0);
  vals = sort_pairwise(vals, perm1, mask1);
  vals = sort_pairwise(vals, perm2, mask2);
  vals = sort_pairwise(vals, perm3, mask3);
  vals = sort_pairwise(vals, perm4, mask4);
  vals = sort_pairwise(vals, perm5, mask5);

  return vals;
}
