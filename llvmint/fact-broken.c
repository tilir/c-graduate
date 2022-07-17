//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// fact example: broken tail recursion
//
// try:
// > clang -O2 fact-broken.c
//
//-----------------------------------------------------------------------------

unsigned fact_mod(unsigned x, unsigned m) {
  if (x < 2)
    return 1;

  return (x * fact_mod(x - 1, m)) % m;
}