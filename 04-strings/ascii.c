#include "stdio.h"

int
main() {
  int c;

  for (c = 0; c < 255; ++c) {
    printf("%c ", (char)c);
    if ((c % 16) == 0)
      printf("\n");
  }

}

