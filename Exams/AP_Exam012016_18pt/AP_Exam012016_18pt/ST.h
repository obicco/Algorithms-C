//
//  ST.h
//  AP_Exam012016_18pt
//
//  Created by Oskar Bich on 15/3/22.
//

#ifndef ST_h
#define ST_h

#include <stdio.h>

typedef struct {
    char *name;
    int pop;
    int dist;
} Item;

Item ItemCreate(char *name, int pop, int dist);

typedef struct symboltable *ST;

ST Stinit(int maxN);
void STfree(ST st);
int STserchbyname(ST st, char *name);
void STprint(ST st);
int STinsert(ST st, Item val);
Item STgetbyindex(ST st, int index);
void STsort(ST st);

#endif /* ST_h */
