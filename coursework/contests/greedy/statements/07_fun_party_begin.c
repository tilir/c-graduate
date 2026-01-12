#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum { UNITLEN = 2 };

struct kid_t {
    int id;
    int age;
};

struct kidgroup_t {
    int nkid;
    int ngroup;
};

struct answer_t {
    int ngroups;
    struct kidgroup_t *mapping;
};

struct answer_t funparty(struct kid_t *kids, int nkids);

int main()
{
    int npoints, dummy, i, res;
    struct kid_t *kids;
    struct answer_t answ;

    res = scanf("%d %d", &npoints, &dummy);
    assert(res == 2 && npoints > 0);
    kids = (struct kid_t *) calloc(npoints, sizeof(struct kid_t));
    assert(kids != NULL);

    for (i = 0; i < npoints; ++i) {
        kids[i].id = i;
        res = scanf("%d", &kids[i].age);
        assert(res == 1);
    }

    answ = funparty(kids, npoints);

    printf("%d\n", answ.ngroups);
    free(kids);
    free(answ.mapping);
    return 0;
}

#line 100001
