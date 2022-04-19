//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// LTO complex example, see also complex-main.c
//
//-----------------------------------------------------------------------------

int step2();
int step4();
int step6();
int step8();

int step1() {
  int i, s = 0;
  for (i = 0; i < 10; ++i)
    s += step2();
  return s;
}

int step3() {
  int i, s = 0;
  for (i = 0; i < 10; ++i)
    s += step4();
  return s;
}

int step5() {
  int i, s = 0;
  for (i = 0; i < 10; ++i)
    s += step6();
  return s;
}

int step7() {
  int i, s = 0;
  for (i = 0; i < 10; ++i)
    s += step8();
  return s;
}

int step9() { return 1; }
