//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Test support of different extensions
// avx512f, "f" means "foundational"
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int main() {
  int have_sse = __builtin_cpu_supports("sse") ? 1 : 0;
  int have_avx512 = __builtin_cpu_supports("avx512") ? 1 : 0;
  printf("Have SSE: %d\n", have_sse);
  printf("Have AVX512: %d\n", have_avx512);
}
