//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// popcnt manual optimization
//
// try:
// > clang -O2 popcnt-opt.c
// > clang -O2 -march=haswell popcnt-opt.c
// > clang -O3 -march=haswell popcnt-opt.c
//
//-----------------------------------------------------------------------------

int popcount(unsigned a) {
  unsigned b, c, d, count;
  b = a - ((a >> 1) & 0x55555555);
  c = (b & 0x33333333) + ((b >> 2) & 0x33333333);
  d = (c + (c >> 4)) & 0x0F0F0F0F;
  count = (d * 0x01010101) >> 24;
  return count;
}