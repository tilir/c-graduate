//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// constructor demonstration (init section)
//
// try:
// > gcc -O2 beforemain.c
// > objdump -d -j .text ./a.out | grep foo
// > objdump -d -j .init_array ./a.out
//
//-----------------------------------------------------------------------------

#include <stdio.h>

void __attribute__((constructor)) foo() { printf("Foo\n"); }

int main() { printf("Main\n"); }
