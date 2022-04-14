//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// main module for multi-module demonstrations (see also fact.c)
//
//-----------------------------------------------------------------------------

#include <stdio.h>

#ifdef INC
#include "fact.h"
#else
unsigned fact(unsigned);
#endif

int main() { printf("%d\n", fact(10)); }
