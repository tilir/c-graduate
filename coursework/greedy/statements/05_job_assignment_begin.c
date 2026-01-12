#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct order_t {
    int number;
    int cost;
    int deadline;
};

struct answer_t {
    int norders;
    int *numbers;
};

struct answer_t betforjobs(struct order_t *orders, int n, int totaltime);

// name, mangled to be never used in submission
static int internal__order_number_comparator__(const void *fst,
                                               const void *snd)
{
    struct order_t *ifst = (struct order_t *) fst;
    struct order_t *isnd = (struct order_t *) snd;
    return (ifst->number - isnd->number);
}

int main()
{
    int ndays, norders, i, total = 0, res;
    struct order_t *orders;
    struct answer_t result;

    res = scanf("%d %d", &ndays, &norders);
    assert(res == 2 && ndays > 0 && norders > 0);
    orders = (struct order_t *) calloc(norders, sizeof(struct order_t));
    assert(orders != NULL);

    for (i = 0; i < norders; ++i) {
        orders[i].number = i;
        res = scanf("%d %d", &orders[i].cost, &orders[i].deadline);
        assert(res == 2 && orders[i].deadline >= 0
               && orders[i].deadline < ndays);
    }

    result = betforjobs(orders, norders, ndays);

    // sort orders back to restore numbers
    qsort(orders, norders, sizeof(struct order_t),
          internal__order_number_comparator__);

    for (i = 0; i < result.norders; ++i)
        if (result.numbers[i] > -1)
            total += orders[result.numbers[i]].cost;

    printf("%d\n", total);

    free(orders);
    free(result.numbers);
    return 0;
}

#line 100001
