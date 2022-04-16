//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// simple benchmark infra
//
//-----------------------------------------------------------------------------

#pragma once

#include <stdlib.h>
#include <time.h>

#ifdef _MSC_VER
#include <intrin.h>  // for _ReadWriteBarrier
#include <windows.h> // for GetSystemTimeAsFileTime
#endif

const int MICROSEC_AS_NSEC = 1000;
const int SEC_AS_NSEC = 1000000000;
#define SEC_AS_MICROSEC (SEC_AS_NSEC / MICROSEC_AS_NSEC)

// return difference between timestamps in seconds
static double diff(struct timespec start, struct timespec end) {
  struct timespec temp;
  if (end.tv_nsec - start.tv_nsec < 0) {
    temp.tv_sec = end.tv_sec - start.tv_sec - 1;
    temp.tv_nsec = SEC_AS_NSEC + end.tv_nsec - start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec - start.tv_sec;
    temp.tv_nsec = end.tv_nsec - start.tv_nsec;
  }
  double msec = temp.tv_sec * SEC_AS_MICROSEC + temp.tv_nsec / MICROSEC_AS_NSEC;
  return msec / SEC_AS_MICROSEC;
}

static void maybe_readopt(int argc, char **argv, int n, int *x) {
  if (argc > n) {
    char *flag = NULL;
    *x = strtol(argv[n], &flag, 0);
  }
}

// do not optimize x away
#ifdef _MSC_VER
#include <intrin.h> // for _ReadWriteBarrier
static void __declspec(noinline) UseCharPointer(char const volatile *n) {}
static inline void noopt(int value) {
  UseCharPointer((char const volatile *)&value);
  _ReadWriteBarrier();
}
#define NOOPT(x) noopt(x)
#else
// things are much simpler for GCC and LLVM
#define NOOPT(x) asm("" ::"r,i"(x))
#endif

#ifdef _MSC_VER
#define CLOCKTYPE 0
#define FILETIME_TO_SEC 10000000i64
#define FILETIME_TO_NSEC 100
#define WINTIME_OFF 116444736000000000i64 // 1.jan.1601 to 1.jan.1970

static __int64 convftime(FILETIME fTime) {
  ULARGE_INTEGER large;
  large.LowPart = fTime.dwLowDateTime;
  large.HighPart = fTime.dwHighDateTime;
  return large.QuadPart;
}

static int clock_gettime(int X, struct timespec *spec) {
  __int64 wintime;
  // Contains a 64-bit value representing the number of 100-nanosecond intervals
  // since January 1, 1601 (UTC).
  FILETIME ftime;
  GetSystemTimeAsFileTime(&ftime);
  // build int64 from two dwords
  wintime = convftime(ftime);
  wintime -= WINTIME_OFF;
  spec->tv_sec = wintime / FILETIME_TO_SEC;
  spec->tv_nsec = (wintime % FILETIME_TO_SEC) * FILETIME_TO_NSEC;
  return 0;
}
#else
#define CLOCKTYPE CLOCK_PROCESS_CPUTIME_ID
#endif

static void simple_gettime(struct timespec *spec) {
  clock_gettime(CLOCKTYPE, spec);
}
