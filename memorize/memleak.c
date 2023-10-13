#include <stdio.h>
#include <stdlib.h>

int *foo(int x, int y) {
  int *res = malloc(sizeof(int));
  *res = x + y;
  printf("%p\n", res);
  return res;
}

int main() {
  int *p = foo(0, 42);
  printf("%d\n", *p); // ok
}
