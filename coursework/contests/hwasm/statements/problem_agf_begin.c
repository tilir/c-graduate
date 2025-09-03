#include <stdio.h>

int foo(int x, int y);

int main() {
  int x, y, z;
  scanf("%d", &x);
  y = 0;
  z = foo(x, y);
  printf("%d\n", z);
}
