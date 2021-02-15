#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long mult_mod (unsigned long long n, 
                             unsigned long long k, 
                             unsigned long long m) {
  unsigned long long addend, sum;
  assert (m > 1);
  if (k == 0) return 0;
  addend = n % m; 
  sum = 0;
  while (k > 0) {
    if ((k % 2) == 1) {
      sum = (sum + addend) % m; k = k - 1;
    }
    addend = (addend + addend) % m; k = k / 2;
  }
  return sum;
}

unsigned long long smart_mult_mod (unsigned long long n, 
                                   unsigned long long k, 
                                   unsigned long long m) {
  unsigned long long ullmax = ~0ull;
  if (k == 0) return 0;
  if ((ullmax / k) < n)
    return mult_mod(n, k, m);
  return (n * k) % m;
}

unsigned long long pow_mod (unsigned long long n, 
                            unsigned long long k,
                            unsigned long long m) {
  unsigned long long mult, prod;
  assert (m > 1);
  if (k == 0) return 1;
  mult = n % m; 
  prod = 1;
  while (k > 0) {
    if ((k % 2) == 1) { 
      prod = smart_mult_mod(prod, mult, m); k = k - 1; 
    } 
    mult = smart_mult_mod(mult, mult, m); k = k / 2;
  }
  return prod;
}

const int NUMLIM = 20;

unsigned long long gcd(unsigned long long a,
                       unsigned long long b) {
  if (b > a) return gcd(b, a);
  for(;;) {
    unsigned long long q = a % b;
    if (q == 0)
      break;
    a = b;
    b = q;
  }
  return b;
}

int main () {
  int res, i;
  unsigned long long p, a;
  res = scanf("%llu", &p);
  assert(res == 1);

  printf("gcd test: %llu\n", gcd(24, 32));
  printf("pow test: %llu\n", pow_mod(24, 220, 221));

  srand(time(NULL));
  for (i = 0; i < NUMLIM; ++i) {
    unsigned long long pmod;
    do { 
      a = rand();
    } while (gcd(a, p) != 1);
    pmod = pow_mod(a, p - 1, p);
    printf("next witness: %llu result: %llu\n", a, pmod);
    if (pmod != 1) {
      printf("0");
      return 0;
    }
  }

  printf("1");
}

