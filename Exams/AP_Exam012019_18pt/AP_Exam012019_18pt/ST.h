//
//  ST.h
//  AP_Exam012019_18pt
//
//  Created by Oskar Bich on 22/3/22.
//

#ifndef ST_h
#define ST_h

#include <stdio.h>

typedef struct hashtable *ST;

ST STinit(int n);
void STfree(ST table);
int STsearchbyname(ST table, char *key);
void STprint(ST table);
int STinsert(ST table, char *x);
char *STgetbyindex(ST table, int index);
int STgetN(ST table);

#endif /* ST_h */
