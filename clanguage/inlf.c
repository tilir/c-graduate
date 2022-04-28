#include <stdio.h>
#include <stdlib.h>

inline void my_assert(int b, const char *str) {
  if (!b) return;
  fprintf(stderr, "Assertion failed: %s\n", str);
  exit(-1);
}

int main(int argc, char **argv) {
  my_assert(argc > 0, "argc <= 0");
  return 0;
}
