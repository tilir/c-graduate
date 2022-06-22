//------------------------------------------------------------------------------
//
// this file implements all mixed mode tuples
//
// Details may be found in Knuth, algorithm 7.2.1.1.M
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#include <assert.h>

#include "comb.h"

// input: array of tuple, array of borders N0, N1, ... Nj
// modifies: tuple [first, last)
// returns: 0 if results dropped back to orig, 1 if next tuple generated
int next_mm_tuple_of(int *first, int *last, const int *bfirst) {
  int j = last - first - 1;
  if (j < 0)
    return 0;
  assert(first && last && bfirst && j >= 0);

  // simplest case: just increase
  if (first[j] < bfirst[j] - 1) {
    first[j] += 1;
    return 1;
  }

  // carry case: fining j to increase
  while (j >= 0 && first[j] == bfirst[j] - 1) {
    first[j] = 0;
    j = j - 1;
  }

  // digit position found
  if (j >= 0) {
    first[j] += 1;
    return 1;
  }

  // not found: we already zeroed everything
  return 0;
}
