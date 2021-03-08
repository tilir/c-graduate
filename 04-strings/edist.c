#include <assert.h>
#include <stdio.h>
#include <string.h>

struct costs {
  int addcost, removecost, replacecost;
};

int edistance (const char *fst, const char *snd, struct costs c) {
  // TODO: write code
}

void spoontest() {
  const char *str1 = "spoon";
  const char *str2 = "sponge";
  struct costs c = {1, 1, 2};
  int edist = edistance(str1, str2, c);
  assert(edist == 3);
}

void genomtest() {
  const char *str1 = "AGGCTATCACCTGACCTCCAGGCCGATGCCC";
  const char *str2 = "TAGCTATCACGACCGCGGTCGATTTGCCCGAC";
  struct costs c = {1, 1, 2};
  int edist = edistance(str1, str2, c);
  printf("%d\n", edist);
}

int
main () {
  spoontest();
  genomtest();
}

