#include <stdio.h>
#include <stdlib.h>

int *foo(int x, int y) {
  int res = x + y;
  printf("%p\n", &res);
  return &res;
}

int main() {
  int *p = foo(0, 42);
  #if 0
    printf("%d\n", *p); // oops
  #endif
}

