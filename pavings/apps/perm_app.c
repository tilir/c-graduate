//------------------------------------------------------------------------------
//
// Lexicographic permutation generation app and tests
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

static void test2() {
  int arr[] = {1, 2};
  int k = 1;
  printf("Test for 2 elements:\n");

  while (k == 1) {
    print_arr(arr, arr + 2);
    k = next_perm_of(arr, arr + 2);
  }

  printf("Restored array:\n");
  print_arr(arr, arr + 2);
}

static void test_multi() {
  int arr[] = {1, 1, 2, 3};
  int k = 1;
  printf("Test for multiset:\n");

  while (k == 1) {
    print_arr(arr, arr + 4);
    k = next_perm_of(arr, arr + 4);
  }

  printf("Restored array:\n");
  print_arr(arr, arr + 4);
}

static void test4() {
  int arr[] = {1, 2, 3, 4};
  int k = 1;
  printf("Test for 4 elements:\n");

  while (k == 1) {
    print_arr(arr, arr + 4);
    k = next_perm_of(arr, arr + 4);
  }

  printf("Restored array:\n");
  print_arr(arr, arr + 4);
}

int main() {
  test2();
  test_multi();
  test4();
}