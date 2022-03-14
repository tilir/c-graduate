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
//
//-----------------------------------------------------------------------------

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

#include "drawer.h"
#include "cmplx.h"

const int def_bigsize = 1000;
const int def_xsize = 1024;
const int def_ysize = 768;
const unsigned black = 0xff1010ff;
const unsigned white = 0xffffffff;
const unsigned maxiter = 50;
const double ARGSTEP = 0.01;

struct julia_data {
  struct cmplx *pc; 
  struct cmplx *pcenter;
  double *psz;
};

static void draw_julia(struct Surface *s, void *data) {  
  const unsigned char clblue = 0xaa;
  const unsigned cmod = 8;

  struct julia_data *jd = (struct julia_data *) data;
  struct cmplx c = *jd->pc;
  struct cmplx center = *jd->pcenter;
  double sz = *jd->psz;

  int xsize = Surface_w(s);
  int ysize = Surface_h(s);
  Surface_fillwith(s, white);
  for (int ix = -xsize / 2; ix < xsize / 2; ix += 1)
    for (int iy = -ysize / 2; iy < ysize / 2; iy += 1) {
      double x = 2.0 * sz * ix / def_bigsize;
      double y = 2.0 * sz * iy / def_bigsize;
      struct cmplx z = { center.re + x, center.im + y };
      unsigned cl = buildcolor(0, 0, 0, clblue);

      for (unsigned i = 0; i < maxiter; ++i) {
        if (sqrt(z.re * z.re + z.im * z.im) > max(2.0 * sz, 4.0)) {
          cl = buildcolor(0, (i * cmod) & 0xFF, (i * cmod) & 0xFF, clblue);
          break;
        }
        z = cmplx_add(cmplx_mul(z, z), c);
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
  struct cmplx c = {-0.7, 0.0};
  struct cmplx center = {0.0, 0.0};
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
    double re = std::atof(argv[1]);
    double im = std::atof(argv[2]);
#endif
    c.re = re;
    c.im = im;
  }

  double abs = sqrt(c.re * c.re + c.im * c.im);
  double arg = acos(c.re / abs);
  double argmul = 1.0;
  double sz = 2.0;
  bool pause = false;
  int dumpnum = 0;
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
    c.re = abs * cos(arg);
    c.im = abs * sin(arg);
  }

  ViewPort_destroy(v);
}