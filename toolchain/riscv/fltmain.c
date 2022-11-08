//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Float ABI with main function
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int fto_int(float f) {
  return f;
}

int main() {
  printf("%d\n", fto_int(1.99f));
  printf("%d\n", fto_int(1.09f));
  printf("%d\n", fto_int(1.5f));
}
