//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Naive iterative fibonacci. Try n = 50 or n = 90
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

unsigned long long fib(unsigned n) {
  unsigned long long first = 0ull, second = 1ull;
  int idx;
  if (n == 0)
    return 0ull;
  for (idx = 2; idx <= n; ++idx) {
    unsigned long long tmp = second;
    second = second + first;
    first = tmp;
  }
  return second;
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
