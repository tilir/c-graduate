#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_t {
  struct node_t *next;
  int data;
};

struct node_t *read_list(FILE *inp);
void delete_list(struct node_t *top);

int main() {
  struct node_t *top = read_list(stdin);
  struct node_t *cur = top;

  while (cur) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
  printf("\n");

  delete_list(top);
}
