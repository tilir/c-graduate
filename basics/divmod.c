//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Simplest function: variant 1. Find problems in this code!
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int main() {
  int a, b, p, q;
  printf("input a and b: ");
  scanf("%d %d", &a, &b);
  p = a / b;
  q = a % b;
  printf("p = %d, q = %d\n", p, q);
  return 0;
}
