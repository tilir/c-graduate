#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { BIG_AX = 2000, BIG_AY = 1600, BIG_BY = 1200 };
// enum { BIG_AX = 1600, BIG_AY = 1200, BIG_BY = 800 };

// A[AX][AY] * B[AY][BY] = C[AX][BY]
void matrix_mult(const int *A, const int *B, int *C, int AX, int AY, int BY) {
  assert(A != NULL && B != NULL && C != NULL);
  assert(AX > 0 && AY > 0 && BY > 0);
  for(int i = 0; i < AX; i++)
    for(int j = 0; j < BY; j++) {
      C[i * BY + j] = 0;
      // Multiply and accumulate the values  
      // in the current row of A and column of B
      for(int k = 0; k < AY; k++)
        C[i * BY + j] += A[i * AY + k] * B[k * BY + j];
    }
}

// to exclude silly errors
void smoketest() {
  int a[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  int b[2][1] = {{1}, {2}};
  int c[3][1];

  matrix_mult(&a[0][0], &b[0][0], &c[0][0], 3, 2, 1);

  assert(c[0][0] == 5);
  assert(c[1][0] == 11);
  assert(c[2][0] == 17);
}

void matrix_rand_init(int *arr, int sz) {
  srand(time(NULL));
  for (int i = 0; i < sz; ++i)
    arr[i] = (rand() % 20) - 10;
}

int
main () {
  clock_t start, fin;
  double diff;
  
  smoketest();
  int (*a)[BIG_AY] = (int (*)[BIG_AY]) malloc(BIG_AX * BIG_AY * sizeof(int));
  int (*b)[BIG_BY] = (int (*)[BIG_BY]) malloc(BIG_AY * BIG_BY * sizeof(int)); 
  int (*c)[BIG_BY] = (int (*)[BIG_BY]) malloc(BIG_AX * BIG_BY * sizeof(int));
  
  matrix_rand_init(&a[0][0], BIG_AX * BIG_AY);
  matrix_rand_init(&b[0][0], BIG_AY * BIG_BY);
  matrix_rand_init(&c[0][0], BIG_AX * BIG_BY);
  
  start = clock();
  matrix_mult(&a[0][0], &b[0][0], &c[0][0], BIG_AX, BIG_AY, BIG_BY);
  fin = clock();
  
  diff = (double)(fin - start) / CLOCKS_PER_SEC;
  printf("Elapsed: %lg seconds\n", diff);
  
  free(c);
  free(b);
  free(a);
}
