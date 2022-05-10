//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Simple SIMD tests
//
// Compilation line:
// > gcc -O2 -march=tigerlake basic_tests.c
//
//-----------------------------------------------------------------------------

#include <stdio.h>

#include "simd.h"

void set_and_print() {
  ri128 x;
  ri256 y;
  ri512 z0, z1, zd, zr;

  printf("%s\n", "set and print test");
  x = set_xvalue(4);
  assert(equal_xvalue(x, set_xvalues(4, 4, 4, 4)));
  y = set_yvalue(8);
  assert(equal_yvalue(y, set_yvalues(8, 8, 8, 8, 8, 8, 8, 8)));
  z0 = set_zvalue(16);
  z1 = set_zvalues(16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
                   16);
  assert(equal_zvalue(z0, z1));
  zd = set_zvalues(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  zr = setr_zvalues(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  DUMP_ZREG(zd);
  DUMP_RZREG(zd);
  DUMP_ZREG(zr);
  DUMP_RZREG(zr);
}

void store_and_load() {
  int vals[16] __attribute__((aligned(64)));
  ri512 z0, z1, z2, z3;
  m16 mask = 0xF0F0;

  printf("%s\n", "store and load test");
  z0 = set_zvalue(16);
  z1 = set_zvalue(20);
  store_zvalue(vals, z0);
  z2 = mask_load_zvalue(z1, vals, mask); // load and blend with z1
  z3 = blend_zvalues(mask, z1, z0);
  assert(equal_zvalue(z2, set_zvalues(16, 16, 16, 16, 20, 20, 20, 20, 16, 16,
                                      16, 16, 20, 20, 20, 20)));
  assert(equal_zvalue(z2, z3));
  z3 = blend_zvalues(mask, z0, z1);
  assert(equal_zvalue(z3, set_zvalues(20, 20, 20, 20, 16, 16, 16, 16, 20, 20,
                                      20, 20, 16, 16, 16, 16)));
}

void permute() {
  ri512 z0, z1, z2, z3, answ;
  printf("%s\n", "permute test");
  z0 = setr_zvalues(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  z1 = setr_zvalues(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
  z2 = permute_zvalue(z1, z0); // equal to z0, as z1 is identity
  z3 = permute_zvalue(z0, z1); // equal to z0, as z0 is reverse
  assert(equal_zvalue(z0, z2));
  assert(equal_zvalue(z2, z3));
  z0 = set_zvalue(16);
  z1 = set_zvalues(16, 16, 16, 16, 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
  assert(11 == first_equal_zvalue(z0, z1));
  // permutation with loss of information
  z0 = set_zvalues(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  z1 = setr_zvalues(0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
  z1 = permute_zvalue(z1, z0);
  answ = set_zvalues(1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0);
  assert(equal_zvalue(z1, answ));
}

void rotate_shift() {
  ri512 z0, z1, z2, lo, hi, up, down, anshi;
  printf("%s\n", "rotate test");
  z0 = set_zvalues(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  z1 = rotate_zvalue(z0, 3);
  assert(equal_zvalue(
      z1, set_zvalues(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13)));
  z2 = rotate_zvalue(z0, -4);
  assert(equal_zvalue(
      z2, set_zvalues(3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4)));
  z1 = shift_zvalue(z0, 3);
  assert(equal_zvalue(
      z1, set_zvalues(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0)));
  z2 = shift_zvalue(z0, -4);
  assert(equal_zvalue(
      z2, set_zvalues(0, 0, 0, 0, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4)));
  lo = set_zvalues(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  hi = add_zvalues(lo, set_zvalue(16));
  up = shift_carry_up_zvalues(lo, hi, 3); // 28, 27, ...., 16, 15, 14, 13
  assert(equal_zvalue(up, add_zvalues(lo, set_zvalue(13))));
  down = shift_carry_down_zvalues(lo, hi, 4); // 19, 18, 17, 16, 15, ..., 5, 4
  assert(equal_zvalue(down, add_zvalues(lo, set_zvalue(4))));
  shift_carry_down_inplace_zvalues(&lo, &hi, 4);
  assert(equal_zvalue(lo, down));
  anshi = set_zvalues(0, 0, 0, 0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20);
  assert(equal_zvalue(hi, anshi));
}

void arithmetics() {
  ri512 z0, z1, z2, z3;
  printf("%s\n", "arithmetics test");
  z0 = set_zvalue(10);
  z1 = add_zvalues(z0, z0);
  assert(equal_zvalue(z1, set_zvalue(20)));
  z1 = set_zvalues(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  z2 = min_zvalues(z0, z1);
  assert(equal_zvalue(
      z2, set_zvalues(10, 10, 10, 10, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)));
  z3 = max_zvalues(z0, z1);
  assert(equal_zvalue(z3, set_zvalues(15, 14, 13, 12, 11, 10, 10, 10, 10, 10,
                                      10, 10, 10, 10, 10, 10)));
}

void sorts() {
  ri512 z0, z1, z2;
  printf("%s\n", "sort test");
  z0 = set_zvalues(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  z1 = set_zvalues(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
  z2 = set_zvalues(0, 2, 14, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 15);
  DUMP_ZREG(sort_two_lanes_of_8(z0));
  DUMP_ZREG(sort_two_lanes_of_8(z1));
  DUMP_ZREG(sort_two_lanes_of_8(z2)); // 1 8 9 ... 15 0 2 3 ... 14
}

int main() {
  set_and_print();
  store_and_load();
  permute();
  rotate_shift();
  arithmetics();
  sorts();
  printf("%s\n", "done");
}