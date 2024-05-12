#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct triple {
  int x, y, z;
};

int tcmp(void const *key, void const *elt) {
  struct triple const *lhs = (struct triple const *)key;
  struct triple const *rhs = (struct triple const *)elt;
  if (lhs->x == rhs->x && lhs->y == rhs->y)
    return (lhs->z < rhs->z);
  if (lhs->x == rhs->x)
    return (lhs->y < rhs->y);
  return (lhs->x < rhs->x);
}

typedef int (*cmp_t)(const void *lhs, const void *rhs);

int selstep(void *parr, int eltsize, int n, int last, cmp_t cmp);

int main() {
  int i, res, n, last;
  struct triple *parr;

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 2);

  parr = (struct triple *)calloc(n / 3, sizeof(struct triple));

  for (i = 0; i < n / 3; ++i) {
    res = scanf("%d %d %d", &parr[i].x, &parr[i].y, &parr[i].z);
    assert(res == 3);
  }

  res = scanf("%d", &last);
  assert(res == 1);
  assert(last < n);

  selstep(parr, sizeof(struct triple), n / 3, last / 3, &tcmp);

  for (i = 0; i < n / 3; ++i)
    printf("%d %d %d\n", parr[i].x, parr[i].y, parr[i].z);

  free(parr);
  return 0;
}
