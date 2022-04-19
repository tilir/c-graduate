//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// LTO complex example, see also complex-part.c
//
// try:
// > gcc -O2 complex-main.c complex-part.c -flto
//
//-----------------------------------------------------------------------------

#include <stdio.h>

int step1();
int step3();
int step5();
int step7();
int step9();

int main() {
  int i, s = 0;
  for (i = 0; i < 10; ++i)
    s += step1();
  printf("%d steps performed\n", s);
}

int step2() {
  int i, s = 0;
  for (i = 0; i < 10; ++i)
    s += step3();
  return s;
}

int step4() {
  int i, s = 0;
  for (i = 0; i < 10; ++i)
    s += step5();
  return s;
}

int step6() {
  int i, s = 0;
  for (i = 0; i < 10; ++i)
    s += step7();
  return s;
}

int step8() {
  int i, s = 0;
  for (i = 0; i < 10; ++i)
    s += step9();
  return s;
}
