//------------------------------------------------------------------------------
//
// Gray binary code app and tests
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

static void test4() {
  int arr[] = {0, 0, 0, 0};
  int ainf = 0;
  int k = 1;
  printf("Gray codes:\n");

  while (k == 1) {
    print_arr(arr, arr + 4);
    k = next_gray(arr, arr + 4, &ainf);
  }

  printf("Restored array:\n");
  print_arr(arr, arr + 4);
}

static void test4_rho() {
  int arr[] = {0, 0, 0, 0};
  int ainf = 0;
  int k = 1;
  printf("Gray codes (rho):\n");

  while (k == 1) {
    print_arr(arr, arr + 4);
    k = next_gray_rho(arr, arr + 4, &ainf);
  }

  printf("Restored array:\n");
  print_arr(arr, arr + 4);
}

int main() {
  test4();
  test4_rho();
}