// $ sudo apt-get install libatlas-base-dev
// $ gcc -O2 test_mmult.c -lcblas
// test on wolphram: https://tinyurl.com/ms37nyju
// {{1, 2}, {3, 4}, {5, 6}} * {{2, 0, 1, 2}, {2, 1, 1, 0}}
// result:
// {{6, 2, 3, 2}, {14, 4, 7, 6}, {22, 6, 11, 10}}

#include <cblas.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int AX = 3;
int AY = 2;
int BY = 4;

// A row major and have 3 rows 2 columns, i.e. 3 * 2
double A[3 * 2] = {1, 2, 3, 4, 5, 6};

// B row major and have 2 rows 4 columns, i.e. 2 * 4
double B[2 * 4] = {2, 0, 1, 2, 2, 1, 1, 0};

// C row major and have 3 rows, 4 columns, i.e. 3 * 4
double C[3 * 4] = {0};

double CETA[] = {6, 2, 3, 2, 14, 4, 7, 6, 22, 6, 11, 10};

int main() {
  int i, j, failed = 0;

  printf("-- A --\n");

  for (i = 0; i < AX; ++i) {
    for (j = 0; j < AY; ++j)
      printf("%5.1f", A[i * AY + j]);
    printf("\n");
  }

  printf("-- B --\n");

  for (i = 0; i < AY; ++i) {
    for (j = 0; j < BY; ++j)
      printf("%5.1f", B[i * BY + j]);
    printf("\n");
  }

  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, AX, BY, AY, 1.0, A, AY,
              B, BY, 0.0, C, BY);

  printf("-- A * B --\n");

  for (i = 0; i < AX; ++i) {
    for (j = 0; j < BY; ++j)
      printf("%5.1f", C[i * BY + j]);
    printf("\n");
  }

  for (i = 0; i < AX; ++i)
    for (j = 0; j < BY; ++j) {
      double v = C[i * BY + j], w = CETA[i * BY + j];
      if (v != w) {
        printf("Error in C[%d, %d]: %lf != %lf\n", i, j, v, w);
        failed = 1;
      }
    }

  if (!failed)
    printf("Test passed!\n");
}
