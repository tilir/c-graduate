#include <assert.h>
#include <math.h>
#include <stdio.h>

int is_prime_1(unsigned n) {
  if (n < 2) return 0;
  unsigned last = (unsigned) sqrt(n) + 1;
  for (unsigned j = 2; j < last; ++j)
    if ((n % j) == 0)
      return 0;
  return 1;
}

int is_prime_2(unsigned n) {
  if (n == 2) return 1;
  if ((n < 2) || ((n % 2) == 0)) return 0;
  unsigned last = (unsigned) sqrt(n) + 1;
  for (unsigned j = 3; j < last; j += 2)
    if ((n % j) == 0)
      return 0;
  return 1;
}

int is_prime(unsigned n) {
  if ((n == 2) || (n == 3)) 
    return 1;
  if ((n < 2) || ((n % 2) == 0) || ((n % 3) == 0)) 
    return 0;
  unsigned last = (unsigned) sqrt(n) + 1;
  for (int j = 5; j < last; j += 6)
    if (((n % j) == 0) || ((n % (j + 2)) == 0))
      return 0;
  return 1;
}

int
main() {
  unsigned n;
  int nitems, res;

  // some self-check
  for (n = 2; n < 100; ++n) {
    res = is_prime_1(n);
    assert(res == is_prime_2(n));
    assert(res == is_prime(n));
  }

  printf("Input number: ");
  nitems = scanf("%u", &n);
  assert(nitems == 1);

  res = is_prime(n);

  printf("This number is %s\n", 
         res ? "prime" : "non prime");
}

