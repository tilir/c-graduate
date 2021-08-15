//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Euclid algorithm: variant 2. Proper support of signed integers.
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int iabs(int x) { return (x < 0) ? -x : x; }

// Euclidean division: a = qb + r, 0 <= r < |b|
// C-style % operation: a == (a / b) * b + (a % b)
// We need proper euclidean division here
int eu_mod(int x, int y) {
  int r;
  assert(y != 0);
  r = x % y;
  if (r < 0)
    r += iabs(y);
  return r;
}

int gcd(int x, int y) {
  int q;
  assert(y != 0);
  q = eu_mod(x, y);
  if (q == 0)
    return y;
  return gcd(y, q);
}

int main() {
  int x, y, g, res;
  res = scanf("%d%d", &x, &y);
  if (res != 2 || y == 0) {
    printf("%s\n", "Wrong input");
    abort();
  }
  g = gcd(x, y);
  printf("%d\n", g);
  return 0;
}
