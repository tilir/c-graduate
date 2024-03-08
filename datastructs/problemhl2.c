#include <assert.h>
#include <stdio.h>

struct list_t {
  struct list_t *next;
  int data;
}; 

int loop_len(struct list_t *top) {
  // TODO: your code here
}

enum {
  NELEMS = 10
};

int
main () {
  struct list_t elems[NELEMS] = {{0,0}};
  int i;

  // list with no loop
  for (i = 1; i < NELEMS; ++i)
    elems[i-1].next = &elems[i];

  assert(0 == loop_len(&elems[0]));

  // create loop
  elems[NELEMS-1].next = &elems[3];

  assert(7 == loop_len(&elems[0]));

  return 0;
}

