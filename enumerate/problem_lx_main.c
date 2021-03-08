#include "problem_lx.h"

enum { MAXLEN = 1024 };

int test_dump() {
  struct lexem_t lxs[5] = {
    {BRACE, LBRAC}, {NUM, 2}, {OP, MUL}, {NUM, 2}, {BRACE, RBRAC}
  };
  
  struct lex_array_t larr = {lxs, 5, 5}; 
  dump_lexarray(larr);
}

int main() {
  int res;
  struct lex_array_t larr;
  char inp[MAXLEN] = {0};
  
  res = scanf("%1023c", inp);
  assert(res == 1);
  
  larr = lex_string(inp);

  if (larr.lexems == NULL) {
    printf("ERROR\n");
    return 0;
  }

  dump_lexarray(larr);

  free(larr.lexems);
  return 0;
}
