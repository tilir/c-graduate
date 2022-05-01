//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Vectorized find benchmark
// > gcc -march=tigerlake -O2 bench-find.c
// > ./a.out
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "simd.h"
#include "simple-bench.h"

const int NREPS = 1000000;
const int DEFMEM = 12;

typedef int (*find_ty)(const int *a, int n, int x);

int find(const int *a, int n, int x) {
  int i;
  for (i = 0; i < n; i++)
    if (a[i] == x)
      return i;
  return -1;
}

int find_simd(const int *a, int n, int x) {
  int i;
  ri512 needle = set_zvalue(x);
  int mainsz = (n / 16) * 16;

  for (i = 0; i < mainsz; i += 16) {
    ri512 undertest = load_zvalue_unaligned(a + i);
    int m = first_equal_zvalue(needle, undertest);
    if (m != -1)
      return i + m;
  }

  for (i = mainsz; i < n; i += 1)
    if (a[i] == x)
      return i;

  return -1;
}

int measure_find(find_ty f, const int *a, int n, int reps, int q) {
  double macc;
  int i, j;
  struct timespec time1, time2;

  simple_gettime(&time1);
  for (j = 0; j < reps; ++j) {
    NOOPT(j);
    int pos = f(a, n, rand() % n);
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
    printf("Hello from find bench. Usage:\n%s [lg size] [reps] [q]\n", argv[0]);

  if (mem > 30)
    abort();
  mem = 1 << mem;
  if (!q)
    printf("Measuring %d reps of finds in %d-sized array\n", reps, mem);
  else
    printf("%d ", mem);

  a = calloc(mem, sizeof(int));
  if (!a)
    abort();

  for (i = 0; i < mem; ++i)
    a[i] = i;

  i = rand() % mem;
  res = find(a, mem, i);
  res_simd = find_simd(a, mem, i);
  if (res != res_simd) {
    printf("Bug detected: %d position: %d vs %d\n", i, res, res_simd);
    abort();
  }

  if (!q)
    printf("Simple find\n");
  measure_find(find, a, mem, reps, q);
  if (!q)
    printf("SIMD find\n");
  measure_find(find_simd, a, mem, reps, q);

  if (q)
    printf("\n");
  free(a);
}