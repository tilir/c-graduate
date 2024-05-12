#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct sieve_t {
    int n;
    char *s;
};

int sieve_bound(int num)
{
    double dnum, dres;
    if (num <= 20)
        return 100;
    dnum = num;
    dres = dnum * (log(dnum) + log(log(dnum)));
    return (int) round(dres);
}

void fill_sieve(struct sieve_t *s);
int nth_prime(struct sieve_t *s, int N);

int main()
{
    int n, outp;
    int res;
    struct sieve_t *s;

    res = scanf("%d", &n);
    assert(res == 1);
    s = (struct sieve_t *) malloc(sizeof(struct sieve_t));
    s->n = sieve_bound(n);
    s->s = (char *) calloc(s->n, sizeof(char));

    fill_sieve(s);
    outp = nth_prime(s, n);
    printf("%d\n", outp);

    free(s->s);
    free(s);
}

#line 10000
