#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  float f, nextf, fone, feps, fenext;
  double d, nextd;

  f = 16777216.0f; // 2^24
  nextf = f + 1.0f;

  fone = 1.0f;
  feps = FLT_EPSILON;
  fenext = fone + feps;

  d = 9007199254740992.0; // 2^53
  nextd = d + 1.0;

  printf("f: %8.0lf\t\tnextf: %8.0lf\n", f, nextf);
  printf("feps: %.8f\tfenext: %.8f\n", feps, fenext);
  printf("d: %16.0lf\tnextd: %16.0lf\n", d, nextd);
}

