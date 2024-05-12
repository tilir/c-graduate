#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int majority_element(const int *parr, int len);

int main() {
  int res, n, i, answ;
  int *arr;

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  arr = calloc(n, sizeof(int));
  for (i = 0; i < n; ++i) {
    res = scanf("%d", arr + i);
    assert(res == 1);
  }

  answ = majority_element(arr, n);

  printf("%d\n", answ);

  free(arr);
  return 0;
}
