#include <assert.h>
#include <stdio.h>
#include <math.h>

unsigned long long sieve_bound(unsigned num) {
  assert(num > 20);
  double dnum = num;
  double dres = dnum * (log(dnum) + log(log(dnum)));
  return (unsigned long long) round(dres);
}

int
main() {
  printf("for 1000: %llu\n", sieve_bound(1000));
  printf("for 1000000: %llu\n", sieve_bound(1000000));
}

