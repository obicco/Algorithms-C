//
//  inv.h
//  Lab09es3
//
//  Created by Oskar Bich on 25/12/20.
//

#ifndef inv_h
#define inv_h
#include <stdio.h>
#define N 51

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct {
    char *name;
    char *type;
    stat_t *stats;
} inv_t;

typedef struct {
    inv_t *vInv;
    int nInv;
} tabInv_t;

tabInv_t *loadFileInv(char *file);
void printTabInv(tabInv_t *tabInv);
void printInv(inv_t inv);
void freeTabInv(tabInv_t *tabInv);
void freeInv(inv_t Inv);
void readInv(inv_t *inv, FILE *fp);

#endif /* inv_h */
