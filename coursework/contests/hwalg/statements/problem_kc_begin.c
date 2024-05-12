#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned R = 10u;
const unsigned Q = 31u;

int rabin_karp(const char *needle, const char *haystack);

// say hash(c1, c2, c3) = c1*r^2 + c2*r + c3
//                      = ((c1 * r + c2) * r) + c3
unsigned get_hash(const char *pat, const char *end) {
  unsigned p = 0;
  for (; pat != end; ++pat)
    p = (p * R + *pat) % Q;
  return p;
}

// (c1*r^2 + c2*r + c3 - c1*r^2) * r + c4
unsigned update_hash(unsigned hash, unsigned n, char cf, char cl) {
  unsigned nf = (cf * n) % Q;
  if (hash < nf)
    hash += Q;
  hash = ((hash - nf) * R + cl) % Q;
  return hash;
}

unsigned long long pow_mod(unsigned n, unsigned k, unsigned m) {
  unsigned long long mult, prod;
  if (n == 0 || n == 1 || k == 1)
    return n;
  if (k == 0)
    return 1;
  mult = n;
  prod = 1;
  while (k > 0) {
    if ((k % 2) == 1)
      prod = (prod * mult) % m;
    mult = (mult * mult) % m;
    k = k / 2;
  }
  return prod;
}

static char *read_word(int *len) {
  char *text;
  int res, n, i;

  res = scanf("%d", len);
  assert(res == 1);

  n = *len;
  assert(n > 0);

  text = (char *)calloc(n + 1, sizeof(char));
  assert(text != NULL);

  res = scanf("%*c");
  (void)res;

  for (i = 0; i < n; ++i) {
    char c;
    res = scanf("%c", &c);
    assert(res == 1);
    text[i] = c;
  }

  return text;
}

int main() {
  int nlen, hlen, count = 0;
  char *needle, *haystack, *sres;

  haystack = read_word(&hlen);
  needle = read_word(&nlen);

  sres = haystack;
  for (;;) {
    int pos = rabin_karp(needle, sres);
    if (pos == -1)
      break;
    count += 1;
    sres += (pos + nlen);
  }

  printf("%d\n", count);

  free(haystack);
  free(needle);
}
