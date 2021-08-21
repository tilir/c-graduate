//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Algorithm P. Naive primality test, third approach
//
// Testing input is: K s1 s2 ... sk
// Where: K == number of queries
// assume K > 0, si > 1
//
// Try input file:  10 10 11 12 13 14 15 16 17 18 19
// Result shall be:     0  1  0  1  0  0  0  1  0  1
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int is_prime(unsigned n) {
  if ((n == 2) || (n == 3))
    return 1;
  if ((n < 2) || ((n % 2) == 0) || ((n % 3) == 0))
    return 0;
  for (int j = 5; j * j <= n; j += 6)
    if (((n % j) == 0) || ((n % (j + 2)) == 0))
      return 0;
  return 1;
}

int main() {
  int res, nqueries, i;
  res = scanf("%d", &nqueries);
  if (res != 1 || nqueries <= 0) {
    printf("%s\n", "Wrong nqueries");
    abort();
  }

  for (i = 0; i < nqueries; ++i) {
    int num, pr;
    res = scanf("%d", &num);
    if (res != 1 || num < 2) {
      printf("%s\n", "Wrong query");
      abort();
    }
    pr = is_prime(num);
    printf("%d ", pr);
  }
  printf("\n");
}
