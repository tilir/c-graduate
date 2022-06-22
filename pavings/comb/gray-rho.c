//------------------------------------------------------------------------------
//
// this file implements all gray codes in binary
//
// This is not from Knuth, this is just variation around explicit rho function
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#include <stdlib.h>

#include "comb.h"

int next_gray_rho(int *first, int *last, int *n) {
  *n += 1;
  int j = __builtin_ctz(*n); // rho function
  if (j == last - first) {
    first[j - 1] = 0;
    return 0;
  }
  first[j] = 1 - first[j];
  return 1;
}
