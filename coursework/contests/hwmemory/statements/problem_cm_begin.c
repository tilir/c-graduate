#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);

int compare(void *lhs, int lsz, void *rhs, int rsz) {
  int *ilhs = (int *)lhs;
  int *irhs = (int *)rhs;
  return (*ilhs - *irhs);
}

void printmem(void *mem, int *sizes, int nelts) {
  int i;
  int *imem = (int *) mem;
  for (i = 0; i < nelts; ++i) {
    printf("%d ", *imem);
    imem += sizes[i] / sizeof(int); 
  }
  printf("\n");
}

int main() {
  int res, n, i, nextsz, totalsz;
  int *sizes;
  int *mem, *pos;

  assert(sizeof(int) == 4);

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  sizes = (int *) calloc(n, sizeof(int));
  assert(sizes != NULL);

  // for tests we are setting sizes to 4, 8 or 12
  // but using only first 4

  totalsz = 0;
  nextsz = 0;
  for (i = 0; i < n; ++i) {
    nextsz = (nextsz + 4) % 8; // 0 -> 4 -> 8
    sizes[i] = nextsz + 4;
    totalsz += sizes[i];
  }

  mem = (int *) calloc(totalsz / sizeof(int), sizeof(int));
  assert(mem != NULL);
  pos = mem;

  for (i = 0; i < n; ++i) {
    int elt;
    res = scanf("%d", &elt);
    assert(res == 1);
    *pos = elt;
    pos += sizes[i] / sizeof(int);
  }

#ifdef VISUALIZE
  // print array before sort
  printmem(mem, sizes, n);
#endif

  xmsort(mem, sizes, n, compare);

  printmem(mem, sizes, n);

  free(mem);
  free(sizes);
}
