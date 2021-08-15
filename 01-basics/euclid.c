#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int gcd(int x, int y) {
  int q;
  assert(y != 0);
  q = x % y;
  if (q == 0)
    return y;
  return gcd(y, q);
}

int main() {
  int x, y, g, res;
  res = scanf("%d%d", &x, &y);
  if (res != 2 || y == 0) {
    printf("%s\n", "Wrong input");
    abort();
  }
  g = gcd(x, y);
  printf("gcd(%d, %d) = %d\n", x, y, g);
  return 0;
}
