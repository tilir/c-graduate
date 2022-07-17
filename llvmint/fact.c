//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// fact example: compiler unwinds tail recursion
//
// try:
// > clang -O2 -fno-vectorize fact.c
//
//-----------------------------------------------------------------------------

unsigned fact(unsigned x) {
  if (x < 2)
    return 1;

  return x * fact(x - 1);
}