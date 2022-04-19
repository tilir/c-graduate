//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// LTO basic example, see also part.c
//
// try:
// > gcc -O2 main.c part.c -flto
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int number();

int main() { printf("%d\n", number()); }
