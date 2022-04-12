//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// ASCII table to the screen
//
//-----------------------------------------------------------------------------

#include "stdio.h"

int main() {
  int c;

  for (c = 0; c < 128; ++c) {
    printf("%c ", (char)c);
    if ((c % 16) == 0)
      printf("\n");
  }
  printf("\n");
}
