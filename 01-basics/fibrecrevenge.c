#include <stdio.h>

unsigned long long fib(unsigned n) {
  unsigned long long fk, fkprev;
  unsigned k;
  if (n == 0) return 0ull; 
  if (n <= 2) return 1ull;
  k = (n + (n % 2)) / 2; 
  fk = fib(k); 
  fkprev = fib(k - 1);
  if ((n % 2) == 0)
    return (2 * fkprev + fk) * fk;
  return fk * fk + fkprev * fkprev;
}

int main () {
  printf("%llu\n", fib(50));
}
