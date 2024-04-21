// $ sudo apt-get install libatlas-base-dev
// $ gcc -O2 test_mmult.c -lcblas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cblas.h>

double A[] = { 1, 2, 3, 4 };
double B[] = { 2, 0, 1, 2};
double C[] = { 0, 0, 0, 0};

int main() {
  int i, j;

  printf("-- A --\n");

  for (i = 0; i < 2; ++i) {
    for (j = 0; j < 2; ++j)
      printf("%5.1f", A[i * 2 + j]);
    printf("\n");
  }

  printf("-- B --\n");

  for (i = 0; i < 2; ++i) {
    for (j = 0; j < 2; ++j)
      printf("%5.1f", B[i * 2 + j]);
    printf("\n");
  }

  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 2, 2, 2, 1.0, A, 2, B, 2, 0.0, C, 2);

  printf("-- A * B --\n");

  for (i = 0; i < 2; ++i) {
    for (j = 0; j < 2; ++j)
      printf("%5.1f", C[i * 2 + j]);
    printf("\n");
  }
}

