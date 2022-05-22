//
//  ST.h
//  AP_Exam032022_18pt
//
//  Created by Oskar Bich on 7/4/22.
//

#ifndef ST_h
#define ST_h

#include <stdio.h>

typedef struct hashtable *ST;

ST STinit(int MaxN);
void STinsert(ST st, char *val);
int STgetindex(ST st, char *val);
void STprint(ST st); //Output

#endif /* ST_h */
