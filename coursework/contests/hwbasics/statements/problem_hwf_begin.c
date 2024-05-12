#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int next_turn(int total, int possible);

int main()
{
    int n, q, res;

    res = scanf("%d%d", &n, &q);
    assert(res == 2);

    n = next_turn(n, q);
    printf("%d\n", n);

    return 0;
}

#line 1001
