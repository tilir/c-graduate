//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// how we are loosing in instruction count
//
// gcc -O2 -S loose.c -o loose-x86.s
// riscv64-linux-gnu-gcc -march=rv64imfd -O2 -S loose.c -o loose-rv.s
// riscv64-linux-gnu-gcc -march=rv64imfd -O2 -c loose.c
// riscv64-linux-gnu-objdump -d loose.o
// riscv64-linux-gnu-gcc -march=rv64imfdc -O2 -c loose.c
// riscv64-linux-gnu-objdump -d loose.o
//
//-----------------------------------------------------------------------------

int elt(int *arr, long n) {
  return arr[n + 2];
}
