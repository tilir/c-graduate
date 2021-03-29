//------------------------------------------------------------------------------
//
// Julia set in C
//
//------------------------------------------------------------------------------
//
// default is -7.0 0.0
// try also -0.7 0.1, -0.7 0.2 and -0.7 0.5
//          -0.9 0.2 is equally well
//          0.3 0.7 awesome
//
//------------------------------------------------------------------------------

#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "drawer.h"

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

typedef double complex cdt;

const int def_bigsize = 1000;
const int def_xsize = 1024;
const int def_ysize = 768;
const unsigned black = 0xff1010ff;
const unsigned white = 0xffffffff;
const unsigned maxiter = 100;
const double ARGSTEP = 0.01;
const double sq2 = sqrt(2.0);

struct julia_data_t {
  cdt c;
  cdt center;
  double sz;
};

// analogue to std::max
static double max(double x, double y) {
  if (x > y) return x;
  return y;
}

void draw_julia(struct surface_t* s, void *data) {  
  const unsigned char clblue = 0xaa;
  const unsigned cmod = 8;
  int xsize, ysize, ix, iy;
  unsigned i;
  cdt c, center;
  double sz;
  struct julia_data_t *jdata = (struct julia_data_t *) data;
 
  assert(s);
  assert(jdata);

  c = jdata->c;
  center = jdata->center;
  sz = jdata->sz;

  xsize = surface_width(s);
  ysize = surface_height(s);
  surface_fillwith(s, white);
  for (ix = -xsize / 2; ix < xsize / 2; ix += 1)
    for (iy = -ysize / 2; iy < ysize / 2; iy += 1) {
      double x = 2.0 * sz * ix / def_bigsize;
      double y = 2.0 * sz * iy / def_bigsize;
      cdt z = center + x + 1.0i * y;
      unsigned cl = buildcolor(0, 0, 0, clblue);

      for (i = 0; i < maxiter; ++i) {
        if (cabs(z) > max(2.0 * sz, 4.0)) {
          cl = buildcolor(0, i * cmod, i * cmod, clblue);
          break;
        }
        z = z * z + c;
      }

      surface_putpixel(s, ix + (xsize / 2), iy + (ysize / 2), cl);
    }
}

struct key_data_t {
  cdt *center;
  double *abs;
  double *arg;
  double *argmul;
  double *sz;
  bool *pause;
  int *dumpnum;
  struct viewport_t *v;
};

void key_control(struct keypressed_t k, void *data) {
  cdt *center;
  double *abs;
  double *arg;
  double *argmul;
  double *sz;
  bool *pause;
  int *dumpnum;

  struct key_data_t *kd = data;
  assert(kd);

  center = kd->center;
  abs = kd->abs;
  arg = kd->arg;
  argmul = kd->argmul;
  sz = kd->sz;
  pause = kd->pause;
  dumpnum = kd->dumpnum;
  
  if (is_special(&k)) {
    switch(special(&k)) {
      case KEY_UP:
        *center -= 0.1 * I * *sz;
        break;
      case KEY_DOWN:
        *center += 0.1 * I * *sz;
        break;
      case KEY_LEFT:
        *center -= 0.1 * *sz;
        break;
      case KEY_RIGHT:
        *center += 0.1 * *sz;
        break;
    }
  }
  else {
    switch(regular(&k)) {
      case '+':
        *sz -= 0.1 * *sz;
        break;
      case '-':
        *sz += 0.1 * *sz;
        break;
      case 'p':
        *pause = !*pause;
        break;
      case 's':
        *arg += *argmul * *sz * ARGSTEP;
        break;
      case 'd': {
        char name[1024] = {0};
        sprintf(name, "julia%d.bmp", *dumpnum);          
        dump(kd->v, name);
        *dumpnum += 1;
        break;
      }
      case 'r':
        *argmul = -*argmul;
        break;
    }
  }
}

int
#if defined(_WIN32) || defined(WIN32)
WinMain (HINSTANCE, HINSTANCE, LPSTR, int)
#else
main (int argc, char **argv)
#endif
{
  cdt c = -0.7;
  cdt center = 0.0;
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
    c = re + 1.0 * I * im;
  }

  double abs = cabs(c);
  double arg = carg(c);
  double argmul = 1.0;
  double sz = 2.0;
  bool pause = false;
  int dumpnum = 0;
  struct viewport_t *v;

  struct key_data_t kd = { &center, &abs, &arg, &argmul, &sz, &pause, &dumpnum, v};

  struct julia_data_t jd = { c, center, sz };

  v = query_viewport(def_xsize, def_ysize, &draw_julia, &jd);
  bindkeys(v, key_control, &kd);

  while (viewport_poll(v) == PROCEED) {
    const double SPEEDUP = 0.3;
    clock_t phase = clock();
    double dph = phase;
    double dphase = SPEEDUP * ((dph - start_phase) / CLOCKS_PER_SEC);
    start_phase = phase;
    
    if (!pause)
      arg += argmul * dphase;
    c = abs * cos(arg) + I * abs * sin(arg);
  }

  free_viewport();
}



