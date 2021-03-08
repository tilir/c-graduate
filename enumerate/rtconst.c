#include <stdio.h>

//enum result { Ok = 0, Failed = -1};

enum state { Working = 0, Failed, Freezed };

enum { asize = 5 };
int a[asize];

int foo() {
  enum state { Working = 6, Failed = 12, Freezed };
  int t = 4;
  enum state s = t;
  s += 1;
  enum state *ps = &s;
}

enum DTS { DT_DAY = 0, DT_TIME };
struct DT {
 enum DTS what;
 union DayOrTime {
   int day;
   time_t time;
 } u;
};

struct DT d = { DT_DAY, {42} };
struct DT d1 = { .what = DT_DAY, .u.day = 42 };


int
main () {
  const int j = a[0];
}

