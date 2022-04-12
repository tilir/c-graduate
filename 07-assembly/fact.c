//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// fact module for ABI demonstrations (see also main.c)
//
//-----------------------------------------------------------------------------

int fact(int x) {
  if (x < 2) return x;
  return fact(x - 1) * x;
}

