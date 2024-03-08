#include <assert.h>
#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main() {
  unsigned u, res, v;
  float f, d, n; 

  fesetround(FE_DOWNWARD);

  res = fscanf(stdin, "%f", &d);
  assert(res == 1);

  f = 1.0f / d;
  n = nextafterf(f, f + 1);

  memcpy(&u, &f, sizeof(unsigned));
  memcpy(&v, &n, sizeof(unsigned));

  printf("%x\n", u);
  printf("%#08x\n", v);
}

