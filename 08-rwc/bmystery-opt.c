//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Mystery of pre-sorting data: data flow counter-argument
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simple-bench.h"

enum { ARRSZ = 32000, NITER = 50000 };

unsigned long long gsum;

double measure(int *arr, int len) {
  struct timespec time1, time2;
  int i, j;
  unsigned long long sum = 0;

  simple_gettime(&time1);
  for (i = 0; i < NITER; ++i) {
    NOOPT(i);
    for (j = 0; j < len; ++j) {
      NOOPT(j);
      int tmp = (arr[j] > 128) ? 1 : 0;
      sum = arr[j] * tmp; // moved to data-flow
      NOOPT(sum);
    }
  }
  simple_gettime(&time2);
  return diff(time1, time2);
}

int less(const void *lhs, const void *rhs) { return *(int *)lhs - *(int *)rhs; }

int main() {
  int i;
  int *data = malloc(ARRSZ * sizeof(int));
  double elapsed;

  for (i = 0; i < ARRSZ; ++i)
    data[i] = rand() % 256;

  printf("not pre-sorting data\n");
  elapsed = measure(data, ARRSZ);
  printf("elapsed time: %lf\n", elapsed);

  printf("pre-sorting data\n");
  qsort(data, ARRSZ, sizeof(int), less);
  elapsed = measure(data, ARRSZ);
  printf("elapsed time: %lf\n", elapsed);

  free(data);
}
