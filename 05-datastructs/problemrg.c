#include <assert.h>
#include <stdio.h>

typedef int (*generator_t)(int);

unsigned cycle_len(generator_t gen) {
  // TODO: your code here
}

int sample_gen(int x) {
  return (x + 2) % 5;
}

enum {
  SHOWME = 10
};

int
main () {
  int i, x;
  unsigned llen;
  printf("Look at generated list:\n");

  x = 0;
  for (i = 0; i < SHOWME; ++i) {
    x = sample_gen(x);
    printf("%d ", x);
  }
  printf("\n");

  llen = cycle_len(sample_gen);
  printf("Calculated loop len is: %u\n", llen);
  return 0;
}

