#include <assert.h>
#include <stdio.h>

int gcd(int x, int y) {
  assert((x > y) && (y > 0));
  int q = x % y;
  if (q == 0)
    return y;
  return gcd(y, q);
}

int main() {
  printf("%d\n", gcd(1769, 427));
}