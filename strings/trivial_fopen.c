//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// trivial fopen example with error processing
//
//-----------------------------------------------------------------------------

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

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
