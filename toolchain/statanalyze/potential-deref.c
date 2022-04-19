//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// stat analyzer detecting nukk pointer dereferencing
//
// clang-tidy --checks=*,-modernize-* potential-deref.cc -- potential-deref.cc
//
//-----------------------------------------------------------------------------

int foo(int *x) { return *x; }

int main() {
  int t = 2;
  foo(&t);
  foo(nullptr);
}
