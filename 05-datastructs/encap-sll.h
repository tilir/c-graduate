#pragma once

struct list_t;

// create single-element list
struct list_t *list_create_elt(int d);

// create list with elements from s to f
struct list_t *list_create_diap(int s, int f);

// get value at given node
int list_value(struct list_t * lst);

// next node
struct list_t *list_next(struct list_t * lst);

// insert after given node
struct list_t *list_insert_after(struct list_t * pre, int d);

// remove node after given, i.e. pre->next will be equal to pre->next->next after operation
struct list_t *list_pop(struct list_t * pre);

// print list
void list_print(struct list_t * top);

// free list
void list_free(struct list_t * top);

