//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// benchmark: measuring multiplication with transpose
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simple-bench.h"

enum { DEF_AX = 1600, DEF_AY = 1200, DEF_BY = 800 };

typedef unsigned MatrixTy;

// A[AX][AY] * B[AY][BY] = C[AX][BY]
void matrix_mult_transpose(const int *A, const int *B, int *C, int AX, int AY,
                           int BY) {
  int *tmp = (int *)malloc(BY * AY * sizeof(int));

  assert(A != NULL && B != NULL && C != NULL && tmp != NULL);
  assert(AX > 0 && AY > 0 && BY > 0);

  for (int i = 0; i < AY; i++)
    for (int j = 0; j < BY; j++)
      tmp[j * AY + i] = B[i * BY + j];

  for (int i = 0; i < AX; i++)
    for (int j = 0; j < BY; j++) {
      C[i * BY + j] = 0;
      // Multiply and accumulate the values
      // in the current row of A and column of B
      for (int k = 0; k < AY; k++)
        C[i * BY + j] += A[i * AY + k] * tmp[j * AY + k];
    }

  free(tmp);
}

void matrix_rand_init(MatrixTy *arr, int sz) {
  for (int i = 0; i < sz; ++i)
    arr[i] = (rand() % 20) - 10;
}

int main(int argc, char **argv) {
  struct timespec time1, time2;
  MatrixTy *a, *b, *c;
  int ax = DEF_AX, ay = DEF_AY, by = DEF_BY;
  srand(time(NULL));
  printf("Hello from mult bench. Usage:\n%s [ax] [ay] [by]\n", argv[0]);

  maybe_readopt(argc, argv, 1, &ax);
  maybe_readopt(argc, argv, 2, &ay);
  maybe_readopt(argc, argv, 3, &by);

  if (ax <= 0 || ay <= 0 || by <= 0)
    abort();

  a = malloc(ax * ay * sizeof(MatrixTy));
  b = malloc(ay * by * sizeof(MatrixTy));
  c = malloc(ax * by * sizeof(MatrixTy));

  matrix_rand_init(a, ax * ay);
  matrix_rand_init(b, ay * by);
  matrix_rand_init(a, ax * by);

  printf("Measuring [%d x %d] * [%d x %d]\n", ax, ay, ay, by);
  simple_gettime(&time1);
  matrix_mult_transpose(a, b, c, ax, ay, by);
  simple_gettime(&time2);

  printf("Measured: %lf\n", diff(time1, time2));

  free(c);
  free(b);
  free(a);
}
