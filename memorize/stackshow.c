#include <stdio.h>
#include <stdlib.h>

int foo (int x, int y) {
  int res = x + y;
  printf("foo frame: %p\n", &res);
  return res;
}

int bar (int x) {
  int res = foo (x, x * 2);
  printf("bar frame: %p\n", &res);
  return res;
}

int main() {
  int res = bar(3);
  printf("main frame: %p\n", &res);
  return res;
}

