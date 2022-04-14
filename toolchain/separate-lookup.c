//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Example of dynamic linking with lookup table
//
// Try:
// gcc -shared -fPIC separate-lookup-table.c -o libseparate-lookup-table.so
// nm -CD libseparate-lookup-table.so
//
// gcc separate-lookup.c -L. -lseparate-lookup-table -Wl,-rpath,.
// objdump -d a.out >& a.dis
//
//-----------------------------------------------------------------------------

#include <assert.h>

extern unsigned lookup[];

unsigned __attribute__((noinline)) fact(unsigned x) {
  assert(x < 13);
  return lookup[x];
}

int main() {
  assert(fact(10) == 3628800);
  return 0;
}
