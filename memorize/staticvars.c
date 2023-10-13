#include <stdio.h>
#include <stdlib.h>

int foo() {
  static int x = 0; // время жизни: всегда
  x += 1;
  printf("%d\n", x);
}

int main() {
  foo(); // на экране 1
  foo(); // на экране 2
  foo(); // на экране 3
}

