//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Problem SP template
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *replace(char *str, char const *from, char const *to) {
  // TODO: your code here
}

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