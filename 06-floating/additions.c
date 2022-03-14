#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int i;
  double h, cosval;

  for (i = 1; i < 20; ++i) {
    h = pow(10.0, -i);
    cosval = (sin(1.0 + h) - sin(1.0)) / h;
    printf("%d:\t%.15lf\n", i, cosval);
  }

  cosval = cos(1.0);
  printf("True result: %.15lf\n", cosval);
}

