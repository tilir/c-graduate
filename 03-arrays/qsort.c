#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned partition(int *arr, unsigned low, unsigned high) {
  // TODO: code here
}

void qsort_impl(int *arr, unsigned low, unsigned high) {
  if (low >= high) return;
  unsigned pi = partition(arr, low, high);
  if (pi > low)
    qsort_impl(arr, low, pi - 1);
  qsort_impl(arr, pi + 1, high);
}

void qsort_(int *arr, unsigned len) {
  qsort_impl(arr, 0, len - 1);
}

enum {
  UNSORTED_SZ = 1000
};

int
main() {
  int idx;
  int unsorted[UNSORTED_SZ];

  // sort unsorted
  qsort_(unsorted, UNSORTED_SZ);
  
  // after sort check unsorted to be ordered
  for (idx = 0; idx < (UNSORTED_SZ - 1); ++idx)
    assert(unsorted[idx] < unsorted[idx + 1]);

  return 0;
}
