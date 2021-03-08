#include <stdio.h>

void copy_simple(char *dst, const char *src) {
  while (*src != '\0') {
    *dst = *src;
    dst += 1;
    src += 1;
  }
  *dst = '\0';
}

void copy_really_stylish(char *dst, const char *src) {
  while ((*dst++ = *src++) != '\0') {}
}

int main () {
  char hello[20] = "Hello, world!";
  char duplicate[20] = {0};
  char duplicate2[20] = {0};

  copy_simple(duplicate, hello);
  printf("%s == %s\n", hello, duplicate);

  copy_really_stylish(duplicate2, hello);
  printf("%s == %s\n", hello, duplicate2);
}

