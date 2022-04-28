//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// gprof profiling issue
//
// try:
// > gcc -pg profil-gprof.c -O1 -g -o test-pg.x
// ./test-pg.x
// gprof test-pg.x gmon.out --width=120
//
// callgrind solution:
// > gcc profil-gprof.c -O1 -g -o test-cg.x
// > valgrind --tool=callgrind -- ./test-cg.x 1000
//
//-----------------------------------------------------------------------------

#include <stdlib.h>

#define NOOPT(x) asm("" ::"r,i"(x))

__attribute__((noinline)) void work(int n) {
  for (int i = 0; i < n; ++i) {
    NOOPT(i);
    for (int j = 0; j < n; ++j) {
      NOOPT(j);
    }
  }
}

#define SMALLAMT (1 << 5)
#define BIGAMT (1 << 16)

// easy task
void easy() { work(SMALLAMT); }

// hard task
void hard(int bigamt) { work(bigamt); }

// argument exists for callgrind runs
// try 1024 (still larger then 32 but callgrind will do).
int main(int argc, char **argv) {
  int bigamt = BIGAMT;
  if (argc > 1) {
    char *flag = NULL;
    bigamt = strtol(argv[1], &flag, 0);
  }
  easy();
  hard(bigamt);
}
