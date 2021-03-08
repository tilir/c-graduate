#include <stdio.h>
#include <string.h>

char *strcat_ (char *dst, const char *src) {
  // TODO: concatenate dst with src
  return dst;
}

int strlen_ (const char *src) {
  int len = 0;
  // TODO: length of src without terminating '\0'
  return len;
}

int strcmp_ (const char *lhs, const char *rhs) {
  // TODO: compare lhs with rhs
}

const char *strchr_ (const char *src, char c) {  
  // TODO: pointer to first occurence of c in src
}

int
main () {
  char buf[100];
  const char *hello = "Hello, ";
  const char *world = "world!";

  // strcat_ test
  strcpy(buf, hello);
  strcat_(buf, world); 
  if (!strcmp(buf, "Hello, world!")) {
    printf("strcat passed\n");
  }

  // strcmp_ test
  strcpy(buf, hello);
  strcat(buf, world);
  if ((0 == strcmp_(buf, "Hello, world!")) &&
      (0 < strcmp_(buf, "Hallo, world!")) &&
      (0 > strcmp_(buf, "Hello, worlt!")))  {
    printf("strcmp passed\n");
  }

  strcpy(buf, hello);
  strcat(buf, world);
  if ((strlen_(buf) == strlen_(hello) + strlen_(world)) &&
      (strlen_(buf) > strlen_(hello))) {
    printf("strlen passed\n");
  }

  strcpy(buf, hello);
  strcat(buf, world);  
  if (!strcmp(strchr_(buf, 'w'), world)) {
    printf("strchr passed\n");
  }
}

