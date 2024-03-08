//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Mystery of loop interchange
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { ARRSZ = 2000, NITER = 500 };

unsigned long long gsum;

#include "simple-bench.h"

double measure_ij(int *arr, int asz) {
  struct timespec time1, time2;
  int i, j, k, n;

  simple_gettime(&time1);
  for (k = 0; k < NITER; ++k) {
    NOOPT(k);
    for (i = 0; i < asz; ++i) {
      NOOPT(i);
      for (j = 0; j < asz; ++j) {
        NOOPT(j);
        n = arr[i * asz + j];
        NOOPT(n);
      }
    }
  }
  simple_gettime(&time2);
  return diff(time1, time2);
}

double measure_ji(int *arr, int asz) {
  struct timespec time1, time2;
  int i, j, k, n;

  simple_gettime(&time1);
  for (k = 0; k < NITER; ++k) {
    NOOPT(k);
    for (j = 0; j < asz; ++j) {
      NOOPT(j);
      for (i = 0; i < asz; ++i) {
        NOOPT(i);
        n = arr[i * asz + j];
        NOOPT(n);
      }
    }
  }
  simple_gettime(&time2);
  return diff(time1, time2);
}

int main() {
  int i;
  double elapsed;
  int *arr = malloc(ARRSZ * ARRSZ * sizeof(int));

  srand(time(NULL));
  for (i = 0; i < ARRSZ * ARRSZ; ++i)
    arr[i] = rand() % 100;

  printf("i then j loop order\n");
  elapsed = measure_ij(arr, ARRSZ);
  printf("elapsed time: %lf\n", elapsed);

  printf("j then i loop order\n");
  elapsed = measure_ji(arr, ARRSZ);
  printf("elapsed time: %lf\n", elapsed);
}
