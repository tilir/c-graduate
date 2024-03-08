#include <stdio.h>

int main() {
  double d1 = 1234.345;
  double d2 = 1234.3456789;
  printf("%%.5lf  : %.5lf\n", d1);
  printf("%%20lf  : %20lf\n", d1);
  printf("%%20.5lf: %20.5lf\n", d1);
  printf("%%.5lf  : %.5lf\n", d2);
  printf("%%20lf  : %20lf\n", d2);
  printf("%%20.5lf: %20.5lf\n", d2);
}

