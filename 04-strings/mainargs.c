#include "stdio.h"
#include "string.h"

void print_plus(const char *p) {
  const char *arg;
  for (arg = p; *arg != '\0'; ++arg)
    printf("%c", (*arg == '-') ? '+' : *arg);
  printf("\n");
}

int
main(int argc, char **argv) {
  int i; const char *arg;
  int rev = 0; 

  for (i = 1; i < argc; ++i)
    if (!strcmp(argv[i], "-r")) {
      rev = 1;
      break;
    }

  if (!rev) {
    for (i = 1; i < argc; ++i)
      print_plus(argv[i]);
  } else {
    for (i = argc - 1; i > 0; --i)
      print_plus(argv[i]);
  }
  
}
