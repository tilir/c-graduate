//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Naive recursive fibonacci. Try n = 50.
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

unsigned long long fib(unsigned n) {
  if (n == 0)
    return 0ull;
  if (n <= 2)
    return 1ull;
  return fib(n - 1) + fib(n - 2);
}

int main() {
  unsigned x;
  unsigned long long f;
  int res;
  res = scanf("%u", &x);
  if (res != 1) {
    printf("%s\n", "Wrong input");
    abort();
  }
  f = fib(x);
  printf("%llu\n", f);
  return 0;
}
