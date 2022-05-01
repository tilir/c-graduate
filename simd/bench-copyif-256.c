//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Vectorized copy-if benchmark with lookup table, YMM version
// > gcc -march=tigerlake -O2 bench-copyif-256.c
// > ./a.out
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "simd.h"
#include "simple-bench.h"

const int NREPS = 100000;
const int DEFMEM = 13;

typedef int (*copy_ifty)(const int *a, int *b, int n, int p);

// regular copy_if_less
// copies a to b if a[i] < p
int copy_if_less(const int *a, int *b, int n, int p) {
  int k = 0;
  for (int i = 0; i < n; i++)
    if (a[i] < p)
      b[k++] = a[i];
  return k;
}

// 8-element permutations for 8-bit masks
__attribute__((aligned(64))) int permutation[(1 << 8)][8];

void precalc() {
  for (int m = 0; m < (1 << 8); m++) {
    int k = 0;
    for (int i = 0; i < 8; i++)
      if (m >> i & 1)
        permutation[m][k++] = i;
#ifdef VISUALIZE_PERM
    if (m < 64) {
      printf("%d: ", m);
      for (int i = 0; i < 8; i++)
        printf("%d ", permutation[m][i]);
      printf("\n");
    }
#endif
  }
}

int copy_if_less_simd(const int *a, int *b, int n, int p) {
  int k = 0, i;
  int mainsz = (n / 8) * 8;
  ri256 pred = set_yvalue(p);

  for (i = 0; i < mainsz; i += 8) {
    ri256 x, idx, y;
    m8 mask;

    x = load_yvalue_unaligned(a + i);
    mask = greater_yvalue_mask(pred, x);
    idx = load_yvalue_unaligned(permutation + mask);
    y = permute_yvalue(idx, x);
    store_yvalue_unaligned(b + k, y);
    k += __builtin_popcount(mask);
  }

  for (i = mainsz; i < n; i += 1)
    if (a[i] < p)
      b[k++] = a[i];
  return k;
}

int measure_copyif(copy_ifty f, const int *a, int n, int reps, int q) {
  double macc;
  int i, j;
  struct timespec time1, time2;
  int *b = malloc(n * sizeof(int));
  if (!b)
    abort();

  simple_gettime(&time1);
  for (j = 0; j < reps; ++j) {
    NOOPT(j);
    int ncpy = f(a, b, n, n / 2);
    NOOPT(ncpy);
  }
  simple_gettime(&time2);
  macc = diff(time1, time2);

  if (!q)
    printf("Measured: %lf\n", macc);
  else
    printf("%lf ", macc);
  free(b);
}

int smoke_test(const int *a, int n) {
  int i, ncpy, ncpy_simd;
  int *b = malloc(n * sizeof(int));
  int *bsimd = malloc(n * sizeof(int));
  if (!b || !bsimd)
    abort();

  ncpy = copy_if_less(a, b, n, n / 3);
  ncpy_simd = copy_if_less_simd(a, bsimd, n, n / 3);

  if (ncpy != ncpy_simd) {
    printf("Bug detected: sizes: %d vs %d\n", ncpy, ncpy_simd);
    abort();
  }

  for (i = 0; i < ncpy; ++i)
    if (b[i] != bsimd[i]) {
      printf("Bug detected: %d position: %d vs %d\n", i, b[i], bsimd[i]);
      abort();
    }

  free(b);
  free(bsimd);
}

int main(int argc, char **argv) {
  int i, mem = DEFMEM, reps = NREPS, q = 0, res, res_simd;
  int *a;
  srand(time(NULL));

  maybe_readopt(argc, argv, 1, &mem);
  maybe_readopt(argc, argv, 2, &reps);
  maybe_readopt(argc, argv, 3, &q);

  if (!q)
    printf("Hello from find bench. Usage:\n%s [lg size] [reps] [q]\n", argv[0]);

  if (mem > 30)
    abort();
  mem = 1 << mem;
  if (!q)
    printf("Measuring %d reps of copy_ifs of %d-sized array\n", reps, mem);
  else
    printf("%d ", mem);

  a = calloc(mem, sizeof(int));
  if (!a)
    abort();

  for (i = 0; i < mem; ++i)
    a[i] = rand() % mem;

  // masks precalc required for copy_if_less_simd
  precalc();

  // basic correctness check before measurements
  smoke_test(a, mem);

  if (!q)
    printf("Simple copy_if\n");
  measure_copyif(copy_if_less, a, mem, reps, q);

  if (!q)
    printf("SIMD copy_if\n");
  measure_copyif(copy_if_less_simd, a, mem, reps, q);

  if (q)
    printf("\n");
  free(a);
}