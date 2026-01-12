#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int coverpoints(int *pts, int n, int unitlen);

int main()
{
    int npoints, unitlen, i, res;
    int *points;

    res = scanf("%d %d", &npoints, &unitlen);
    assert(res == 2 && npoints > 0 && unitlen > 0);
    points = (int *) calloc(npoints, sizeof(int));
    assert(points != NULL);

    for (i = 0; i < npoints; ++i) {
        res = scanf("%d", points + i);
        assert(res == 1);
    }

    res = coverpoints(points, npoints, unitlen);

    printf("%d\n", res);
    free(points);
    return 0;
}

#line 100001
