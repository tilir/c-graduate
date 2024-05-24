#include <stdio.h>

unsigned caller(unsigned n, unsigned k, unsigned m);

unsigned callee(unsigned x, unsigned y, unsigned m) {
  unsigned addend, sum;

  if ((0ull == x) || (((~0ull) / x) > y))
    return (x * y) % m;

  addend = x % m;
  sum = 0;
  while (y > 0) {
    if ((y % 2) == 1) {
      sum = (sum + addend) % m; y = y - 1;
    }
    else {
      addend = (addend + addend) % m; y = y / 2;
    }
  }
  return sum;
}

#ifdef ETA

unsigned caller(unsigned n, unsigned k, unsigned m) {
  unsigned mult, prod;
  if (k == 0) return 1;
  mult = n % m;
  prod = 1;
  while (k > 0) {
    if ((k % 2) == 1) {
      prod = callee(prod, mult, m); k = k - 1;
    }
    else {
      mult = callee(mult, mult, m); k = k / 2;
    }
  }
  return prod;
}

#endif

int main() {
  unsigned a, b, c, res;
  scanf("%u%u%u", &a, &b, &c);
  res = caller(a, b, c);
  printf("%u\n", res);
}

