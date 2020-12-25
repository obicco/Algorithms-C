//
//  pg.h
//  Lab09es3
//
//  Created by Oskar Bich on 25/12/20.
//

#ifndef pg_h
#define pg_h

#include <stdlib.h>
#include <stdio.h>
#include "inv.h"

#define N 51
#define MAX_EQ 8
#define S 6

typedef struct {
    int cnt;
    inv_t **vEq;
} tabEquip_t;

typedef struct {
    char *cod;
    char *name;
    char *class;
    tabEquip_t *eq;
    stat_t *b_stat, *eq_stat;
} pg_t;

typedef struct nodePg *linkPg;
typedef struct nodePg{
    pg_t *pg;
    linkPg next;
}nodePg_t;

typedef struct{
    linkPg headPg, tailPg;
    int nPg;
}tabPg_t;

tabPg_t *loadFilePg(char *file);
int readPg(FILE *fp, tabPg_t *tabPg);
linkPg allocateNodePg(tabPg_t *tabPg);
void insertSorted(nodePg_t *x,tabPg_t *tabPg);
void printTabPg(tabPg_t *tabPg);
void printPg(pg_t *pg);
void freeTabPg(tabPg_t *tabPg);
void freeNodePg(linkPg x);
void addPg(tabPg_t *tabPg);
int deletePgCod(tabPg_t *tabPg, char *cod);
linkPg searchPgCod(tabPg_t *tabPg, char *cod);
void attributeEquip(tabPg_t *tabPg, tabInv_t *tabInv, int flag);
int checkDup(inv_t **vEq, char *eqName);
void printStatsWithEq (linkPg x, tabInv_t *tabInv);

#endif /* pg_h */
