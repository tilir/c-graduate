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
// clang-tidy --checks=*,-modernize-* potential-deref-2.cc
//
//-----------------------------------------------------------------------------

#include <iostream>

int foo(const int *x) { return *x; }

int main() {
  int t = 2;
  foo(&t);
  int x;
  std::cin >> x;
  if (x < 3) {
    foo(nullptr);
  }
}
