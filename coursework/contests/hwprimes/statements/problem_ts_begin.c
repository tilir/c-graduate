#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point_t {
  int x, y;
};

struct triangle_t {
  struct point_t pts[3];
};

int double_area(struct triangle_t tr);

int main() {
  int res;
  struct triangle_t tr;

  res = scanf("%d%d%d%d%d%d", &tr.pts[0].x, &tr.pts[0].y, &tr.pts[1].x, &tr.pts[1].y, &tr.pts[2].x, &tr.pts[2].y);
  assert(res == 6);
  res = double_area(tr);
  printf("%d\n", res);
}

#line 10000
