//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// valgrind simple out of range
// here valgrind can not do anything (!) on stack
//
// gcc -O0 -g outrange.c
// valgrind ./a.out
// gcc -O0 -g -DHEAP outrange.c
// valgrind ./a.out
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int foo(int *a, int len) {
  assert((a != 0) && (len > 1));
  return a[len / 2]; /* ORLY? */
}

#if !defined(HEAP)

int main() {
  int a[10] = {0};
  int t = foo(a, 1000);
  printf("%d\n", t);
}

#else // HEAP

int main() {
  int *a = calloc(10, sizeof(int));
  int t = foo(a, 1000);
  printf("%d\n", t);
  free(a);
}

#endif // HEAP