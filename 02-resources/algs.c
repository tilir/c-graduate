#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
  unsigned size;
  unsigned char *sieve;
};

// 1 если составное
int is_composite(struct sieve_t s, int i) {
  int nbyte = i / 8;
  int nbit = i % 8;
  return (s.sieve[nbyte] >> nbit) & 1;
}

void set_composite(struct sieve_t s, int i) {
  int nbyte = i / 8;
  int nbit = i % 8;
  s.sieve[nbyte] = s.sieve[nbyte] | (1u << nbit);
}

struct sieve_t 
init_sieve (unsigned n) 
{
  struct sieve_t res;
  int i, j;
  unsigned char *sieve;
  assert(n > 2);
  sieve = calloc(n, sizeof(unsigned char));
  res.size = n;
  res.sieve = sieve;
  assert ((n > 1) && (sieve != NULL));
  unsigned r = (unsigned) sqrt (n) + 1;
  res.sieve[0] = 0x3;
  for (i = 2; i < r; ++i) {
    // если число составное
    if (is_composite(res_sieve, i)) 
      continue;
    for (j = i * i; j < n; j += i)
      set_composite(res_sieve, i);
  }

  return res;
}

void 
free_sieve(struct sieve_t *s) 
{
  free(s->sieve);
  s->sieve = 0;
  s->size = 0;
}

int
is_prime (struct sieve_t s, unsigned n) {
  assert (n < s.size);
  return (s.sieve[n] == 1) ? 0 : 1;
}

int
main ()
{
  struct sieve_t s = init_sieve(100);
  assert (is_prime(s, 96) == 0);
  assert (is_prime(s, 97) == 1);
  free_sieve(&s);
}

