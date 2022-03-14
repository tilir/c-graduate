#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  double d = 1.79e+308;
  double infd = 2.0 * d;
  double infdzero = infd * 0.0;
  printf("d: %le\tinfd: %le\tinfdzero: %le\n", d, infd, infdzero);
}

