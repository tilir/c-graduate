#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct tree_t {
  struct tree_t *left, *right;
  int data;
};

// subroutine for read_tree
// return head node
struct tree_t * 
read_tree_structure(struct tree_t **nodes, int n) {
  int i;
  struct tree_t *head = NULL;
  int *nodemarks;
  
  assert(nodes != NULL);

  nodemarks = (int *) calloc(n, sizeof(int));
  assert(nodemarks != NULL);    
  
  for (;;) {
    int res, parent, left, right;

    res = scanf("%d %d %d", &parent, &left, &right);
    if (res != 3)
      break;
    
    assert(parent >= 0);
    assert(parent < n && left < n && right < n);
    nodemarks[parent] += 1;
    if (left != -1) {
      nodes[parent]->left = nodes[left];
      nodemarks[left] -= 1;
    }
    if (right != -1) {
      nodes[parent]->right = nodes[right];
      nodemarks[right] -= 1;
    }
  }
  
  for (i = 0; i < n; ++i)
    if (nodemarks[i] > 0) {
      assert(head == NULL);
      head = nodes[i];
    }   
 
  free(nodemarks);  
  return head;
}

struct tree_t *read_tree() {
  int res, i, n;
  struct tree_t *head = NULL;
  struct tree_t **nodes;

  res = scanf("%d", &n);
  assert(res == 1);

  nodes = (struct tree_t **) calloc(n, sizeof(struct tree_t*));
  assert(nodes != NULL);

  for (i = 0; i < n; ++i) {
    nodes[i] = (struct tree_t *) calloc(1, sizeof(struct tree_t));
    assert(nodes[i] != NULL);
    nodes[i]->data = i;
  }
  
  head = read_tree_structure(nodes, n);

  free(nodes);
  assert(head != NULL);
  return head;
}

void out_nest(FILE *f, int nest) {
  while (nest-->0) {
    fprintf(f, " ");    
  }
}

void pretty_print_tree(FILE *f, struct tree_t *t, int nest) {
  if (t == NULL) return;
  out_nest(f, nest);
  fprintf(f, "%d\n", t->data);
  pretty_print_tree(f, t->left, nest + 2);
  pretty_print_tree(f, t->right, nest + 2);
}

void free_tree(struct tree_t *t) {
  if (t == NULL) return;
  free_tree(t->left);
  free_tree(t->right);
  free(t);
}

void print_preorder(struct tree_t *t) {
  if (t == NULL) return;
  printf("%d ", t->data);
  print_preorder(t->left);
  print_preorder(t->right);
}

void print_inorder(struct tree_t *t) {
  if (t == NULL) return;
  print_inorder(t->left);
  printf("%d ", t->data);
  print_inorder(t->right);
}

void print_postorder(struct tree_t *t) {
  if (t == NULL) return;
  print_postorder(t->left);
  print_postorder(t->right);
  printf("%d ", t->data);
}

int
main () {
  struct tree_t *t = read_tree();
  pretty_print_tree(stdout, t, 0);
  print_preorder(t); printf("\n");
  print_inorder(t); printf("\n");
  print_postorder(t); printf("\n");
  free_tree(t); 
}

