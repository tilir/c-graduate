#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct intvl_t {
    int number;
    int start;
    int fin;
};

int schedulemax(struct intvl_t *reqs, int nreqs);

int main()
{
    int n, res, i;
    struct intvl_t *arr;

    res = scanf("%d", &n);
    assert(res == 1 && n > 0);
    arr = (struct intvl_t *) calloc(n, sizeof(struct intvl_t));
    assert(arr != NULL);

    for (i = 0; i < n; ++i) {
        arr[i].number = i;
        res = scanf("%d %d", &arr[i].start, &arr[i].fin);
        assert(res == 2);
    }

    res = schedulemax(arr, n);
    printf("%d\n", res);

    free(arr);
    return 0;
}

#line 100001
