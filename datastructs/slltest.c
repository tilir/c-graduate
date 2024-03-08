#include "encap-sll.h"

int
main () {
  struct list_t *lst, *tmp;
  lst = list_create_diap(0, 20);
  list_print(lst);
  tmp = list_next(lst);
  list_pop(tmp);
  list_insert_after(tmp, 21);
  list_print(lst);
  return 0;
}

