#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Poly { 
  unsigned n; 
  unsigned *p; 
};

struct Poly 
mult(struct Poly lhs, struct Poly rhs) {
  struct Poly ret = { rhs.n + lhs.n - 1, NULL };
  ret.p = (unsigned *) calloc(ret.n, sizeof(unsigned));

  // TODO: ret = lhs * rhs 

  return ret;
}

int
main () {
  unsigned c1[4] = {7, 4, 3, 1};
  unsigned *c2 = (unsigned *) malloc(4 * sizeof(unsigned));
  c2[0] = 4; c2[1] = 1; c2[2] = 5; c2[3] = 1;
  
  struct Poly p1 = {4, c1};
  struct Poly p2 = {4, c2};
  struct Poly p3;
  
  p3 = mult(p1, p2);
  
  assert(p3.n == 7);
  
  assert(p3.p[0] == 28);
  assert(p3.p[1] == 23);
  assert(p3.p[2] == 51);
  assert(p3.p[3] == 34);
  assert(p3.p[4] == 20);
  assert(p3.p[5] == 8);
  assert(p3.p[6] == 1);

  free(p2.p);
  free(p3.p);
  return 0;
}
