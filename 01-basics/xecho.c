#include <assert.h>
#include <stdio.h>

int main() {
  int x, res;
  res = scanf("%d", &x);
  assert(res == 1);
  printf("%d\n", x);
}
