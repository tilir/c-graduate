//------------------------------------------------------------------------------
//
// this file implements all mixed mode tuples, loopless variant
//
// Details may be found in Knuth, algorithm 7.2.1.1.H
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#include <stdlib.h>

#include "comb.h"

struct loopless_state {
  int *f, *o;
};

struct loopless_state *create_loopless_state(int n) {
  struct loopless_state *ls = malloc(sizeof(struct loopless_state));

  ls->f = malloc((n + 1) * sizeof(int));
  ls->o = malloc(n * sizeof(int));

  for (int i = 0; i < n; ++i) {
    ls->f[i] = i;
    ls->o[i] = 1;
  }

  ls->f[n] = n;
  return ls;
}

void free_loopless_state(struct loopless_state *state) {
  free(state->f);
  free(state->o);
  free(state);
}

int loopless_next_mm_tuple_of(int *first, int *last, const int *bfirst,
                              struct loopless_state *ls) {
  int *f = ls->f, *o = ls->o, *a = first;
  const int *m = bfirst;
  int n = last - first;
  int j = f[0];
  f[0] = 0;

  if (j == n) {
    a[n - 1] = 0; // others are zeroes already
    return 0;
  }

  // we need skip coordinate if we can not increase
  if (m[j] != 1)
    a[j] = a[j] + o[j];

  if (a[j] == 0 || a[j] == m[j] - 1) {
    o[j] = -o[j];
    f[j] = f[j + 1];
    f[j + 1] = j + 1;
  }

  return 1;
}
