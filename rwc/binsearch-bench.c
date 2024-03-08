//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// benchmark: measuring binary search
// see also: https://quick-bench.com/q/e7_6reEBEPWXnOqwpgKapL3yjp4
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simple-bench.h"

typedef int ArrTy;

const int SZ = 22;        // 1 << 22 main
const int SZ_SHIFT = 10;  // 1 << 10 additional
const int REPS = 1000000; // # of reps

static ArrTy dice(ArrTy min, ArrTy max) { return (rand() % max) + min; }

static void iota(ArrTy *begin, ArrTy *end, ArrTy fst) {
  for (ArrTy *cur = begin; cur != end; ++cur)
    *cur = fst++;
}

int binarySearch(ArrTy *arr, int l, int r, ArrTy x) {
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (arr[m] == x)
      return 1;

    if (arr[m] < x)
      l = m + 1;
    else
      r = m - 1;
  }

  return 0;
}

static double BinarySearchBench(int sz, int nreps) {
  struct timespec time1, time2;
  int b, i;
  ArrTy *a = malloc(sz * sizeof(ArrTy));
  iota(a, a + sz, 0);

  simple_gettime(&time1);
  for (i = 0; i < nreps; ++i) {
    b = binarySearch(a, 0, sz, dice(0, sz - 1));
    NOOPT(b);
    NOOPT(i);
  }
  simple_gettime(&time2);
  return diff(time1, time2);
}

int main(int argc, char **argv) {
  int reps = REPS;
  int sz = SZ;
  int shift = SZ_SHIFT;
  ArrTy *a;
  double t;

  printf("Hello from binsearch bench. Usage:\n%s [logsz] [logshift] [reps]\n",
         argv[0]);
  maybe_readopt(argc, argv, 1, &sz);
  maybe_readopt(argc, argv, 2, &shift);
  maybe_readopt(argc, argv, 3, &reps);

  printf("Measuring (1 << %d), %d repetitions\n", sz, reps);
  t = BinarySearchBench(1 << sz, reps);
  printf("Measured: %lf\n", t);

  printf("Measuring (1 << %d) + (1 << %d), %d repetitions\n", sz, shift, reps);
  t = BinarySearchBench((1 << sz) + (1 << shift), reps);
  printf("Measured: %lf\n", t);
}
