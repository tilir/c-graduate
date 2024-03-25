//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// fact combined with main
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int fact(int x);

#if 0
int fact(int x) {
  if (x < 2) return x;
  return fact(x - 1) * x;
}
#endif

int main() {
  int f = fact(5);
  printf("%d\n", f);
}

