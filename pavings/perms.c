//------------------------------------------------------------------------------
//
// Lexicographic permutation generation
// see also: 7.2.1.2.L in TAOCP
//
// This file implements next_perm_of
// just like std::next_permuitation but in C
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void swap(int *p1, int *p2) {
  int t = *p1;
  *p1 = *p2;
  *p2 = t;
}

// [1, 2, 3, 4) --> [4, 3, 2, 1)
static void reverse_subarr(int *first, int *last) {
  while (first < last - 1) {
    swap(first, last - 1);
    first += 1;
    last -= 1;
  }
}

int next_perm_of(int *first, int *last) {
  int n = last - first;
  assert(first && last && n > 1);

  // L2: is_sorted for permutation
  // for 1 2 3 4 we see first inversion at (3 4)
  // for 2 4 3 1 we see first inversion at (2 4)
  // for 4 3 2 1 we see no inversion
  int j = n - 2;
  while (first[j] >= first[j + 1])
    j -= 1;

  // at this point j is the smallest subscript for which all a0..aj perms
  // were already visited
  if (j != -1) {
    // L3: find element to swap
    int l = n - 1;
    while (first[j] >= first[l])
      l -= 1;

    // first[l] is the smallest element, greater, then first[j]
    swap(first + j, first + l);
  }

  // reverse subarray
  if (j < n - 2)
    reverse_subarr(first + j + 1, last);

  // if j was 0, wealready reverssed back
  return (j != -1);
}

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