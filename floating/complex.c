#include <complex.h>
#include <stdio.h>

int main() {
  complex double a, b, c;

  a = CMPLX(0.0, 1.0);
  b = CMPLX(0.0, 1.0);
  c = cpow(a, b);
  printf("%lf + %lf * i\n", creal(c), cimag(c));
}
