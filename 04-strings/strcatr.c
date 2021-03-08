#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// dest (with len)
// source (with len)
// bufsize
char *
strcat_r(char *dest, int dstlen, char const *src, int srclen, int *bufsz) {
  int bsz = *bufsz;
  int len;

  len = dstlen + srclen + 1;

  if (len > bsz) {
    // extend memory under dest
    dest = realloc(dest, len);
    assert(dest);
  }

  strncat(dest, src, srclen);

  *bufsz = bsz;
  return dest;
}

int main() {
  char *buf;
  char *res;
  int bufsz = 20;
  
  buf = malloc(20);
  assert(buf);
  
  strcpy(buf, "Hello");
  res = strcat_r(buf, 6, "world", 6, &bufsz);
  printf("%s\n", res);
  
  free(buf);
}

