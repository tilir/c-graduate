#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *f;

  if (argc < 2) {
    printf("Usage: <%s file-to-open>\n", argv[0]);
    return -1;
  }

  f = fopen(argv[1], "w");
  
  if (f == NULL) {
    perror("File open error:");
    return -2;
  }

  fprintf(f, "%s\n", "Hello, file world!");

  // printf == fprintf(stdout, .....)
  fprintf(stdout, "%s\n", "Hello, console world!");

  fclose(f);
}

