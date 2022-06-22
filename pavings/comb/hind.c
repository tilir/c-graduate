//------------------------------------------------------------------------------
//
// Hindenburg algorithm, rewritten in C way
// see also: 7.2.1.4H in TAOCP
//
// This file implements next_partition(n, m, begin, end)
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#include <assert.h>

#include "comb.h"

// 11 to 4 parts -> 1 + 1 + 1 + 8
// 9 to 5 parts -> 1 + 1 + 1 + 1 + 5
void initial_partition(int n, int m, int *start) {
  int excess = n - m;
  for (int i = 0; i < m - 1; ++i)
    start[i] = 1;
  start[m - 1] = excess + 1;
}

int next_partition(int n, int m, int *start) {
  int *pre_last, *last, *itj;
  int j, s, x;

  // nothing to be done;
  if (n < 2 || m < 2)
    return 0;

  assert(start && n >= 2 && m >= 2);

  pre_last = start + m - 2;
  last = start + m - 1;

  // most common and simple case, like 1118 -> 1127 -> 1136 -> 1145
  // but having 1145 we can not further proceed with 1154 (same partition)
  if (*pre_last < *last - 1) {
    *last -= 1;
    *pre_last += 1;
    return 1;
  }

  // so we need to start hard case like 1145 -> 1226
  j = 3;
  itj = start + m - 3;
  s = *last + *pre_last - 1;

  // by finding smallest j, such that start[j] can be increased
  // without changing start[j + 1] ... start[m]
  // note: s = a[j + 1] ... a[m] - 1
  while ((j <= m) && (*itj >= *last - 1)) {
    s = s + *itj;
    j += 1;
    itj--;
  }

  // this is the case we was at 2333
  // nothing can be improved
  if (j > m) {
    initial_partition(n, m, start);
    return 0;
  }

  x = *itj + 1;
  *itj = x;
  itj++;
  j -= 1;

  // tweaking start[0] ... start[j]
  while (j > 1) {
    *itj = x;
    s -= x;
    j -= 1;
    itj++;
  }

  *last = s;
  return 1;
}
