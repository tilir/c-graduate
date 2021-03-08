#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strrev(char *str) {
  // TODO: reverse string
}

int main() {
  char *buf = (char *) calloc(50, sizeof(char));
  strcpy(buf, "1 23 456 78 9");
  strrev(buf);
  assert (0 == strcmp(buf, "9 87 654 32 1");
}

