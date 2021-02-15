#include <stdio.h>

void read_input(int*, int*);

int main () {
  int a, b, p, q;
  read_input(&a, &b);
  p = a / b;
  q = a % b;
  printf("p: %d, q: %d\n", p, q);  
}  

void read_input(int *pa, int *pb) {
 for (;;) {
    int nitems;
    printf("input a and b: ");
    nitems = scanf("%d %d", pa, pb);
    if ((nitems == 2) && (*pb != 0))
      break;
    printf("Wrong input!\n");
    rewind(stdin);
  }
}
