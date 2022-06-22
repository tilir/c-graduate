//------------------------------------------------------------------------------
//
// Lexicographic partition generation app and tests
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

static void test9() {
  int arr[5];
  int k = 1;

  initial_partition(9, 5, arr);

  while (k == 1) {
    print_arr(arr, arr + 5);
    k = next_partition(9, 5, arr);
  }

  printf("Restored array:\n");
  print_arr(arr, arr + 5);
}

int main() { test9(); }