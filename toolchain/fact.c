//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// fact module for multi-module demonstrations (see also main.c)
//
//-----------------------------------------------------------------------------

#ifdef INC
#include "fact.h"
#endif

unsigned fact(unsigned x) {
  if (x < 2)
    return 1;

  return x * fact(x - 1);
}
