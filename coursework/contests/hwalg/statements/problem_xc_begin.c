#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_MAX 13

typedef int (*get_hash_t)(const char *s);

int ncollisions(char **strs, int n, get_hash_t f);

int myhash(const char *s) {
  int sum = 0;
  while (*s) {
    sum += *s;
    s += 1;
  }

  return (sum % HASH_MAX);
}

static char *read_word(int *len) {
  char *text;
  int res, n, i;

  res = scanf("%d", len);
  assert(res == 1);

  n = *len;
  assert(n > 0);

  text = (char *)calloc(n + 1, sizeof(char));
  assert(text != NULL);

  res = scanf("%*c");
  (void)res;

  for (i = 0; i < n; ++i) {
    char c;
    res = scanf("%c", &c);
    assert(res == 1);
    text[i] = c;
  }

  return text;
}

int main() {
  char **strs;
  int i, n, res, col;

  res = scanf("%d", &n);
  assert(res == 1);

  strs = calloc(n, sizeof(char *));
  for (i = 0; i < n; ++i) {
    int len;
    strs[i] = read_word(&len);
  }

  col = ncollisions(strs, n, myhash);

  printf("%d\n", col);

  for (i = 0; i < n; ++i)
    free(strs[i]);
  free(strs);
}
