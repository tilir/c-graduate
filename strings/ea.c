#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  int i, reverse = 0;
  printf("prog: %s\n", argv[0]);
  printf("args:\n");
  for (i = 1; i < argc; ++i)
    if (strcmp(argv[i], "-r") == 0)
      reverse = 1;
  for (i = 1; i < argc; ++i) {
    int j, k = i;
    if (reverse)
      k = argc - i;
    for (j = 0; j < strlen(argv[k]); ++j)
      if (argv[k][j] == '-')
        argv[k][j] = '+';
    printf("%s\n", argv[k]);
  }
}

