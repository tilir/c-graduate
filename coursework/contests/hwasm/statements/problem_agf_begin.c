#include <stdio.h>

int foo(int x, int y);

int main() {
  int x, y, z;
  scanf("%d%d", &x, &y);
  z = foo(x, y);
  printf("%d\n", z);
}
