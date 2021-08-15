//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Double precision fibonacci. Try n = 90
//
//-----------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long fibd(unsigned n) {
  double phi = (1.0 + sqrt(5.0)) / 2.0;
  double phi2 = (1.0 - sqrt(5.0)) / 2.0;
  return round((pow(phi, n) - pow(phi2, n)) / sqrt(5.0));
}

int main() {
  unsigned x;
  unsigned long long f;
  int res;
  res = scanf("%u", &x);
  if (res != 1) {
    printf("%s\n", "Wrong input");
    abort();
  }
  f = fibd(x);
  printf("%llu\n", f);
  return 0;
}
