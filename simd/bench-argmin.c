//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Vectorized argmin benchmark
// > gcc -march=tigerlake -O2 bench-argmin.c
// > ./a.out
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "simd.h"
#include "simple-bench.h"

const int NREPS = 500000;
const int DEFMEM = 12;

typedef int (*argmin_ty)(const int *a, int n);

int argmin(const int *a, int n) {
  int i, k = 0;
  for (i = 0; i < n; i++)
    if (a[i] < a[k])
      k = i;
  return k;
}

int argmin_simd(const int *a, int n) {
  int i, k;
  int min_arr[16], idx_arr[16];

  // current indices and increment step
  ri512 cur = set_zvalues(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  ri512 step = set_zvalue(16);

  // current minimum and its position (start with maxint an 0)
  ri512 min = set_zvalue(INT_MAX);
  ri512 argmin = set_zvalue(0);

  int mainsz = (n / 16) * 16;

  for (i = 0; i < mainsz; i += 16) {
    ri512 undertest = load_zvalue_unaligned(a + i);
    m16 mask = greater_eq_zvalue_mask(min, undertest);
    argmin = blend_zvalues(mask, argmin, cur);
    min = min_zvalues(min, undertest);
    cur = add_zvalues(cur, step);
  }

  // unwrap min_arr
  store_zvalue_unaligned(min_arr, min);
  store_zvalue_unaligned(idx_arr, argmin);

  k = 0;
  for (int i = 1; i < 16; i += 1) {
    if (min_arr[i] < min_arr[k])
      k = i;

    // return first minimum, not arbitrary one
    if (min_arr[i] == min_arr[k] && idx_arr[i] < idx_arr[k])
      k = i;
  }
  // unwrap k to proper value in global array
  k = idx_arr[k];

  // process tail
  for (i = mainsz; i < n; i += 1)
    if (min_arr[i] < min_arr[k])
      k = i;

  return k;
}

int measure_argmin(argmin_ty f, const int *a, int n, int reps, int q) {
  double macc;
  int i, j;
  struct timespec time1, time2;

  simple_gettime(&time1);
  for (j = 0; j < reps; ++j) {
    NOOPT(j);
    int pos = f(a, n);
    NOOPT(pos);
  }
  simple_gettime(&time2);
  macc = diff(time1, time2);

  if (!q)
    printf("Measured: %lf\n", macc);
  else
    printf("%lf ", macc);
}

int main(int argc, char **argv) {
  int i, mem = DEFMEM, reps = NREPS, q = 0, res, res_simd;
  int *a;
  srand(time(NULL));

  maybe_readopt(argc, argv, 1, &mem);
  maybe_readopt(argc, argv, 2, &reps);
  maybe_readopt(argc, argv, 3, &q);

  if (!q)
    printf("Hello from argmin bench. Usage:\n%s [lg size] [reps] [q]\n",
           argv[0]);

  if (mem > 30)
    abort();
  mem = 1 << mem;
  if (!q)
    printf("Measuring %d reps of argmins in %d-sized array\n", reps, mem);
  else
    printf("%d ", mem);

  a = calloc(mem, sizeof(int));
  if (!a)
    abort();

  for (i = 0; i < mem; ++i)
    a[i] = rand() % mem;

  res = argmin(a, mem);
  res_simd = argmin_simd(a, mem);
  if (res != res_simd) {
    printf("Bug detected: argmin %d vs %d\n", res, res_simd);
    abort();
  }

  if (!q)
    printf("Simple argmin\n");
  measure_argmin(argmin, a, mem, reps, q);
  if (!q)
    printf("SIMD argmin\n");
  measure_argmin(argmin_simd, a, mem, reps, q);

  if (q)
    printf("\n");
  free(a);
}