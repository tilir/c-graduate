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
// clang-tidy --checks=*,-modernize-* potential-outbound.cc
//
//-----------------------------------------------------------------------------

#include <cassert>

int g[100];

int foo(int *a, int len) {
  assert((a != nullptr) && (len > 1));
  return a[len / 2];
}

int main() { foo(g, 300); }
