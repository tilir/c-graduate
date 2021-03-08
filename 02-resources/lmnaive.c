#include <assert.h>
#include <stdio.h>

unsigned long long
least_all_multiples_upto(unsigned n) {
  unsigned long long res = n;
  for(;;) {
    unsigned all_ok = 1;
    for (unsigned k = 2; k < n; ++k)
      if ((res % k) != 0) {
        all_ok = 0;
        break;
      }
    if (all_ok)
      break;
    res += 1;
  }
  return res;
}

int
main() {
  unsigned long long ulm10 = least_all_multiples_upto(10);
  printf ("%d\n", ulm10);
  unsigned long long ulm20 = least_all_multiples_upto(20);
  printf ("%d\n", ulm20);
  unsigned long long ulm25 = least_all_multiples_upto(25);
  printf ("%d\n", ulm25);
}

