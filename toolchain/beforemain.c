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
//-----------------------------------------------------------------------------

#include <stdio.h>

int __attribute__((constructor)) foo() { printf("Before main!\n"); }

int main() { printf("Main\n"); }
