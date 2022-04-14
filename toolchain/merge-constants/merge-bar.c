//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// merge constants: second module
//
//-----------------------------------------------------------------------------

float use(float x);

int bar() {
  float x = 1.0f;
  use(x);
  return (int)x;
}
