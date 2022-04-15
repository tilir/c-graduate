//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// valgrind simple leak example
//
// gcc -O0 -g leak.c
// valgrind ./a.out
//
//-----------------------------------------------------------------------------

#include <stdlib.h>

char *__attribute__((noinline)) leak() {
  char *ix = malloc(10);
  return ix;
}

int main() { leak(); }
