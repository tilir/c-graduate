#include <stdio.h>

int foo(int arr[restrict static 10][20]) {
  printf("Victory\n");
}

int main() {
  int arr[5][20];
  int arr2[15][20];
  int arr3[15][25];
  foo(arr);
  foo(arr2);
#if 0
  foo(arr3);
#endif
}

