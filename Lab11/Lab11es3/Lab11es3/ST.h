//
//  ST.h
//  Lab11es3
//
//  Created by Oskar Bich on 10/01/21.
//

#ifndef ST_h
#define ST_h
#include "Item.h"

typedef struct symbtab *ST;

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, Item x);
int STsearch(ST st, Key k);
void STdisplayByIndex(ST st, int index);

#endif /* ST_h */
