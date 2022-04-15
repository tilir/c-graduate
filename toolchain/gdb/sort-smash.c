//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Simple stack smashing example to demonstrate loop debugging
//
// > gcc -O1 -g -fno-stack-protector sort-smash.c -Wl,-z,execstack
// > while ./a.out; do echo "OK"; done;
//
// Disable stack execution protection:
// execstack -s a.out
//
// Next in gdb
// (gdb) b main --------> 2
// (gdb) b _Exit -------> 3
// (gdb) command 3
// run
// end
// (gdb) command 2
// record
// continue
// end
// (gdb) run
// (gdb) reverse-stepi
// (gdb) print $sp ----> sp-value
// (gdb) watch *(long **) sp-value
// (gdb) reverse-continue
//
// note: GLIBC_TUNABLES=glibc.cpu.hwcaps=-AVX2_Usable,-AVX_Fast_Unaligned_Load
// gdb ./a.out this may be required
//
//-----------------------------------------------------------------------------

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

// sort function: also buggy?

void sort(long *arr, unsigned n) {
  int i = 0;
  bool sorted;

  do {
    sorted = true;
    for (i = 0; i < (n - 1); i++) {
      long *item_one = &arr[i];
      long *item_two = &arr[i + 1];
      long swap_store;

      if (*item_one <= *item_two)
        continue;

      sorted = false;
      swap_store = *item_two;
      *item_two = *item_one;
      *item_one = swap_store;
    }
  } while (!sorted);
}

void out_array(long *arr, unsigned n) {
  int i;

  printf("[");
  for (i = 0; i < (n - 1); i++)
    printf("%ld, ", arr[i]);
  printf("%ld]\n", arr[n - 1]);
}

// caller

int main() {
  long array[32];
  int i;

  srand(time(NULL));
  for (i = 0; i < rand() % sizeof array; i++)
    array[i] = rand();

  out_array(array, 32);

  sort(array, 32);

  out_array(array, 32);

  return 0;
}
