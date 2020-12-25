//
//  inv.c
//  Lab09es3
//
//  Created by Oskar Bich on 25/12/20.
//

#include "inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tabInv_t *loadFileInv(char *file) {
    tabInv_t *tabInv = calloc(1, sizeof(tabInv_t));
    FILE *fIN = fopen(file, "r");
    if (fIN == NULL)
        exit(-1);
    
    fscanf(fIN, "%d", &tabInv->nInv);
    inv_t *vInv = calloc(tabInv->nInv, sizeof(inv_t));
    tabInv->vInv = vInv;
    
    for (int i = 0; i < tabInv->nInv; i++)
        readInv(&tabInv->vInv[i], fIN);
    return tabInv;
}

void readInv(inv_t *inv, FILE *fp) {
    char tmpName[N], tmpType[N];
    stat_t *stats = calloc(1, sizeof(stat_t));
    inv->stats = stats;
    
    fscanf(fp, "%s %s %d %d %d %d %d %d", tmpName, tmpType, &inv->stats->hp, &inv->stats->mp, &inv->stats->atk, &inv->stats->def, &inv->stats->mag, &inv->stats->spr);
    inv->name = strdup(tmpName);
    inv->type = strdup(tmpType);
}

void printTabInv(tabInv_t *tabInv) {
    printf("INVENTARIO:\n");
    for (int i = 0; i < tabInv->nInv; i++)
        printInv(tabInv->vInv[i]);
}

void printInv(inv_t inv) {
    fprintf(stdout, "%s %s [hp=%d mp=%d atk=%d def=%d mag=%d spr=%d]\n", inv.name, inv.type, inv.stats->hp, inv.stats->mp, inv.stats->atk, inv.stats->def, inv.stats->mag, inv.stats->spr);
}

void freeTabInv(tabInv_t *tabInv) {
    for (int i = 0; i < tabInv->nInv; i++)
        freeInv(tabInv->vInv[i]);
    free(tabInv->vInv);
    free(tabInv);
}

void freeInv(inv_t Inv) {
    free(Inv.name);
    free(Inv.type);
    free(Inv.stats);
}
