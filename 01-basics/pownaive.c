#include <assert.h>
#include <stdio.h>

unsigned pow_mod (unsigned n, unsigned k, unsigned m) {
  unsigned long long mult, prod;
  assert (m > 1);
  if (k == 0) return 1;
  mult = n % m; 
  prod = mult;
  while (k > 1) {
    prod = (prod * mult) % m;
    k -= 1;
  }
  return prod;
}

int main () {
  printf("%d\n", pow_mod(2018, 2018, 20));
}