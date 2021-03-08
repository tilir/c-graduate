#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *f;
  unsigned char c;
  int cnt = 0;

  if (argc < 2) {
    printf("Usage: <%s file-to-open>\n", argv[0]);
    return -1;
  }

  f = fopen(argv[1], "rb");
  
  if (f == NULL) {
    perror("File open error:");
    return -2;
  }

  while(fread(&c, sizeof(unsigned char), 1, f) == 1) {
    printf("%#02x\t", (unsigned) c);
    if (cnt == 8) {
      printf("\n");
      cnt = 0;
    }
    cnt += 1;
  }
  printf("\n");

  fclose(f);
}

