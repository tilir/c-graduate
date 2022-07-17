//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// pownmod example: compiler unrolls loop but don't improve algorithm
//
// try:
// > clang -O2 powmod.c
//
//-----------------------------------------------------------------------------

int pow_mod(int x, int n, int m) {
  int i, acc = 1;
  for (i = 0; i < n; ++i)
    acc = (acc * x) % m;
  return acc;
}
