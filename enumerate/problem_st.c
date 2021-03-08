#include "problem_st.h"

// Grammar:
// expr ::= mult {+, -} expr | mult
// mult ::= term {*, /} mult | term
// term ::= ( expr ) | number

struct node_t *
build_syntax_tree(struct lex_array_t lexarr) {
  // TODO: your code here
}

int calc_result(struct node_t *top) {
  // TODO: your code here
}

void free_syntax_tree(struct node_t * top) {
  // TODO: your code here
}
