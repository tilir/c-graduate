//------------------------------------------------------------------------------
//
// Mixed mode tuple generation app and tests
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#include <stdio.h>

#include "comb.h"

static void print_arr(int *first, int *last) {
  for (int *p = first; p != last; ++p)
    printf("%d ", *p);
  printf("\n");
}

static void test2134() {
  int borders[] = {2, 1, 3, 4};
  int arr[] = {0, 0, 0, 0};
  int k = 1;

  while (k == 1) {
    print_arr(arr, arr + 4);
    k = next_mm_tuple_of(arr, arr + 4, borders);
  }

  printf("Restored array:\n");
  print_arr(arr, arr + 4);
}

static void test2134_loopless() {
  int m[] = {2, 2, 3, 4};
  int a[] = {0, 0, 0, 0};    // a(n-1) .. a(0)
  int f[] = {0, 1, 2, 3, 4}; // f(n) .. f(0)
  int o[] = {1, 1, 1, 1};

  printf("Loopless:\n");

  for (int i = 0; i < 9; ++i) {
    int j;

    // H2:
    print_arr(a, a + 4);

    // H3:
    j = f[0];
    f[0] = 0;
    printf("Active coord: %d\n", j);

    if (j == 4)
      break;

    a[j] = a[j] + o[j];

    if (a[j] == 0 || a[j] == m[j] - 1) {
      printf("Reflect: %d\n", j);
      o[j] = -o[j];
      f[j] = f[j + 1];
      f[j + 1] = j + 1;
      print_arr(f, f + 5);
    }
  }
}

int main() {
  test2134();
  test2134_loopless();
}