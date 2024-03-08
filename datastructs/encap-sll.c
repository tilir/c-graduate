#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "encap-sll.h"

struct list_t {
  struct list_t *next;
  int data;
}; 

// create single-element list
struct list_t *list_create_elt(int d) {
  struct list_t *top;
  top = (struct list_t *) malloc(sizeof(struct list_t));
  top->next = NULL;
  top->data = d;
  return top;
}

// create list with elements from s to f
struct list_t *list_create_diap(int s, int f) {
  struct list_t *top = NULL;
  while (f >= s) {
    struct list_t *oldtop = top;
    top = list_create_elt(f);
    top->next = oldtop;
    f -= 1;
  }
  return top;
}

// get value at given node
int list_value(struct list_t * lst) {
  assert(lst);
  return lst->data;
}

// next node
struct list_t *list_next(struct list_t * lst) {
  assert(lst);
  return lst->next;
}

// insert after given node
struct list_t *list_insert_after(struct list_t * pre, int d) {
  struct list_t *newelem;
  assert(pre);
  newelem = list_create_elt(d);
  newelem->next = pre->next;
  pre->next = newelem;
  return newelem;
}

// remove node after given, i.e. 
// pre->next will be equal to pre->next->next after operation
struct list_t *list_pop(struct list_t * pre) {
  assert(pre && pre->next);
  struct list_t *oldelem = pre->next;
  pre->next = pre->next->next;
  free(oldelem);
  return pre;
}

// print list
void list_print(struct list_t * top) {
  while (top) {
    printf("%d ", top->data);
    top = top->next;
  }
  printf("\n");
}

// free list
void list_free(struct list_t * top) {
  while(top) {
    struct list_t *oldtop = top;
    top = top->next;
    free(oldtop);
  }
}

