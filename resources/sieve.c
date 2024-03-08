//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Algorithm S. Template to write your code.
//
// Testing input is: N K s1 s2 ... sk
// Where: N == sieve size, K == number of queries
// assume N > 2, K > 0, 1 < si < N
//
// Try input file: 100 10 10 11 12 13 14 15 16 17 18 19
// Result shall be:        0  1  0  1  0  0  0  1  0  1
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
  unsigned size;
  unsigned char *sieve;
};

struct sieve_t init_sieve(unsigned n) {
  struct sieve_t res;
  int i, j;
  unsigned char *sieve;
  assert(n > 2);
  sieve = calloc(n, sizeof(unsigned char));
  res.size = n;
  res.sieve = sieve;
  assert((n > 1) && (sieve != NULL));
  unsigned r = (unsigned)sqrt(n) + 1;

  // TODO: your code here
  // initially sieves have all zeros
  // set one for all composite numbers

  return res;
}

void free_sieve(struct sieve_t *s) {
  free(s->sieve);
  s->sieve = 0;
  s->size = 0;
}

int is_prime(struct sieve_t s, unsigned n) {
  assert(n < s.size);
  return (s.sieve[n] == 1) ? 0 : 1;
}

int main() {
  int res, size, nqueries, i;
  res = scanf("%d%d", &size, &nqueries);
  if (res != 2 || size <= 2 || nqueries <= 0) {
    printf("%s\n", "Wrong size or nqueries");
    abort();
  }

  struct sieve_t s = init_sieve(size);

  for (i = 0; i < nqueries; ++i) {
    int num, pr;
    res = scanf("%d", &num);
    if (res != 1 || num >= size || num < 2) {
      printf("%s\n", "Wrong query");
      abort();
    }
    pr = is_prime(s, num);
    printf("%d ", pr);
  }
  printf("\n");

  free_sieve(&s);
}
