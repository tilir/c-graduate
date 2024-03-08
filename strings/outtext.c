//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Writing some text to file
//
//-----------------------------------------------------------------------------

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *f;
  char c;

  if (argc < 2) {
    printf("Usage: <%s file-to-open>\n", argv[0]);
    return -1;
  }

  f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("File open error:");
    return -2;
  }

  while (fscanf(f, "%c", &c) == 1)
    printf("%c", c);
  printf("\n");

  fclose(f);
}
