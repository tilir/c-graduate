#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int (*cmp_t)(const void *, const void *);

unsigned
min_element_pos(const void *parr, unsigned eltsize, unsigned len, cmp_t cmp) {
  unsigned i, minpos;
  const char *carr = (const char *) parr;
  const char *minp;

  assert(parr);
  assert(len > 0);
  minp = carr;
  minpos = 0;
  for (i = 1; i < len; ++i)
    if (cmp(carr + i * eltsize, minp)) {
      minp = carr + i * eltsize;
      minpos = i;
    }
  return minpos;
}

void swap_int(int *v1, int *v2) {
  int tmp = *v1;
  *v1 = *v2;
  *v2 = tmp;
}

void swap_char(char *v1, char *v2) {
  char tmp = *v1;
  *v1 = *v2;
  *v2 = tmp;
}

void swap(void *v1, void *v2, unsigned size) {
  unsigned i;
  for (i = 0; i < size; ++i)
    swap_char((char *)v1 + i, (char *)v2 + i);
}

void selstep(void *arr, unsigned eltsize, unsigned i, unsigned len, cmp_t cmp) {
  unsigned pos = min_element_pos((char *)arr + i * eltsize, 
                                 eltsize, 
                                 len - i, 
                                 cmp);
  pos += i;
  swap((char *)arr + i * eltsize, (char *)arr + pos * eltsize, eltsize);
}

int cmpi(const void *lhs, const void *rhs) {
  int lhsi = *(const int*)lhs;
  int rhsi = *(const int*)rhs;
  return lhsi < rhsi;
}

void selsort(int *arr, unsigned len) {
  unsigned i;

  for (i = 0; i < len; ++i)
    selstep(arr, sizeof(int), i, len, cmpi);
}

int
main() {
  int idx;
  int unsorted[5] = {67, 1, 89, 45, 23};
  int sorted[5] = {1, 23, 45, 67, 89};

  // sort unsorted
  selsort(unsorted, 5);
  
  // after sort check sorted == unsorted
  for (idx = 0; idx < 5; ++idx)
    assert(sorted[idx] == unsorted[idx]);

  return 0;
}

