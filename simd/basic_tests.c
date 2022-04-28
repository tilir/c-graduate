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

#include "simd.h"

void set_and_print() {
  ri128 x = set_xvalue(4);
  DUMP_XREG(x);
  ri256 y = set_yvalue(8);
  DUMP_YREG(y);
  ri512 z = set_zvalue(16);
  DUMP_ZREG(z);
}

int main() { set_and_print(); }