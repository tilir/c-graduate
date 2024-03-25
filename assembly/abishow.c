#include "abishow.h"

int foo(int x, int y) {
  // lea eax, [rdi+rsi]
  // ret
  return x + y;
}

long long bar(char a, short b, int c, long d, long long e) {
  // movsx esi, si
  // movsx edi, dil
  // add edi, esi
  // add edi, edx
  // movsx rdi, edi
  // add rdi, rcx
  // lea rax, [rdi+r8]
  // ret
  return a + b + c + d + e;
}

long long bar2(char a, short b, int c, long d, long long e, int v0, int v1) {
  return a + b + c + d + e + v0 + v1;
}

long long sums(struct S s1, struct S s2, int a) {
  return s1.y + s2.y + a;
}
