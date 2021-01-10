//
//  Item.h
//  Lab11es3
//
//  Created by Oskar Bich on 10/01/21.
//

#ifndef Item_h
#define Item_h
#define MAXL 31

#include <stdio.h>

typedef struct {
    char elab[MAXL];
    char net[MAXL];
} Item;

typedef char *Key;

Item ITEMload(char name1[], char name2[]);
void ITEMstore(Item val);
Item ITEMsetNull(void);
Key KEYget(Item *pval);
void KEYscan(char node[]);
int KEYcmp(Key k1, Key k2);

#endif /* Item_h */
