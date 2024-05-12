#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void patpreproc(char const *needle, int *needle_lps);
char *strstrci(char const *needle, int const *needle_lps, char const *haystack);

static char *read_word(int *len) {
  char *text;
  int res, n, i;

  res = scanf("%d", len);
  assert(res == 1);

  n = *len;
  assert(n > 0);

  text = (char *)calloc(n + 1, sizeof(char));
  assert(text != NULL);

  res = scanf("%*c");
  (void)res;

  for (i = 0; i < n; ++i) {
    char c;
    res = scanf("%c", &c);
    assert(res == 1);
    text[i] = c;
  }

  return text;
}

int main() {
  int nlen, hlen, count = 0;
  char *needle, *haystack, *sres;
  int *needle_lps;

#if VISUALIZE
  int i;
#endif

  haystack = read_word(&hlen);
  needle = read_word(&nlen);

  needle_lps = (int *)calloc(nlen + 1, sizeof(int));
  patpreproc(needle, needle_lps);

#if VISUALIZE
  for (i = 0; i < nlen; ++i)
    printf("%c ", needle[i]);
  printf("\n");

  for (i = 0; i < nlen; ++i)
    printf("%d ", needle_lps[i]);
  printf("\n");
#endif

  sres = haystack;
  for (; ; ) {
    sres = strstrci(needle, needle_lps, sres);
    if (!sres)
      break;
    count += 1;
    sres += nlen;
  }

  printf("%d\n", count);

  free(haystack);
  free(needle);
  free(needle_lps);
}
