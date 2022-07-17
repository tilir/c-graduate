//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// canonicalization example: all functions spawn same code
//
// try:
// > clang -O2 -emit-llvm -S canonicalize.c
//
//-----------------------------------------------------------------------------

unsigned foo0(unsigned a, unsigned b, unsigned c) {
  unsigned x = a ? b : c;
  return x;
}

unsigned foo1(unsigned a, unsigned b, unsigned c) {
  int x = c;
  if (a)
    x = b;
  return x;
}

unsigned foo2(unsigned a, unsigned b, unsigned c) {
  int x;
  if (!a)
    x = c;
  else
    x = b;
  return x;
}