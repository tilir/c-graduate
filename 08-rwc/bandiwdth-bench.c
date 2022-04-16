//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// benchmark: measuring memory bandwidth
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simple-bench.h"

const int DEFMEM = 1000;
const unsigned long long NACCS = 1ull << 32;

int main(int argc, char **argv) {
  struct timespec time1, time2;
  unsigned long long i, j, K;
  int N = DEFMEM;
  char *a;

  printf("Hello from bandwidth bench. Usage:\n%s [size]\n", argv[0]);
  maybe_readopt(argc, argv, 1, &N);
  if (N < 0)
    abort();

  a = calloc(N, sizeof(char));
  K = NACCS / N;

  printf("Measuring %llu:%d iterations\n", K, N);
  simple_gettime(&time1);
  for (j = 0; j < K; ++j) {
    NOOPT(j);
    for (i = 0; i < N; ++i) {
      NOOPT(i);
      a[i]++;
    }
  }
  simple_gettime(&time2);

  printf("Measured: %lf\n", diff(time1, time2));
  free(a);
}
