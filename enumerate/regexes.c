#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFLEN 128

int main() {
  regex_t regex;
  int res;
  char buf[BUFLEN];

#ifdef INTERACTIVE
  puts("Please input regex.\n");
#endif

  // Read regex. Try: ^a[[:alnum:]]
  res = scanf("%s", buf);
  if (res != 1)
    abort();

  // Compile regular expression
  res = regcomp(&regex, buf, 0);
  if (res) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

#ifdef INTERACTIVE
  puts("Regex compiled ok. Now input lines to test.\n");
#endif

  for (;;) {
    res = scanf("%s", buf);
    if (res != 1)
      break;
    // Execute regular expression
    res = regexec(&regex, buf, 0, NULL, 0);
    if (!res)
      puts("Match");
    else if (res == REG_NOMATCH)
      puts("No match");
    else {
      regerror(res, &regex, buf, sizeof(buf));
      fprintf(stderr, "Regex match failed: %s\n", buf);
    }
  }

  // Free memory allocated to the pattern buffer by regcomp()
  regfree(&regex);
}
