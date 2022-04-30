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

const int NFINDS = 100000;
const int NREPS = 10;
const int DEFMEM = 12;

typedef int (*find_ty)(const int *a, int mem, int x);

int find(const int *a, int mem, int x) {
  int i;
  for (i = 0; i < mem; i++)
    if (a[i] == x)
      return i;
  return -1;
}

int find_simd(const int *a, int mem, int x) {
  int i;
  ri512 needle = set_zvalue(x);
  int mainsz = (mem / 16) * 16;

  for (i = 0; i < mainsz; i += 16) {
    ri512 undertest = load_zvalue_unaligned(a + i);
    int m = first_equal_zvalue(needle, undertest);
    if (m != -1)
      return i + m;
  }

  for (i = mainsz; i < mem; i += 1) {
    if (a[i] == x)
      return i;
  }
  return -1;
}

int measure_find(find_ty f, const int *a, int mem, int reps) {
  double macc;
  int i, j;
  struct timespec time1, time2;
  simple_gettime(&time1);
  for (i = 0; i < NFINDS; ++i) {
    NOOPT(i);
    for (j = 0; j < reps; ++j) {
      NOOPT(j);
      int pos = f(a, mem, rand() % mem);
      NOOPT(pos);
    }
  }
  simple_gettime(&time2);
  macc = diff(time1, time2);
  printf("Measured: %lf\n", macc);
}

int main(int argc, char **argv) {
  int i, mem = DEFMEM, reps = NREPS, res, res_simd;
  int *a;
  srand(time(NULL));

  printf("Hello from find bench. Usage:\n%s [size] [reps]\n", argv[0]);
  maybe_readopt(argc, argv, 1, &mem);
  maybe_readopt(argc, argv, 2, &reps);
  if (mem > 30)
    abort();
  mem = 1 << mem;
  printf("Measuring %d repetitions of %d-finds in %d-sized array\n", reps,
         NFINDS, mem);

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

  printf("Simple find\n");
  measure_find(find, a, mem, reps);
  printf("SIMD find\n");
  measure_find(find_simd, a, mem, reps);
}