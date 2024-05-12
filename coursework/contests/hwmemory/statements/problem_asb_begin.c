#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arrpopcount(const unsigned char *parr, int len);

int main() {
  int res, answ, n, i;
  unsigned char *parr;

  res = scanf("%d", &n);
  assert(res == 1);
  assert(n > 0);

  parr = calloc(n, sizeof(unsigned char));

  for (i = 0; i < n; ++i) {
    res = scanf("%hhd", parr + i);
    assert(res == 1);
  }

  answ = arrpopcount(parr, n);

  printf("%d\n", answ);

  free(parr);
}
