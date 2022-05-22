//
//  BT.c
//  AP_Exam012022
//
//  Created by Oskar Bich on 28/1/22.
//

#include "BT.h"

typedef struct node *link;

struct node {
    int val;
    link r, l;
};

struct BT_t {
    link h;
    int dim;
};

link addNode(int val, link l, link r);
void checkR(link h, int *nok);

BT BTinit(void) {
    BT t = malloc(sizeof(*t));
    t->h = NULL;
    t->dim = 0;
    return t;
}

void loadEx2(BT t) {
    t->h = addNode(3, addNode(2, addNode(1, NULL, NULL), NULL), addNode(5, addNode(4, NULL, NULL), addNode(6, NULL, NULL)));
}

int checkBT(BT t) {
    int nok = 0;
    checkR(t->h, &nok);
    return nok;
}

void checkR(link h, int *nok) {
    if (h == NULL)
        return;
    if (h->l != NULL && h->l->val > h->val) {
        *nok = 1;
        return;
    }
    if (h->r != NULL && h->r->val < h->val) {
        *nok = 1;
        return;
    }
    checkR(h->l, nok);
    checkR(h->r, nok);
}

link addNode(int val, link l, link r) {
    link x = malloc(sizeof(*x));
    x->val = val;
    x->l = l;
    x->r = r;
    return x;
}
