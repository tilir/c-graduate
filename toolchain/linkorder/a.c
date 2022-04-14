//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// link order experiments: a.c, b.c and d.c
// try:
// > gcc -O2 b.c -c -o b.o
// > ar cr libb.a b.o
// > gcc -O2 d.c -c -o d.o
// > ar cr libd.a d.o
//
// Then to investigate link order effects:
// > gcc -L. -lb -ld a.c
// > gcc -L. -ld -lb a.c
// > gcc a.c -L. -ld -lb
// > gcc a.c -L. -lb -ld
//
//-----------------------------------------------------------------------------

extern int a;

int main() { return a; }
