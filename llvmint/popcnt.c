//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// popcnt example to emphasize importance of arch
//
// try:
// > clang -O2 popcnt.c
// > clang -O2 -march=haswell popcnt.c
//
//-----------------------------------------------------------------------------

int popcount(int a) {
  int count = 0;
  while (a) {
    count += 1;
    a &= a - 1;
  }
  return count;
}