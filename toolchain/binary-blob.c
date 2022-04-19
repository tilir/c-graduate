//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Binary blob example:
//
// > dd if=/dev/urandom of=blob.bin bs=1 count=16
// > xxd -i blob.bin
// > objcopy -I binary -O elf64-x86-64 -B i386:x86-64 blob.bin blob.o
// > gcc binary-blob.c blob.o
//
//-----------------------------------------------------------------------------

#include <stdio.h>

extern unsigned char _binary_blob_bin_start[];
extern unsigned char _binary_blob_bin_end[];

int main() {
  int i;
  unsigned char *pblob = _binary_blob_bin_start;

  printf("Blob start: %llx\n", (unsigned long long)_binary_blob_bin_start);
  printf("Blob end: %llx\n", (unsigned long long)_binary_blob_bin_end);

  for (pblob = _binary_blob_bin_start; pblob < _binary_blob_bin_end; ++pblob)
    printf("0x%x ", (unsigned)*pblob);
  printf("\n");
}
