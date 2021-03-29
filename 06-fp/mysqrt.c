#include <math.h>
#include <stdio.h>

float tests[] = {2, 3, 5, 7, 9, 11};

union fltbits {
  float f;
  unsigned u;
};

float mysqrt(float x) {
  union fltbits u;
  u.f = x;
  u.u = (u.u >> 1) + (0x3f800000 >> 1);

  u.f = (u.f * u.f + x) / (2.0f * u.f);
  u.f = (u.f * u.f + x) / (2.0f * u.f);

  return u.f;
}

int main() {
  int i;
  int ntests = sizeof(tests) / sizeof(tests[0]);

  for (i = 0; i < ntests; ++i)
    fprintf(stdout, "%f: %.6f vs %.6f\n", 
            tests[i], sqrtf(tests[i]), mysqrt(tests[i]));  
}

