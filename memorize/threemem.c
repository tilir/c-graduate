#include <stdio.h>
#include <stdlib.h>

int x[100];
int main () {
  int y[100] = {0};
  int *pz = calloc(100, sizeof(int));

  printf("global: %p\n", x);
  printf("local: %p\n", y);
  printf("heap: %p\n", pz);

  free(pz);
  return 0;
}

