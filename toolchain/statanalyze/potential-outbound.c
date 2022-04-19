//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// stat analyzer and ton of garbage
//
// clang-tidy --checks=* potential-outbound.c -- potential-outbound.c
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdlib.h>

enum { ARRSZ = 10, FOOARG = 30 };

int g[ARRSZ];

int foo(int *a, int len) {
  assert((a != NULL) && (len > 1));
  return a[len / 2];
}

int main() { foo(g, FOOARG); }
