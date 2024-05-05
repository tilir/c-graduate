//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
// 
// Julia set example
//
// default is -7.0 0.0
// try also -0.7 0.1, -0.7 0.2 and -0.7 0.5
//          -0.9 0.2 is equally well
//          0.3 0.7 awesome
//
// cl /EHsc /O2 /std:c11 julia.c sdlutil.c /Fe:julia /link SDL2.lib shell32.lib
// gcc -O2 -flto -ffast-math newtons.c sdlutil.c -lm -lSDL2
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
const unsigned maxiter = 50;
const double ARGSTEP = 0.01;

struct julia_data {
  complex double *pc; 
  complex double *pcenter;
  double *psz;
};

static complex double next_newton(complex double z) {
  complex double numerator = z * z * z - 1;
  complex double denominator = 3 * z * z;
  return z - numerator / denominator;
}

static complex double next(complex double z, complex double c) {
  return z * z + c;
}

static void draw_julia(struct Surface *s, void *data) {  
  const unsigned char clblue = 0xaa;
  const unsigned cmod = 8;

  struct julia_data *jd = (struct julia_data *) data;
  complex double c = *jd->pc;
  complex double center = *jd->pcenter;
  double sz = *jd->psz;

  int xsize = Surface_w(s);
  int ysize = Surface_h(s);
  Surface_fillwith(s, white);
  for (int ix = -xsize / 2; ix < xsize / 2; ix += 1)
    for (int iy = -ysize / 2; iy < ysize / 2; iy += 1) {
      double x = 2.0 * sz * ix / def_bigsize;
      double y = 2.0 * sz * iy / def_bigsize;
      complex double z = CMPLX(creal(center) + x, cimag(center) + y);
      unsigned cl = buildcolor(0, 0, 0, clblue);

      for (unsigned i = 0; i < maxiter; ++i) { 
        if (cabs(z) > max(2.0 * sz, 4.0)) {
          cl = buildcolor(0, (i * cmod) & 0xFF, (i * cmod) & 0xFF, clblue);
          break;
        }
        z = next(z, c);
      }

      Surface_putpixel(s, ix + (xsize / 2), iy + (ysize / 2), cl);
    }
}

int
#if defined(_WIN32) || defined(WIN32)
WinMain(HINSTANCE h, HINSTANCE g, LPSTR s, int n)
#else
main(int argc, char **argv)
#endif
{
  complex double c = CMPLX(-0.7, 0.0);
  complex double center = CMPLX(0.0, 0.0);
  clock_t start_phase = clock();

#if defined(_WIN32) || defined(WIN32)
  int argc;
  LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
#else
#endif

  if (argc == 3) {
#if defined(_WIN32) || defined(WIN32)
    double re = _wtof(argv[1]);
    double im = _wtof(argv[2]);
#else
    double re = atof(argv[1]);
    double im = atof(argv[2]);
#endif
    c = CMPLX(re, im);
  }

  double abs = cabs(c);
  double arg = acos(creal(c) / abs);
  double argmul = 1.0;
  double sz = 2.0;
  bool pause = false;
  struct julia_data jd = {&c, &center, &sz};
  struct ViewPort *v = ViewPort_query(def_xsize, def_ysize, draw_julia, &jd, true);
  
  while (ViewPort_poll(v) == PROCEED) {
    const double SPEEDUP = 0.3;
    clock_t phase = clock();
    double dph = phase;
    double dphase = SPEEDUP * ((dph - start_phase) / CLOCKS_PER_SEC);
    start_phase = phase;
    
    if (!pause)
      arg += argmul * dphase;
    c = CMPLX(abs * cos(arg), abs * sin(arg));
  }

  ViewPort_destroy(v);
}
