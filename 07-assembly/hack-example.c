//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Simple hack example (requires hex editor)
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

int g_code;
int g_code2;

int check() {
  return (g_code2 == g_code);
}

int main() {
  int code, res;
  printf("Enter code: ");
  res = scanf("%d", &code);
  if (!res) abort();
  g_code = code;
  g_code2 = code + 1;
  if (!check())
   abort();
  printf("Victory\n");
}

