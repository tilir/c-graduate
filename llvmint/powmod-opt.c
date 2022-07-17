//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// pownmod opt example
//
// try:
// > clang -O2 powmod-opt.c
//
//-----------------------------------------------------------------------------

int pow_mod(int x, int n, int m) {
  int acc = x % m, prod = 1;
  for (; n > 0;) {
    if ((n % 2) == 1)
      prod = (prod * acc) % m;
    acc = (acc * acc) % m;
    n = n / 2;
  }
  return prod;
}