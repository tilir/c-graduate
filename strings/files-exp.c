//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// calculating file checksum
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char buf;
  unsigned long long sum = 0;

  if (argc < 2) abort();

  FILE *f = fopen(argv[1], "rb");
  if (f == NULL)
    perror("Error opening file: ");

  while (1 == fscanf(f, "%c", &buf)) {
    printf("%c", buf);
    sum += buf;
  }
  printf("\n Checksum: %llu\n", sum);
  fclose(f);
}

