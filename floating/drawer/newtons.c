//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
// 
// Newton fractal example
//
// cl /EHsc /O2 /std:c11 newtons.c sdlutil.c /Fe:newtons /link SDL2.lib
// gcc -O2 newtons.c sdlutil.c -lm -lSDL2
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

#include "drawer.h"

const int def_bigsize = 1000;
const int def_xsize = 1024;
const int def_ysize = 768;
const unsigned black = 0xff1010ff;
const unsigned white = 0xffffffff;
const unsigned maxiter = 35;
const double ARGSTEP = 0.01;

struct newton_data {
  complex double *pcenter;
  double *psz;
};

static complex double next_newton(complex double z) {
  complex double numerator = z * z * z - 1;
  complex double denominator = 3 * z * z;
  return z - numerator / denominator;
}

static void draw_newton(struct Surface *s, void *pdata) {
  const unsigned char clblue = 0xaa;
  const unsigned cmod = 16;

  complex double center = *(((struct newton_data *)pdata)->pcenter);
  double sz = *(((struct newton_data *)pdata)->psz);

  double scale = 50.0;
  complex double roots[3] = {CMPLX(1.0, 0.0), CMPLX(-0.5, 0.866), CMPLX(-0.5, -0.866)};

  int xsize = Surface_w(s);
  int ysize = Surface_h(s);
  Surface_fillwith(s, white);
  for (int ix = -xsize / 2; ix < xsize / 2; ix += 1)
    for (int iy = -ysize / 2; iy < ysize / 2; iy += 1) {
      double x = 2.0 * sz * ix / def_bigsize;
      double y = 2.0 * sz * iy / def_bigsize;
      double r, g, b;
      complex double z = CMPLX(creal(center) + x, cimag(center) + y);
      unsigned cl = buildcolor(0, 0, 0, clblue);

      for (unsigned i = 0; i < maxiter; ++i)
        z = next_newton(z);
      
      r = cabs(z - roots[0]);
      g = cabs(z - roots[1]);
      b = cabs(z - roots[2]);
      
      cl = buildcolor(0, max(0xff - r * scale, 0), max(0xff - g * scale, 0), max(0xff - b * scale, 0));
      Surface_putpixel(s, ix + (xsize / 2), iy + (ysize / 2), cl);
    }
}

void keybind(struct ViewPort *vp, struct KeyPressed kp, bool is_down,
             void *data) {
  struct newton_data *pdata = (struct newton_data *)data;
  if (Key_IsRegular(kp) && is_down) {
    switch (Key_GetRegular(kp)) {
    case '-':
      *pdata->psz += 0.01;
      break;
    case '+':
      *pdata->psz -= 0.01;
      break;
    }
  }
  if (Key_IsSpecial(kp) && is_down) {
    switch (Key_GetSpecial(kp)) {
    case KEY_UP:
      *pdata->pcenter += CMPLX(0.0, 0.01);
      break;
    case KEY_DOWN:
      *pdata->pcenter += CMPLX(0.0, -0.01);
      break;
    case KEY_LEFT:
      *pdata->pcenter += CMPLX(-0.01, 0.0);
      break;
    case KEY_RIGHT:
      *pdata->pcenter += CMPLX(0.01, 0.0);
      break;
    }
  }
}

int
#if defined(_WIN32) || defined(WIN32)
WinMain(HINSTANCE h, HINSTANCE g, LPSTR s, int n)
#else
main(int argc, char **argv)
#endif
{
  complex double center = CMPLX(-0.25, 0.0);
  double sz = 0.5;
  struct newton_data nd = {&center, &sz};

  double step = 0.1;
  struct ViewPort *v = ViewPort_query(def_xsize, def_ysize, draw_newton, (void *)&nd, true);
  ViewPort_bind(v, keybind);
  while (ViewPort_poll(v) == PROCEED) {
  }
  ViewPort_destroy(v);
}
