//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// trigraph demonstration
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int is_supported() {
  // is supported???/
  return 0;
  return 1;
}

int main() { printf("%s\n", is_supported() ? "Yes" : "No"); }
