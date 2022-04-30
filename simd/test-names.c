//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Different approaches to SIMD intrinsics
//
// Compilation line see in basic_tests.c
//
//-----------------------------------------------------------------------------

#include <stdio.h>

#include "simd.h"

typedef int __attribute__((vector_size(64))) v16si;

int main() {
  __m512i regular_val = _mm512_set1_epi32(20);
  DUMP_ZREG(regular_val);
  v16si gcc_val = 20 - (v16si){};
  DUMP_ZREG((__m512i)gcc_val);
  ri512 val = set_zvalue(20);
  DUMP_ZREG(val);
}