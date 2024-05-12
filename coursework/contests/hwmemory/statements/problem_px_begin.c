#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

void powNxN(unsigned (*A)[N], unsigned k, unsigned m);

int main() {
  int res, i, j;
  unsigned m, k;
  unsigned A[N][N];

  res = scanf("%u%u", &m, &k);
  assert(res == 2);
  assert(m > 0);

  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j) {
      res = scanf("%u", &A[i][j]);
      assert(res == 1);
    }

  powNxN(A, k, m);

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j)
      printf("%u ", A[i][j]);
    printf("\n");
  }
}
