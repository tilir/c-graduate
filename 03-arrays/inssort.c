#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned moveright(int *arr, int key, unsigned last) {
  // TODO
}

void inssort(int *arr, unsigned len) {
  for (unsigned i = 0; i < len; ++i) {
    int key = arr[i];
    unsigned pos = moveright(arr, key, i);
    arr[pos] = key;
  }
}

int
main() {
  int idx;
  int unsorted[5] = {67, 1, 89, 45, 23};
  int sorted[5] = {1, 23, 45, 67, 89};

  // sort unsorted
  inssort(unsorted, 5);
  
  // after sort check sorted == unsorted
  for (idx = 0; idx < 5; ++idx)
    assert(sorted[idx] == unsorted[idx]);

  return 0;
}
