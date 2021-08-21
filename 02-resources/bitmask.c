//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Test for K&R glorious bit hack
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int main() {
  unsigned mask = 0x69;
  unsigned x = 1;
  while (x != 0) {
    printf("0x%x\n", x);
    x = (x - mask) & mask;
  }
}
