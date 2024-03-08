//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Naive approach to (n ^ k) % m
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned pow_mod(unsigned n, unsigned k, unsigned m) {
  unsigned long long mult, prod;
  assert(m > 1);
  if (k == 0)
    return 1;
  mult = n % m;
  prod = mult;
  while (k > 1) {
    prod = (prod * mult) % m;
    k -= 1;
  }
  return prod;
}

int main() {
  unsigned n, k, m, x;
  int res;
  res = scanf("%u%u%u", &n, &k, &m);
  if (res != 3 || m == 0) {
    printf("%s\n", "Wrong input");
    abort();
  }
  x = pow_mod(n, k, m);
  printf("(%u ^ %u) mod %u = %u\n", n, k, m, x);
  return 0;
}
