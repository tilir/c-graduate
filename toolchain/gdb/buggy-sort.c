//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// buggy sort: main gdb functionality
//
// Ctrl+x+a --> enter or leave
// Ctrl+x+o --> switch active window
// layout src
// info frame
// backtrace
// x/2x $sp
// x/2xg $sp
// (gdb) set $i=0
// (gdb) set $end=m
// (gdb) while ($i < $end)
// p a[$i++].key
// end
// (gdb) p *a@5
//
//-----------------------------------------------------------------------------

#include <stdio.h>

typedef struct {
  char *data;
  int key;
} item;

item array[] = {
    {"Bill", 62}, {"Hill", 60}, {"Barrak", 42}, {"Dicky", 105}, {"W.", 1},
};

/* Simple but buggy bubble sort  *
 * Can you find the bugs?        */
void sort(item *a, int n) {
  int i = 0, j = 0;
  int s = 1;

  for (; i < n && s != 0; i++) {
    s = 0;
    for (j = 0; j < n; j++)
      if (a[j].key > a[j + 1].key) {
        item t = a[j];
        a[j] = a[j + 1];
        a[j + 1] = t;
        s++;
      }
    n--;
  }
}

void print_arr(item *a, int n) {
  int i;

  for (i = 0; i != n; ++i)
    printf("%d: %s\n", a[i].key, a[i].data);
}

int main() {
  print_arr(array, 5);
  sort(array, 5);
  printf("\nAfter sort:\n");
  print_arr(array, 5);
  return 0;
}
