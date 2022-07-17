//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// inline example: LTO mode
//
// try:
// > clang -O2 -flto inline.c inline-main.c
// > objdump -M intel -d a.out > a.dis
//
//-----------------------------------------------------------------------------

#include <stdio.h>

unsigned foo8(unsigned x) { return x; }

unsigned foo0(unsigned x);

int main() {
  unsigned n = foo0(1);
  printf("%u\n", n);
}
