//
//  ST.h
//  AP_Exam032017_18pt
//
//  Created by Oskar Bich on 20/3/22.
//

#ifndef ST_h
#define ST_h

#include <stdio.h>

typedef struct{
    char *id;
    int arrivo;
    int pernottamenti;
}Item;

Item ItemCreate(char *id, int a, int p);

typedef struct hashtable *ST;

ST STinit(int max);
void STfree(ST table);
int getN(ST table);
int STsearchbyname(ST table, char *x);
void STprint(ST table);
int STinsert(ST table, Item x);
Item STgetbyindex(ST table, int index);

#endif /* ST_h */
