#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned partition(int *arr, unsigned low, unsigned high);

void print_fail(int *arr, int *shadow, int n, int i, int pivot) {
  int j;
  printf("\nFAILED!\nSource array: ");
  for (j = 0; j < n; ++j)
    printf("%d ", shadow[j]);
  printf("\nAfter partition (pivot = %d):\n", pivot);
  for (j = 0; j < n; ++j)
    printf("%d ", arr[j]);
  printf("\nLook at position %d, here something gone wrong\n", i);
}

int main() {
  int res, answ, n, i, pivot;
  int *parr, *shadow;

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  parr = calloc(n, sizeof(int));
  assert(parr);

  shadow = calloc(n, sizeof(int));
  assert(shadow);

  for (i = 0; i < n; ++i) {
    res = scanf("%d", parr + i);
    shadow[i] = parr[i];
    assert(res == 1);
  }
  
  pivot = parr[0];

  answ = partition(parr, 0, n - 1);

#if defined(VISUAL)
  for (i = 0; i < n; ++i)
    printf("%d ", shadow[i]);
  printf("\n");
  for (i = 0; i < n; ++i)
    printf("%d ", parr[i]);
  printf("\n");
#endif

  for (i = 0; i < n; ++i) {
    if ((i < answ && parr[i] > pivot) || (i > answ && parr[i] < pivot))
      print_fail(parr, shadow, n, i, pivot);
  }
  
  printf("%d\n", answ);

  free(parr);
}
