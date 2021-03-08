#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct tree_t {
  struct tree_t *left, *right;
  int data;
};

FILE *fexpr, *flexed, *fval;

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

static struct tree_t *
rec_decode_tree(unsigned long long bitstring, int n, int *resdata, 
                int *cnt, int *rescnt) {
  struct tree_t *res;
  int oldval;

  assert(cnt != NULL && resdata != NULL && rescnt != NULL);
  oldval = *cnt;
  
  if (oldval == n)
    return NULL;

  *cnt += 1;
  
  if (0 == (bitstring & (1ull << oldval)))
    return NULL;

  res = (struct tree_t *) calloc(1, sizeof(struct tree_t));
  assert(res != NULL);
  
  res->left = rec_decode_tree(bitstring, n, resdata, cnt, rescnt);
  res->data = resdata[*rescnt];
  *rescnt += 1;
  res->right = rec_decode_tree(bitstring, n, resdata, cnt, rescnt);
  return res;
}

static struct tree_t *
decode_tree(unsigned long long bitstring, int n, int *resdata) {
  struct tree_t *ret;
  int cnt = 0, rescnt = 0;
  ret = rec_decode_tree(bitstring, n, resdata, &cnt, &rescnt);
  return ret;
}

static void
print_num(int n) {
  fprintf(fexpr, "%d", n);
  fprintf(flexed, " NUMBER:%d", n);
}

static void
print_brace(int opcode) {
  switch(opcode) {
    case 0: 
      fprintf(fexpr, "(");
      fprintf(flexed, " LBRAC");
      break;
    case 1: 
      fprintf(fexpr, ")");
      fprintf(flexed, " RBRAC");
      break;
    default:
      assert(0 && "unknown bracket");
  }
}
 
static void
print_op(int opcode) {
  switch(opcode) {
    case 0: 
      fprintf(fexpr, " + ");
      fprintf(flexed, " PLUS");
      break;
    case 1: 
      fprintf(fexpr, " - ");
      fprintf(flexed, " MINUS");
      break;
    case 2:
      fprintf(fexpr, " * ");
      fprintf(flexed, " MUL");
      break;
    case 3:
      fprintf(fexpr, " / ");
      fprintf(flexed, " DIV");
      break;
    default:
      assert(0 && "unknown opcode");
  }
}

static inline int iabs(int x) {
  return (x > 0) ? x : -x;
}

static inline int isgn(int x) {
  return (x > 0) ? x : -x;
}

static int
rec_print_tree(struct tree_t *t) {
  int opcode, leftval, rightval;

  // number on leaf
  if (t == NULL) {
    leftval = rand() % 99 + 1;
    print_num(leftval);
    return leftval;
  }

  // roll die: +, -, *, /
  // if + or -, then also braces
  opcode = rand() % 4;

  if (opcode < 2) print_brace(0);

  leftval = rec_print_tree(t->left);

  print_op(opcode);

  rightval = rec_print_tree(t->right);
  if (opcode < 2) print_brace(1);

  switch(opcode) {
    case 1: rightval = -rightval; // fall through
    case 0: {
      if ((isgn(rightval) == isgn(leftval)) &&
          (iabs(leftval) > INT_MAX - iabs(rightval))) {
        printf("Sorry, integer overflow happened. Please re-run\n");
        abort();
      }        
      return leftval + rightval;
    }
    case 2: {
      if ((rightval != 0) &&
          (iabs(leftval) > INT_MAX / iabs(rightval))) {
        printf("Sorry, integer overflow happened. Please re-run\n");
        abort();
      }
      return leftval * rightval;
    }
    case 3: 
      if (rightval == 0) {
        printf("Sorry, division by zero happened. Please re-run\n");
        abort();        
      }
      else
        return leftval / rightval;
    default: break;
  }

  assert(0 && "Unknown op");
  __builtin_unreachable();
}

static void
free_tree(struct tree_t *t) {
  if (t == NULL) return;
  free_tree(t->left);
  free_tree(t->right);
  free(t);
}

static void
do_generate(unsigned long long bitstring, int n) {
  struct tree_t *rest;
  int res, i, *resdata;
  
  resdata = (int *) calloc(n, sizeof(int));
  assert(resdata != NULL);

  for (i = 0; i < n; ++i)
    resdata[i] = i;

  rest = decode_tree(bitstring, n*2, resdata);

  res = rec_print_tree(rest);
  fprintf(fexpr, "\n");
  fprintf(flexed, "\n");
  fprintf(fval, "%d\n", res);

  free(resdata);
  free_tree(rest);
}

const int NDEFAULT = 32;

int
main (int argc, char **argv) {
  unsigned long long res;
  int n = NDEFAULT;
  int l = n * 2;
  const char *fmod = "001";
  char exprname[100], lexname[100], valname[100];
  
  if (argc > 1) {
    n = strtod(argv[1], NULL);
    assert(n > 1);
    assert(n <= NDEFAULT);
    l = n * 2;
  }

  if (argc > 2) {
    fmod = argv[2];
    assert(strlen(fmod) < 90);
  }

  sprintf(exprname, "%s.expr", fmod);
  sprintf(lexname, "%s.lex", fmod);
  sprintf(valname, "%s.val", fmod);

  srand(time(NULL));
  res = bitstring(l);
  assert ((res & 1) != 0);

  flexed = fopen(lexname, "w");
  fval = fopen(valname, "w");
  fexpr = fopen(exprname, "w");
 
  assert(flexed != NULL);
  assert(fval != NULL);
  assert(fexpr != NULL);

  do_generate(res, n);

  fclose(fexpr);
  fclose(fval);
  fclose(flexed);
}

