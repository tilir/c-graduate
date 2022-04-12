//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// main module for ABI demonstrations (see also fact.c)
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int fact(int x);
int y = 5;

int main() {
  int f;
  f = fact(y);
  // asm("mov edi, %0"::"r"(y));
  // asm("call fact":::"eax");
  // asm("call fact\n\tmov %0, eax":"=r"(f)::"eax");
  printf("%d\n", f);
}

