//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// main arguments example
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int i;
  printf("ARGC is: %d\n", argc);
  for (i = 0; i < argc; ++i)
    printf("ARGV[%d] is: %s\n", i, argv[i]);
}
