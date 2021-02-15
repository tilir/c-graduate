#include <stdio.h>

unsigned long long fib (unsigned n) {
  if (n == 0) return 0ull;
  if (n <= 2) return 1ull;
  return fib(n - 1) + fib(n - 2);
}

int main () {
  printf("%d\n", fib(50));
}
