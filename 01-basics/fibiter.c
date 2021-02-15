#include <stdio.h>

unsigned long long fib (unsigned n) {
  unsigned long long first = 0ull, second = 1ull; int idx;
  if (n == 0) return 0ull;
  for (idx = 2; idx <= n; ++idx) {
    unsigned long long tmp = second;
    second = second + first;
    first = tmp;
  }
  return second;
}

int main () {
  printf("%llu\n", fib(50));
}
