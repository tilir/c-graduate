#include <stdalign.h>
#include <stddef.h>
#include <stdio.h>

struct S {
  char x;
  long y;
};

int main() {
  printf("size of char = %d\n", (int) sizeof(char));
  printf("align of char = %d\n", (int) alignof(char));
  printf("size of long = %d\n", (int) sizeof(long));
  printf("align of long = %d\n", (int) alignof(long));
  printf("size of S = %d\n", (int) sizeof(struct S));
  printf("align of S = %d\n", (int) alignof(struct S));
  printf("offset of x in S = %d\n", (int) offsetof(struct S, x));
  printf("offset of y in S = %d\n", (int) offsetof(struct S, y));
}
