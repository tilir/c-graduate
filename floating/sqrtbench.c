//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// benchmark: measuring isqrt
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <fenv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simple-bench.h"

enum { DEF_REP = 1000, DEF_VAL = 10010, DEF_ADD = 10000 };

unsigned isqrt(unsigned x) {
  unsigned l = 0, r = x, mid;
  while (l < r) {
    mid = (l + r + 1) / 2;
    if (x < mid * mid)
      r = mid - 1;
    else
      l = mid;
  }
  return l;
}

unsigned dsqrt(unsigned x) {
  double d = sqrt(x);
  fesetround(FE_DOWNWARD);
  return rint(d);
}

int main(int argc, char **argv) {
  struct timespec time1, time2;
  int rep = DEF_REP, val = DEF_VAL, res;
  double elapsed;

#ifndef QUIET
  printf("Hello from sqrt bench. Usage:\n%s [rep] [val]\n", argv[0]);
#endif

  maybe_readopt(argc, argv, 1, &rep);
  maybe_readopt(argc, argv, 2, &val);

  if (rep <= 0 || val <= 0)
    abort();

#ifndef QUIET
  printf("Measuring isqrt(%d), using %d * %d repetitions\n", val, rep, DEF_ADD);
#endif
  simple_gettime(&time1);
  for (int i = 0; i < rep; ++i) {
    for (int j = 0; j < DEF_ADD; ++j) {
      res = isqrt(val);
      NOOPT(res);
      NOOPT(j);
    }
    NOOPT(i);
  }
  simple_gettime(&time2);
  elapsed = diff(time1, time2);
  printf("%lf\n", elapsed);

#ifndef QUIET
  printf("Measuring dsqrt(%d), using %d * %d repetitions\n", val, rep, DEF_ADD);
#endif
  simple_gettime(&time1);
  for (int i = 0; i < rep; ++i) {
    for (int j = 0; j < DEF_ADD; ++j) {
      res = dsqrt(val);
      NOOPT(res);
      NOOPT(j);
    }
    NOOPT(i);
  }
  simple_gettime(&time2);
  elapsed = diff(time1, time2);
  printf("%lf\n", elapsed);
}
