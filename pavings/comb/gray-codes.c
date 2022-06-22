//------------------------------------------------------------------------------
//
// this file implements all gray codes in binary
//
// Details may be found in Knuth, algorithm 7.2.1.1.G
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#include <stdlib.h>

#include "comb.h"

int next_gray(int *first, int *last, int *ainf) {
  int j = 0;
  *ainf = 1 - *ainf;
  if (*ainf == 0) {
    // look for minimum j: a[j-1] = 1
    for (int *p = first; p != last; ++p) {
      j += 1;
      if (*p == 1)
        break;
    }
  }
  if (j == last - first) {
    first[j - 1] = 0;
    return 0;
  }

  first[j] = 1 - first[j];
  return 1;
}
