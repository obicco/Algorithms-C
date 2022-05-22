//
//  ST.c
//  AP_Exam032022_18pt
//
//  Created by Oskar Bich on 7/4/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

struct hashtable{
    int max;
    char **v;
};

ST STinit(int max){
    ST table;
    table = malloc(sizeof(*table));
    table->max = max;
    table->v = calloc(max, sizeof(char*));
    return table;
}

void STinsert(ST st, char *val) {
    for (int i = 0; i < st->max; i++)
        if (st->v[i] == NULL) {
            st->v[i] = strdup(val);
            break;
        }
}

int STgetindex(ST st, char *val) {
    for(int i = 0; i < st->max; i++){
        if(strcmp(st->v[i], val) == 0)
            return i;
    }
    return -1;
}

//Output
void STprint(ST st) {
    for(int i = 0; i < st->max; i++){
        printf("%s\n", st->v[i]);
    }
}
