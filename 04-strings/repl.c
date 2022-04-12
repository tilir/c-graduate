//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// replace template
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace(const char *str, const char *from, const char *to) {
  // TODO: write code
}

int main() {
  char *s = replace("Hello, %username, how are you, %username", "%username",
                    "Eric, the Blood Axe");
  printf("%s\n", s);
  free(s);
}
