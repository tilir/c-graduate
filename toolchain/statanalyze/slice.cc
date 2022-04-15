//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// stat analyzer detecting slicing issue
//
// clang-tidy --checks=*,-modernize-* slice.cc -- slice.cc
//
//-----------------------------------------------------------------------------

#include <iostream>

using std::cout;
using std::endl;

struct B {
  int a = 2;
  virtual void f() { cout << "B::f " << a << endl; }
};

struct D : B {
  int b = 3;
  void f() override { cout << "D::f " << a << " " << b << endl; }
};

void use(B b) { b.f(); }

int main() {
  D d;
  use(d);
}
