#include <assert.h>
#include <stdio.h>

void copy_eq(unsigned long long res[4], unsigned long long src[4]) {
  for (int i = 0; i < 4; ++i)
    res[i] = src[i];
}

void reduce_m(unsigned long long n[4], unsigned m) {
  for (int i = 0; i < 4; ++i)
    n[i] = n[i] % m;
}

void mul_eq(unsigned long long prod[4], 
            unsigned long long mult[4],
            unsigned long long m) {
  unsigned long long res[4];
  res[0] = (prod[0] * mult[0] + prod[1] * mult[2]);
  res[1] = (prod[0] * mult[1] + prod[1] * mult[3]);
  res[2] = (prod[2] * mult[0] + prod[3] * mult[2]);
  res[3] = (prod[2] * mult[1] + prod[3] * mult[3]);
  reduce_m(res, m);
  copy_eq(prod, res);
} 

void pow_mod (unsigned long long n[4], unsigned k, unsigned m) {
  unsigned long long mult[4];
  unsigned long long prod[4] = {1, 0, 0, 1};
  assert (m > 1);
  copy_eq(mult, n); 
  reduce_m(mult, m);
  while (k > 0) {
    if ((k % 2) == 1) { 
      mul_eq(prod, mult, m); 
    } 
    mul_eq(mult, mult, m);
    k = k / 2;
  }
  copy_eq(n, prod);
}

int main () {
  unsigned long long n[4] = {1, 1, 1, 0};
  pow_mod(n, 50, 1000);
  printf("%llu\n", n[1]);
}
