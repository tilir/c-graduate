#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace(const char *str, 
              const char *from, 
              const char *to) {
  // TODO: write code
}

int main() {
  char *s = replace("Hello, %username, how are you, %username", 
                    "%username", "Eric, the Blood Axe");
  printf("%s\n", s);
  free(s);
}

