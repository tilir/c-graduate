
#define VARIABLE 4
#define CONCAT(x, y) x ## _ ## y
#define EVAL(x, y) CONCAT(x, y)
#define NAME(x) EVAL(x, VARIABLE) 

extern void NAME(mine)(char *x);

