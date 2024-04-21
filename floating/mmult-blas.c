//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// benchmark: measuring multiplication with BLAS
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <cblas.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simple-bench.h"

enum { DEF_AX = 1600, DEF_AY = 1200, DEF_BY = 800 };

// matrix A is row-major and have AX rows, AY columns
// matrix B is row-major and have AY rows, BY colums
// matrix C is row-major and have AX rows, BY columns
void matrix_mult_cblas(const double *A, const double *B, double *C, int AX, int AY, int BY) {
  // from doc:
  // DGEMM(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC)
  // M specifies the number of rows of the matrix op(A) and of the matrix C.
  // N specifies the number of columns of the matrix op(B) and the number of columns of the matrix C.
  // K specifies  the number of columns of the matrix op(A) and the number of rows of the matrix op(B).
  // i.e. in my terms, M is AX, N is BY, K is AY
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, AX, BY, AY, 1.0, A, AY, B, BY, 0.0, C, BY);
}

void matrix_rand_init(double *arr, int sz) {
  for (int i = 0; i < sz; ++i)
    arr[i] = (rand() % 20) - 10;
}

int main(int argc, char **argv) {
  struct timespec time1, time2;
  double *a, *b, *c;
  int ax = DEF_AX, ay = DEF_AY, by = DEF_BY;
  double elapsed;
  srand(time(NULL));

#ifndef QUIET
  printf("Hello from mult bench. Usage:\n%s [ax] [ay] [by]\n", argv[0]);
#endif

  maybe_readopt(argc, argv, 1, &ax);
  maybe_readopt(argc, argv, 2, &ay);
  maybe_readopt(argc, argv, 3, &by);

  if (ax <= 0 || ay <= 0 || by <= 0)
    abort();

  a = malloc(ax * ay * sizeof(double));
  b = malloc(ay * by * sizeof(double));
  c = malloc(ax * by * sizeof(double));

  matrix_rand_init(a, ax * ay);
  matrix_rand_init(b, ay * by);
  matrix_rand_init(a, ax * by);

#ifndef QUIET
  printf("Measuring [%d x %d] * [%d x %d]\n", ax, ay, ay, by);
#endif
  simple_gettime(&time1);
  matrix_mult_cblas(a, b, c, ax, ay, by);
  simple_gettime(&time2);
  
  elapsed = diff(time1, time2);
  printf("%d %lf\n", ax, elapsed);

  free(c);
  free(b);
  free(a);
}
