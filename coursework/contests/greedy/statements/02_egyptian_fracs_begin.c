#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct denom_array_t {
    unsigned *arr;
    unsigned sz;
};

struct denom_array_t egyptian_fractions(unsigned n, unsigned m);

int main()
{
    unsigned i, n, m, res;
    struct denom_array_t outp;
    res = scanf("%u %u", &n, &m);
    assert(res == 2);
    outp = egyptian_fractions(n, m);
    assert(outp.sz > 0);

    for (i = 0; i < outp.sz; ++i)
        printf("%u ", outp.arr[i]);
    printf("\n");
    free(outp.arr);
    return 0;
}

#line 100001
