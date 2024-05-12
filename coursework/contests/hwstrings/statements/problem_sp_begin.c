#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace(char *str, char const *from, char const *to);

static char *read_word(int *len) {
  char *text;
  int res, n, i;

  res = scanf("%d", len);
  assert(res == 1);

  n = *len;
  assert(n > 0);

  text = (char *)calloc(n + 1, sizeof(char));
  assert(text != NULL);

  scanf("%*c");

  for (i = 0; i < n; ++i) {
    res = scanf("%c", text + i);
    assert(res == 1);
  }

  return text;
}

int main() {
  int i, nword, nrepl, nstr, res;
  char *word, *repl, *str, *newstr;

  word = read_word(&nword);
  repl = read_word(&nrepl);
  str = read_word(&nstr);

  newstr = replace(str, word, repl);

  printf("%s\n", newstr);

  free(word);
  free(repl);
  free(str);
  free(newstr);
}
