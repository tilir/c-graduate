//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// strange hello world
//
// try:
// > gcc allthree.c -o allthree
// > ./allthree < allthree.inp 1> allthree.out 2> allthree.err
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

int main() {
  int n, res;
  res = fscanf(stdin, "%d", &n);
  if (res != 1) {
    fprintf(stderr, "Error: input incorrect\n");
    abort();
  } else if (n == 0) {
    fprintf(stderr, "Error: division by zero\n");
    abort();
  }
  fprintf(stdout, "%d\n", 720 / n);
}
