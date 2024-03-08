#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned 
linear_search(const int *parr, unsigned len, int elem) {
  assert(parr);
  unsigned i;
  for (i = 0; i < len; ++i)
    if (parr[i] == elem)
      return i;
  return len;
}

unsigned 
binary_search(const int *parr, unsigned len, int elem) {
  assert(parr);
  int l = 0; 
  int r = len - 1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (parr[m] == elem) return m;
    if (parr[m] < elem) l = m + 1;
    if (parr[m] > elem) r = m - 1;
  }
  return len; 
} 

int
main() {
  int unsorted[5] = {67, 1, 89, 45, 23};
  int sorted[5] = {1, 23, 45, 67, 89};
  
  unsigned lf = linear_search(unsorted, 5, 45);
  assert(lf == 3);
  
  unsigned lu = linear_search(unsorted, 5, 46);
  assert(lu == 5);

  unsigned bf = binary_search(sorted, 5, 23);
  assert(bf == 1);

  unsigned bu = binary_search(sorted, 5, 24);
  assert(bu == 5);
  
  return 0;
}