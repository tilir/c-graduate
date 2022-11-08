//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Simple segfault example to demonstrate how gdb and valgrind helps us
//
// Try:
// > gcc -g buggy-sieve.c -lm
// > a.out
// > valgrind ./a.out
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
  int n;
  char *s;
};

int sieve_bound(int num) {
  double dnum, dres;
  if (num <= 20)
    return 100;
  dnum = num;
  dres = dnum * (log(dnum) + log(log(dnum)));
  return (int)round(dres);
}

void fill_sieve(struct sieve_t *s);
int nth_prime(struct sieve_t *s, int N);

int main() {
  int n, outp;
  int res;
  struct sieve_t sieve;

  res = scanf("%d", &n);
  assert(res == 1);  
  
  sieve.n = sieve_bound(n);
  sieve.s = (char *)calloc(sieve.n, sizeof(char));
  assert(sieve.s != NULL);

  fill_sieve(&sieve);
  outp = nth_prime(&sieve, n);

  printf("%d\n", outp);

  free(sieve.s);  
}

void fill_sieve(struct sieve_t *sv) {
  int n = 0;
  int m = 0;
  sv->s[0] = 1;
  sv->s[1] = 1;
  for (n = 2; n < (sv->n); ++n) {
    if (sv->s[n] == 0)
      for (m = n * n; m < (sv->n); m += n)
        sv->s[m] = 1;
  }
}

int nth_prime(struct sieve_t *sv, int n) {
  int i = 0;

  int count_prime = 0;
  for (i = 0; count_prime < n; ++i) {
    if (!(sv->s[i]))
      ++count_prime;
  }
  return i - 1;
}