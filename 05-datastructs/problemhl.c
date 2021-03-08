#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct list_t {
  struct list_t *next;
  int data;
}; 

int list_is_a_loop(struct list_t *top) {
  // TODO: your code here
}

enum {
  NELEMS = 10
};

int
main () {
  struct list_t *top = NULL, *last = NULL;
  int i;

  // create list with no loop
  for (i = 0; i < NELEMS; ++i) {
    struct list_t *oldtop = top;
    top = (struct list_t *) malloc(sizeof(struct list_t));
    top->data = NELEMS - 1 - i;
    top->next = oldtop;
    if (i == 0)
      last = top;
  }

  assert(0 == list_is_a_loop(top));

  // create loop
  last->next = top->next->next->next;

  assert(1 == list_is_a_loop(top));

  // undo loop
  last->next = NULL;

  // free memory
  while(top) {
    struct list_t *oldtop = top;
    top = top->next;
    free(oldtop);
  }

  return 0;
}

