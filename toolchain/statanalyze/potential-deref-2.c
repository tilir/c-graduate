//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// stat analyzer detecting null pointer dereferencing with interesting trace
//
// clang-tidy potential-deref-2.c -- potential-deref-2.c
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int foo(const int *x) { return *x; }

int main() {
  int t = 2, x, res;
  foo(&t);  
  res = scanf("%d", &x);
  if (res == 1 && x < 3) {
    foo(NULL);
  }
}
