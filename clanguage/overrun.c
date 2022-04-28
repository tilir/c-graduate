#include <stdio.h>

int d[16] = {0, 1, 2, 3, 4, 5};

int main() {
  int k, satd = 0, dd;
  
  for (dd = d[k = 0]; k < 16; dd = d[++k])
    satd += (dd < 0 ? -dd : dd);

  printf("%d\n", satd);
}
