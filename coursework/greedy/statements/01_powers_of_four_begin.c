#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned powers_of_four(unsigned n, unsigned m);

int main()
{
    int n, m, outp, res;
    res = scanf("%d %d", &n, &m);
    assert((res == 2) && (n >= 0) && (m >= 0));
    outp = powers_of_four(n, m);
    printf("%d\n", outp);
    return 0;
}

#line 100001
