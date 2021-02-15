#include <assert.h>
#include <stdio.h>

int print_converted(unsigned n, unsigned base) {
  assert (base > 1);
  while (n > 0) {
    printf("%d", n % base);
    n = n / base;
  }
}

int main () {
  print_converted(12623, 4);
  printf("\n");
}