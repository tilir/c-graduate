#include "problem_st.h"

enum { MAXLEN = 1024 };

int main() {
  int res, result;
  struct lex_array_t larr;
  struct node_t *stree;
  char inp[MAXLEN] = {0};
  
  res = scanf("%1023c", inp);
  assert(res == 1);
  
  // lex to array of lexems
  larr = lex_string(inp);
  
  if (larr.lexems == NULL) {
    printf("ERROR\n");
    return 0;
  }
  
  stree = build_syntax_tree(larr);

  result = calc_result(stree);
  
  printf("%d\n", result);

  free_syntax_tree(stree);
  free(larr.lexems);
  return 0;
}
