#include <stdio.h>

int main() {
  unsigned mask = 0x69;
  unsigned x = 1;
  while (x != 0) {
    printf("0x%x\n", x);
    x = (x - mask) & mask;
  }
}
