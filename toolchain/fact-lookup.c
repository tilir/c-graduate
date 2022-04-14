//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// factorial with lookup for GOT investigation
//
// try:
// > gcc fact-lookup.c -S -O2 -fPIC
//
//-----------------------------------------------------------------------------

#include <assert.h>

unsigned lookup[] = {1,    1,     2,      6,       24,       120,     720,
                     5040, 40320, 362880, 3628800, 39916800, 79001600};

unsigned fact(unsigned x) {
  assert(x < 13);
  return lookup[x];
}
