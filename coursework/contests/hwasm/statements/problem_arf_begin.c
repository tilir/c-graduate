#include <stdio.h>

long foo(unsigned x);

int main() {
  unsigned x;
  long z;
  scanf("%u", &x);
  z = foo(x);
  printf("%ld\n", z);
}
