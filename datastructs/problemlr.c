#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct list_t {
  struct list_t *next;
  int data;
}; 

struct list_t * reverse(struct list_t *top) {
  // TODO: iterative code here
}

enum {
  NELEMS = 10
};

void print_list(struct list_t *top) {
  while (top) {
    printf("%d ", top->data);
    top = top->next;
  }
  printf("\n");
}

int
main () {
  struct list_t *top = NULL;
  int i;

  // create list with no loop
  for (i = 0; i < NELEMS; ++i) {
    struct list_t *oldtop = top;
    top = (struct list_t *) malloc(sizeof(struct list_t));
    top->data = NELEMS - 1 - i;
    top->next = oldtop;
  }

  print_list(top);
  top = reverse(top); 
  print_list(top);

  while(top) {
    struct list_t *oldtop = top;
    top = top->next;
    free(oldtop);
  }

  return 0;
}

