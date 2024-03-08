#include <assert.h>
#include <stdio.h>
#include <string.h>

#if !defined(SIMPLE)
const unsigned R = 256u;
const unsigned Q = 7919u;
#else
const unsigned R = 10u;
const unsigned Q = 31u;
#endif

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

// алгоритм POWM: n^k % m
unsigned long long pow_mod (unsigned n, unsigned k, unsigned m) {
  unsigned long long mult, prod;
  if (n == 0 || n == 1 || k == 1) return n;
  if (k == 0) return 1;
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

int rabin_karp(const char *needle, const char *haystack) {
  unsigned n, target, cur, count = 0, left = 0, right;
  right = strlen(needle);
  target = get_hash(needle, needle + right);
  cur = get_hash(haystack, haystack + right);
  n = pow_mod(R, right - 1, Q);
  while(target != cur && haystack[right] != 0) {
    cur = update_hash(cur, n, haystack[left], haystack[right]);
    left += 1; right += 1;
  }
  return (target == cur) ? left : -1;
}

int
main() {
  unsigned h1, h2, n, fin, res;  
  const char * str1 = "ABC";
  const char * str2 = "BCD";
  const char * haystack = "ABCDEFGHAHBHCHDHEGHJABCB";
  const char * needle = "HJ";
  h1 = get_hash(str1, str1 + 3);
  h2 = get_hash(str2, str2 + 3);
  n = pow_mod(R, 2, Q);
  printf("h(ABC) = %d, h(BCD) = %d\n", h1, h2);
  h1 = update_hash(h1, n, 'A', 'D');
  assert(h1 == h2 && "Hashes shall be equal after update");
  
  res = rabin_karp(needle, haystack);
  printf("RK found: %d\n", res);
}
