#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct intvl_t {
    int number;
    int start;
    int fin;
};

int covermin(int L, int R, struct intvl_t *intervs, int nintervs);

int main()
{
    int n, l, r, res, i;
    struct intvl_t *arr;

    res = scanf("%d %d %d", &l, &r, &n);
    assert(res == 3 && l > 0 && r > 0 && n > 0);
    arr = (struct intvl_t *) calloc(n, sizeof(struct intvl_t));
    assert(arr != NULL);

    for (i = 0; i < n; ++i) {
        arr[i].number = i;
        res = scanf("%d %d", &arr[i].start, &arr[i].fin);
        assert(res == 2);
    }

    res = covermin(l, r, arr, n);
    printf("%d\n", res);

    free(arr);
    return 0;
}

#line 100001
