//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Simple breakpoint mechanics explanation
//
// Compile with debug info.
// Run, see checksum.
// Run under gdb, break last printf, see checksum.
//
//-----------------------------------------------------------------------------

#include <stdio.h>

__attribute__((noinline)) void *foo() { return __builtin_return_address(0); }

int main() {
  void *curip = foo();
  int checksum = 0;
  unsigned char prevbyte = 0;
  printf("Current function address: 0x%lx\n", (long)curip);

  printf("Contents:\n");
  for (int i = 0;; ++i) {
    unsigned char nextbyte = *((unsigned char *)curip + i);
    printf("\t0x%hhx", nextbyte);
    if (((i + 1) % 16) == 0)
      printf("\n");
    checksum += nextbyte;
    if ((prevbyte == 0xc9) && (nextbyte == 0xc3))
      break;
    prevbyte = nextbyte;
  }

  printf("\nCurrent function checksum: %d\n", checksum);
}
