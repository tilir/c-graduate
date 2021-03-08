#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
char *read_word(int *len) {
  char *text;
  int res, i;
  
  res = scanf("%d", len);
  assert(res == 1);
  
  text = calloc(*len + 1, sizeof(char));
  assert(text != NULL);
  
  scanf("%*c");
  
  for (i = 0; i < *len; ++i) {
    res = scanf("%c", text + i);
    assert(res);
  }
  
  return text;
}
#endif

char * strcat_r(char *dest, int dstlen, char const *src, int srclen, int *bufsz) {
  int bsz = *bufsz;
  int len = dstlen + srclen + 1;

  while (len > bsz) {
    bsz *= 2;
    if (bsz >= len) {
      dest = realloc(dest, bsz);
      assert(dest);
    }
  }

  strncat(dest, src, srclen);
  *bufsz = bsz;
  return dest;
}

char *do_replace(char *word, int nword, char const *repl, int nrepl, char const *str, int nstr) {
  char *buf;
  int buflen, bufstrlen;

  // alloc memory
  bufstrlen = 0;
  buflen = nword;
  buf = calloc(nword, sizeof(char));

  for(; ; ) {
    char *substr = strstr(word, repl);
    if (substr == NULL)
      break;

#if 0    
    printf("New entry: <%s>\n", substr);
    printf("Initial buffer: <%s>\n", buf);
#endif    
    
    // 1. append buf from word to substr
    buf = strcat_r(buf, bufstrlen, word, substr - word, &buflen);
    bufstrlen += (substr - word);
    
    // 2. append buf with str
    buf = strcat_r(buf, bufstrlen, str, nstr, &buflen);
    bufstrlen += nstr;

#if 0    
    printf("Updated buffer: <%s>\n", buf);
#endif    
    
    substr += nrepl;
    word = substr;
  }
  
  nword = strlen(word);
  if (nword > 0) {
    buf = strcat_r(buf, bufstrlen, word, nword, &buflen);
  }
  return buf;
}

char *replace(char *str, char const *from, char const *to) {
  return do_replace(str, strlen(str), from, strlen(from), to, strlen(to));
}

#if 1

int main() {
  int nword, nrepl, nstr;
  char *word, *repl, *str; // replace in word repl to str
  char *result;

  word = read_word(&nword);
  repl = read_word(&nrepl);
  str = read_word(&nstr);
  
  printf("Replacing in: <%s>\n", word);
  printf("Text to find: <%s>\n", repl);
  printf("Text to replace: <%s>\n", str);
  
  result = replace(word, repl, str);

  printf("Result is: <%s>\n", result);
}

#endif

