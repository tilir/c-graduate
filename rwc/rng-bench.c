//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// benchmark: measuring caches
// try: ./a.out 1000000 100
// try: ./a.out 10000000 10
//
//-----------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simple-bench.h"

const int NREPS = 5;
const int DEFMEM = 20;

typedef int ArrTy;

int main(int argc, char **argv) {
  struct timespec time1, time2;
  int i, k, K, N = DEFMEM, REPS = NREPS;
  ArrTy *a;
  double macc, looptime;
  long rn;

  printf("Hello from bandwidth bench. Usage:\n%s [logsize] [logreps]\n", argv[0]);
  maybe_readopt(argc, argv, 1, &N);
  maybe_readopt(argc, argv, 2, &REPS);
  if ((N < 1) || (N > 30) || (REPS < 1) || (REPS > 30)) {
    fprintf(stderr, "Logsize & logreps both 1-30\n");
    abort();
  }

  N = 1 << N;
  REPS = 1 << REPS;

  a = calloc(N, sizeof(ArrTy));
  printf("Measuring %d elements, %d repetitions\n", N, REPS);
  srand(time(NULL));

  // heat
  for (i = 0; i < N; ++i) {
    NOOPT(i);
    a[i] += 1;
  }

  // no rng
  simple_gettime(&time1);
  for (k = 0; k < REPS; ++k) {
    NOOPT(k);
    for (i = 0; i < N; ++i) {
      NOOPT(i);
      a[i] += 1;
    }
  }
  simple_gettime(&time2);
  looptime = diff(time1, time2);

  printf("No rng = %lf\n", looptime);

  // with rng
  simple_gettime(&time1);
  for (k = 0; k < REPS; ++k) {
    NOOPT(k);
    for (i = 0; i < N; ++i) {
      int t;
      NOOPT(i);
      t = rand() % N;
      NOOPT(t);
      a[i] += 1;
    }
  }
  simple_gettime(&time2);
  macc = diff(time1, time2);

  printf("Measured: %lf -> %lf. Ratio: %lf\n", looptime, macc, macc / looptime);
  free(a);
}
