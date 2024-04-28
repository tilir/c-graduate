#include <lapacke.h>
#include <stdio.h>

int main() {
  double a[5 * 5] = {3, 0,  0, 3, 0, -3, 0, -2, 0,  0, 0, -1, 0,
                     0, -3, 0, 0, 0, 3,  3, 0,  -1, 2, 0, 1};
  lapack_int p[5] = {0};
  lapack_int info, n, lda, i, j;

  n = 5;
  lda = 5;

  info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, n, n, a, lda, p);

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("% 2.2lf ", a[i * lda + j]);
    printf("\n");
  }

  for (i = 0; i < n; i++)
    printf("%d ", p[i]);
  printf("\n");
  return info;
}
