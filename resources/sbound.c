//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Sieve bound for erathosphenes
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long sieve_bound(unsigned num) {
  assert(num > 20);
  double dnum = num;
  double dres = dnum * (log(dnum) + log(log(dnum)));
  if (dres > LONG_MAX) {
    printf("You will be unable to allocate this size\n");
    abort();
  }
  return (long)round(dres);
}

int main() {
  int res;
  unsigned num;
  long bnd;
  res = scanf("%d", &num);
  if (res != 1 || num <= 20) {
    printf("%s\n", "Wrong number");
    abort();
  }
  bnd = sieve_bound(num);
  printf("%ld\n", bnd);
}
