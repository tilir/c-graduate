//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Float ABI and double ABI
//
// riscv64-linux-gnu-gcc -march=rv64g fltdbl.c -O2 -S
// riscv64-linux-gnu-gcc -march=rv64i fltdbl.c -O2 -S
// riscv64-linux-gnu-gcc -march=rv64i -mabi=lp64 fltdbl.c -O2 -S
// riscv64-linux-gnu-gcc -march=rv64ifd -mabi=lp64 fltdbl.c -O2 -S
//
// interesting case:
// riscv64-linux-gnu-gcc -march=rv64id fltdbl.c -O2 -S
//
//-----------------------------------------------------------------------------

int fto_int(float f) {
  return f;
}

int dto_int(double d) {
  return d;
}
