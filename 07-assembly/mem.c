//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Module to show working with memory
//
//-----------------------------------------------------------------------------

void fill(int *);

int foo(int i) {
  int arr2[10]; // filler
  int arr[5];
  int arr3[10]; // filler
  fill(arr);
  fill(arr2);
  fill(arr3);
  return arr[i] + arr2[i] + arr3[i];
}

int bar(int *p, int i) {
  int arr[5];
  fill(arr);
  return arr[i] + p[i]; 
}

int a;
int garr[5];
int *gp;

int buz(int i) {
  return a + garr[i] + gp[i];
}

