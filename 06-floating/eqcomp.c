#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int res;
  double d1, d2, d3;
  res = fscanf(stdin, "%lf", &d1);
  assert(res == 1);
  d2 = sqrt(d1);
  d3 = d2 * d2;
  if (d1 != d3)
    printf("d1 (%.15lf) != d3 (%.15lf)\n", d1, d3);
}
