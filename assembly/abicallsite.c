#include "abishow.h"

int callfoo(int a, int b) {
  // mov edx, esi
  // mov esi, edi
  // mov edi, edx
  // call  foo
  // add eax, edx
  // ret
  return foo(b, a) + b;
}

long long callbar() {
  // mov ecx, 8388608
  // mov edx, 18800
  // mov esi, 1500
  // movabs  r8, 70368744177664
  // mov edi, 50
  // jmp bar
  return bar(50, 1500, 18800, (1l << 23), (1ll << 46));
}

long long call_sums(int x, int y) {
  struct S s1 = {x, x, x};
  struct S s2 = {y, y, y};
  return sums(s1, s2, 42);
}