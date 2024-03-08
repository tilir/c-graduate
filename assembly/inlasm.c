//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// main module for ABI demonstrations (see also fact.c)
// gcc -O2 -masm=intel inlasm.c fact.c
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int fact(int x);
int y = 5;

int myadd(int x, int y) {
  int res = x;
  asm ("add %0, %1":"+r"(res):"r"(y));
  return res;
}

int main() {
  int res;
  printf("%d\n", myadd(2, 3));
  // res = fact(y);
  asm("mov edi, %1\n"
      "\tcall fact\n"
      "\tmov %0, eax":"=r"(res):"r"(y):"eax");
  printf("%d\n", res);
}

