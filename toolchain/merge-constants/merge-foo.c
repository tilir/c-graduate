//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// merge constants: first module
//
//-----------------------------------------------------------------------------

float use(float x);

int foo() {
  float x = 1.0f;
  use(x);
  return (int)x;
}
