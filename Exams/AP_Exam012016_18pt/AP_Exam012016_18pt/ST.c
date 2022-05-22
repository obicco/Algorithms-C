//
//  ST.c
//  AP_Exam012016_18pt
//
//  Created by Oskar Bich on 15/3/22.
//

#include "ST.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct symboltable {
    int n, max;
    Item *v;
};

Item ItemCreate(char *name, int pop, int dist) {
    Item val;
    val.name = strdup(name);
    val.pop = pop;
    val.dist = dist;
    return val;
}

ST Stinit(int maxN) {
    ST st = malloc(sizeof(*st));
    st->max = maxN;
    st->n = 0;
    st->v = malloc(maxN*sizeof(Item));
    return st;
}

void STfree(ST st){
    free(st->v);
    free(st);
}

int STserchbyname(ST st, char *name) {
    for (int i = 0; i < st->n; i++)
        if (strcmp(st->v[i].name, name) == 0)
            return i;
    return -1;
}

void STprint(ST st) {
    for (int i = 0; i < st->n; i++)
        printf("%2d | %15s | %3d | %3d\n", i, st->v[i].name, st->v[i].pop, st->v[i].dist);
    printf("\n\n");
}

int STinsert(ST st, Item val) {
    if(st->n == st->max)
        return -1;
    st->v[st->n].name = strdup(val.name);
    st->v[st->n].pop = val.pop;
    st->v[st->n].dist = val.dist;
    st->n++;
    return 1;
}

Item STgetbyindex(ST st, int index) {
    return st->v[index];
}
