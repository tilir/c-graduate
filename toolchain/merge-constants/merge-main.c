//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// merge constants: main module
//
// try:
// > gcc -O2 merge-main.c merge-foo.c merge-bar.c -o merged
// > gcc -O2 -fno-merge-constants merge-main.c merge-foo.c merge-bar.c 
//       -o non-merged
// > objdump -d --section=.rodata merged
// > objdump -d --section=.rodata non-merged
//
//-----------------------------------------------------------------------------

int foo();
int bar();

float use(float x) { return x * x; }

int main() { return (foo() == bar()) ? 0 : 1; }
