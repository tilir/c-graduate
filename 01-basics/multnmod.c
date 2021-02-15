#include <assert.h>
#include <stdio.h>

unsigned mult_mod (unsigned n, unsigned k, unsigned m) {
  unsigned long long acc, prod;
  assert (m > 1);
  if (k == 0) return 0;
  acc = n % m; 
  prod = 0;
  for (; k > 0 ;) {
    if ((k % 2) == 1) 
      prod = (prod + acc) % m; 
    acc = (acc << 1) % m;
    k = k / 2;
  }
  return prod;
}

int main () {
  printf("%d\n", mult_mod(13, 3, 10));
}
