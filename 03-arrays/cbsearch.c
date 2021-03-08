#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int (*cmp_t)(const void *key, const void *elt);

void *bsearch_(const void *key, const void *base, int num, int size, cmp_t cmp) {
  const char *pivot;
  int result;

  while (num > 0) {
    pivot = (const char *) base + (num / 2) * size;
	result = cmp(key, (const void *) pivot);
	if (result == 0) return (void *)pivot;
	if (result > 0) {
	  base = pivot + size; 
	  num--;
	}
	num = num / 2;
  }

  return NULL;
}

// ----------------- using bsearch_ --------------------------

int intcmp(const void *x, const void *y) {
  int ix = *(int *) x;
  int iy = *(int *) y;
  if (ix == iy) return 0;
  if (ix < iy) return -1;
  return 1;  
}

int
main() {
  int sorted[5] = {1, 23, 45, 67, 89};
  
  int key = 23;
  
  void *bf = bsearch_(&key, sorted, 5, sizeof(int), intcmp);
  assert(bf != NULL);

  key = 24;
  
  void *bu = bsearch_(&key, sorted, 5, sizeof(int), intcmp);
  assert(bu == NULL);
  
  return 0;
}
