//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Optimal power (n ^ k) % m
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned pow_mod(unsigned n, unsigned k, unsigned m) {
  unsigned long long acc, prod;
  assert(m > 1);
  if (k == 0)
    return 1;
  acc = n % m;
  prod = 1;
  for (; k > 0;) {
    if ((k % 2) == 1)
      prod = (prod * acc) % m;
    acc = (acc * acc) % m;
    k = k / 2;
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
