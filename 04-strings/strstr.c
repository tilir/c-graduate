#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char *strstrci(const char *haystack, const char *needle) {
  const char *found = NULL;
  int i, hlen, nlen;
  hlen = strlen(haystack);
  nlen = strlen(needle);
  for(i = 0; i < hlen - nlen; ++i){
    const char *s = needle;
    while((*s != '\0') && 
          (toupper(*s) == toupper(haystack[i + s - needle])))
      s += 1;
    if (*s == '\0') {
      found = haystack + i;
      break;
    }
  }
  return (char *) found;
}

int main() {
  const char *needle = "ab";
  const char *src = "aBracadabra";
  char *pos1, *pos2, *pos3; 

  assert(toupper('a') == 'A');

  pos1 = strstrci(src, needle); 
  assert(pos1 != NULL);
  pos2 = strstrci(pos1 + 2, needle);
  assert(pos2 != NULL);
  pos3 = strstrci(pos2 + 2, needle);
  assert(pos3 == NULL);
}

