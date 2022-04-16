//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// basic benchmark: measuring only loop
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simple-bench.h"

const int GIGAOPS = 1000000000;

int main(int argc, char **argv) {
  struct timespec time1, time2;
  int i, e = GIGAOPS;

  printf("Hello from loop bench. Usage:\n%s [size]\n", argv[0]);
  maybe_readopt(argc, argv, 1, &e);
  if (e < 0)
    abort();

  printf("Measuring %d iterations\n", e);
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
  for (i = 0; i < e; ++i) {
    NOOPT(i)
  }
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

  printf("Measured: %lf\n", diff(time1, time2));
}
