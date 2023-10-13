#include <stdio.h>
#include <stdlib.h>

const int MAXCNT = 1000;
const int ALLOCSZ = 10000;

int main() {
  int i, j; int *p;
  for (i = 0; i < MAXCNT; ++i)
    for (j = 0; j < MAXCNT; ++j) {
       p = malloc(ALLOCSZ);
       if (p == NULL)
         printf("Spotted EOM on i = %d, j = %d, ALLOCSZ = %d\n", i, j, ALLOCSZ);
    }
}

