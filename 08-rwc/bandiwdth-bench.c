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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simple-bench.h"

const int NREPS = 4;
const int DEFMEM = 1000;
const int NACCS = 1ull << 30;

typedef int ArrTy;

int main(int argc, char **argv) {
  struct timespec time1, time2;
  int i, j, k, K, N = DEFMEM, REPS = NREPS;
  ArrTy *a;
  double macc, looptime, coef;

  printf("Hello from bandwidth bench. Usage:\n%s [size] [reps]\n", argv[0]);
  maybe_readopt(argc, argv, 1, &N);
  maybe_readopt(argc, argv, 2, &REPS);
  if (N < 0)
    abort();

  a = calloc(N, sizeof(ArrTy));
  K = NACCS / N;
  coef = (double)NACCS / (K * N);
  coef = pow(coef, REPS);
  printf("Measuring %d:%d iterations, %d repetitions, error coef is %lf\n", K,
         N, REPS, coef);
  simple_gettime(&time1);
  for (k = 0; k < REPS; ++k) {
    NOOPT(k);
    for (j = 0; j < K; ++j) {
      NOOPT(j);
      for (i = 0; i < N; ++i) {
        NOOPT(i);
        a[i]++;
      }
    }
  }
  simple_gettime(&time2);
  macc = diff(time1, time2);

  simple_gettime(&time1);
  for (k = 0; k < REPS; ++k) {
    NOOPT(k);
    for (j = 0; j < K; ++j) {
      NOOPT(j);
      for (i = 0; i < N; ++i) {
        NOOPT(i);
      }
    }
  }
  simple_gettime(&time2);
  looptime = diff(time1, time2);

  printf("Measured: %lf, %lf, %lf\n", macc, looptime,
         (coef / REPS) * (macc - looptime));
  free(a);
}
