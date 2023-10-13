#include <stdio.h>
#include <stdlib.h>

const int ALLOCSZ = 100000;
const int MAXCNT = 83; // try 84

int foo(int cnt) {
  char s[ALLOCSZ];
  if (cnt > 0) {
    printf(".");
    foo(cnt - 1);
  }
}

int main() {
  foo(MAXCNT);
}

