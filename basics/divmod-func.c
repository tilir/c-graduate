//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Simplest function: variant 2. Error processing and assertions.
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void read_input(int *, int *);

int main() {
  int a, b, p, q;
  read_input(&a, &b);
  assert(b != 0);
  p = a / b;
  q = a % b;
  printf("p: %d, q: %d\n", p, q);
  return 0;
}

void read_input(int *pa, int *pb) {
  int nitems;
  printf("input a and b: ");
  nitems = scanf("%d %d", pa, pb);
  if (nitems != 2 || *pb == 0) {
    printf("Wrong input!\n");
    abort();
  }
}
