#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tree_t {
  struct tree_t *left, *right;
  int data;
};

// Knuth, 7.2.1.6.W
unsigned long long bitstring(int n) {
  int p = n / 2, q = n / 2, m = 1;
  unsigned long long res = 0;

  assert ((n % 2) == 0);

  while (q != 0) {
    for (;;) {
      int x = rand() % ((q + p) * (q - p + 1));
      assert(q + p == n - m + 1);
      if (x < (q + 1) * (q - p)) {
        q -= 1;
        assert((res & (1ull << (m - 1))) == 0);
        m += 1;
        break;
      }
      p -= 1;
      res |= (1ull << (m - 1));
      m += 1;
    }    
  }
 
  return res;
}

void do_shuffle(int *array, int n) {
  size_t i;
  assert (n > 1);
  for (i = 0; i < n - 1; i++) {
    size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
    int t = array[j];
    array[j] = array[i];
    array[i] = t;
  }
}

struct tree_t *
rec_decode_tree(unsigned long long bitstring, int n, int *resdata, 
                int *cnt, int *rescnt) {
  struct tree_t *res;
  int oldval = *cnt;
  
  if (oldval == n)
    return NULL;

  *cnt += 1;
  
  if (0 == (bitstring & (1ull << oldval)))
    return NULL;

  res = (struct tree_t *) calloc(1, sizeof(struct tree_t));  
  res->left = rec_decode_tree(bitstring, n, resdata, cnt, rescnt);
  res->data = resdata[*rescnt];
  *rescnt += 1;
  res->right = rec_decode_tree(bitstring, n, resdata, cnt, rescnt);
  return res;
}

struct tree_t *
decode_tree(unsigned long long bitstring, int n, int *resdata) {
  struct tree_t *ret;
  int cnt = 0, rescnt = 0;
  ret = rec_decode_tree(bitstring, n, resdata, &cnt, &rescnt);
  return ret;
}

void
rec_print_tree(struct tree_t *t) {
  if (t == NULL) return;
  if (t->left == NULL && t->right == NULL) return;
  
  printf("%d ", t->data);
  printf("%d ", (t->left != NULL) ? t->left->data : -1);
  printf("%d\n", (t->right != NULL) ? t->right->data : -1);
  
  rec_print_tree(t->left);
  rec_print_tree(t->right);
}

void free_tree(struct tree_t *t) {
  if (t == NULL) return;
  free_tree(t->left);
  free_tree(t->right);
  free(t);
}

void
do_generate(unsigned long long bitstring, int n) {
  struct tree_t *rest;
  int i, *resdata, *linearized;
  
  resdata = (int *) calloc(n, sizeof(int));
  assert(resdata);

  for (i = 0; i < n; ++i)
    resdata[i] = i;

  // roll a dice to 1/2 non-search tree prob
  if (rand() % 2) 
    do_shuffle(resdata, n);

  rest = decode_tree(bitstring, n*2, resdata);

  printf("%d\n", n);
  rec_print_tree(rest);

  free(resdata);
  free_tree(rest);
}

const int NDEFAULT = 32;

int
main (int argc, char **argv) {
  unsigned long long res;
  int n = NDEFAULT;
  int l = n * 2;
  
  if (argc > 1) {
    n = strtod(argv[1], NULL);
    assert(n > 1);
    assert(n <= NDEFAULT);
    l = n * 2;
  }

  srand(time(NULL));
  res = bitstring(l);
  assert ((res & 1) != 0); 
  do_generate(res, n);
}

