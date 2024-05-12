#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
    int n;
    unsigned char *mod1;
    unsigned char *mod5;
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
int is_prime(struct sieve_t *sv, unsigned n);

int nth_prime(struct sieve_t *s, int N)
{
    int cnt, p;
    if (N == 1)
        return 2;
    if (N == 2)
        return 3;

    cnt = 2;
    p = 5;

    for (; ; ) {
        if (is_prime(s, p)) {
            cnt += 1;
            if (cnt == N)
                break;
        }
        p += 2;
        if (is_prime(s, p)) {
            cnt += 1;
            if (cnt == N)
                break;
        }
        p += 4;
    }

    return p;
}

int main()
{
    int n, outp;
    int res;
    struct sieve_t *s;

    res = scanf("%d", &n);
    assert(res == 1);
    s = (struct sieve_t *) malloc(sizeof(struct sieve_t));
    s->n = ((sieve_bound(n) / CHAR_BIT) / 6) + 1;
    s->mod1 = (unsigned char *) calloc(s->n, sizeof(char));
    s->mod5 = (unsigned char *) calloc(s->n, sizeof(char));

    fill_sieve(s);

#if 0
    {
        int i = 0, k = 0;
        printf("primes:\n");
        while (k < n) {
            if (is_prime(s, i)) {
                printf("%d ", i);
                k += 1;
            }
            i += 1;
        }
        printf("\n");
    }
#endif

    outp = nth_prime(s, n);
    printf("%d\n", outp);

    free(s->mod1);
    free(s->mod5);
    free(s);
}

#line 10000
