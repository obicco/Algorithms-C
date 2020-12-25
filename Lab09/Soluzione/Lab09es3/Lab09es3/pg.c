//
//  pg.c
//  Lab09es3
//
//  Created by Oskar Bich on 25/12/20.
//

#include "pg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tabPg_t *loadFilePg(char *file) {
    tabPg_t *tabPg = calloc(1, sizeof(tabPg_t));
    FILE *fIN = fopen(file, "r");
    if (fIN == NULL)
        exit(-1);
    while (readPg(fIN, tabPg)) {
        tabPg->nPg++;
    }
    return tabPg;
}

int readPg(FILE *fp, tabPg_t *tabPg) {
    linkPg x;
    char tmpCod[N], tmpName[N], tmpClass[N];
    if (fscanf(fp, "%s%s%s", tmpCod, tmpName, tmpClass) != 3) {
        return 0;
    }
    else {
        x = allocateNodePg(tabPg);
        x->pg->cod = strdup(tmpCod);
        x->pg->name = strdup(tmpName);
        x->pg->class = strdup(tmpClass);
        fscanf(fp, "%d%d%d%d%d%d", &x->pg->b_stat->hp, &x->pg->b_stat->mp, &x->pg->b_stat->atk, &x->pg->b_stat->def, &x->pg->b_stat->mag, &x->pg->b_stat->spr);
        insertSorted(x, tabPg);
        return 1;
    }
}

linkPg allocateNodePg(tabPg_t *tabPg) {
    linkPg x = calloc(1, sizeof(linkPg));
    pg_t *pg = calloc(1, sizeof(pg_t));
    stat_t *b_stat = calloc(1, sizeof(stat_t));
    stat_t *eq_stat = calloc(1, sizeof(stat_t));
    inv_t **vEq = calloc(MAX_EQ, sizeof(inv_t*));
    tabEquip_t *eq = calloc(1, sizeof(tabEquip_t));
    x->pg = pg;
    x->pg->b_stat = b_stat;
    x->pg->eq_stat = eq_stat;
    x->pg->eq = eq;
    x->pg->eq->vEq = vEq;
    return x;
}

void insertSorted(nodePg_t *x,tabPg_t *tabPg) {
    linkPg prev = NULL, curr = tabPg->headPg;
    while (curr !=NULL && strcmp(x->pg->cod, curr->pg->cod) > 0) {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL) {
        x->next = curr;
        tabPg->headPg = tabPg->tailPg = x;
        return;
    }
    if (prev->next == NULL)
        prev->next = tabPg->tailPg = x;
    else {
        prev->next = x;
        x->next = curr;
    }
}

void printTabPg(tabPg_t *tabPg) {
    printf("PERSONAGGI:\n");
    linkPg prev = NULL, curr = tabPg->headPg;
    while (curr != NULL) {
        printPg(curr->pg);
        prev = curr;
        curr = curr->next;
    }
}

void printPg(pg_t *pg) {
    fprintf(stdout, "%s %s %s [hp=%d mp=%d atk=%d def=%d mag=%d spr=%d]\n", pg->cod, pg->name, pg->class, pg->b_stat->hp, pg->b_stat->mp, pg->b_stat->atk, pg->b_stat->def, pg->b_stat->mag, pg->b_stat->spr);
}

void freeTabPg(tabPg_t *tabPg) {
    linkPg prev = NULL, curr = tabPg->headPg;
    while(curr != NULL) {
        freeNodePg(curr);
        prev = curr;
        curr = curr->next;
    }
    free(tabPg);
}

void freeNodePg(linkPg x) {
    free(x->pg->cod);
    free(x->pg->name);
    free(x->pg->class);
    free(x->pg->b_stat);
    free(x->pg->eq_stat);
    free(x->pg->eq);
    free(x->pg);
    free(x);
}

int deletePgCod(tabPg_t *tabPg, char *cod) {
    linkPg prev = NULL, curr = tabPg->headPg;
    while (curr != NULL && strcmp(cod, curr->pg->cod) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL)
        return 0;
    if (prev == NULL) {
        tabPg->headPg = curr->next;
        return 1;
    }
    if (prev->next == NULL)
        tabPg->tailPg = prev;
    else {
        prev->next = curr->next;
        freeNodePg(curr);
    }
    return 1;
}

linkPg searchPgCod(tabPg_t *tabPg, char *cod) {
    linkPg prev = NULL, curr = tabPg->headPg;
    while (curr != NULL && strcmp(cod, curr->pg->cod) != 0) {
        prev = curr;
        curr = curr->next;
    }
    return curr;
}

void attributeEquip(tabPg_t *tabPg, tabInv_t *tabInv, int flag) {
    char cod[N];
    int sel;
    printf("Inserire codice personaggio:\n");
    scanf("%s", cod);
    linkPg x = searchPgCod(tabPg, cod);
    if (x == NULL)
        return;
    if (flag == 1) {
        if (x->pg->eq->cnt >= MAX_EQ) {
            printf("Impossibile aggiungere equipaggiamento - slot pieni\n");
            return;
        }
        for (int i = 0; i < tabInv->nInv; i++) {
            printf("%d - ", i);
            printInv(tabInv->vInv[i]);
        }
        printf("Equipaggiamento da aggiungere > ");
        scanf("%d", &sel);
        if (sel >= 0 && sel < tabInv->nInv && !checkDup(x->pg->eq->vEq, tabInv->vInv[sel].name)) {
            for (int i = 0; i < MAX_EQ; i++) {
                if (x->pg->eq->vEq[i] == NULL) {
                    x->pg->eq->cnt++;
                    x->pg->eq->vEq[i] = &tabInv->vInv[sel];
                    break;
                }
            }
            for (int i = 0; i < MAX_EQ; i++) {
                if (x->pg->eq->vEq[i] == NULL)
                    continue;
                else printf("Slot %d - %s\n", i, x->pg->eq->vEq[i]->name);
            }
        } else return;
    }
    if (flag == 2) {
        for (int i = 0; i < MAX_EQ; i++) {
            if (x->pg->eq->vEq[i] == NULL)
                continue;
            else printf("%d - %s\n", i, x->pg->eq->vEq[i]->name);
        }
        printf("Equipaggiamento da rimuovere > ");
        scanf("%d", &sel);
        if (x->pg->eq->vEq[sel] != NULL) {
            x->pg->eq->cnt--;
            x->pg->eq->vEq[sel] = NULL;
        } else return;
        for (int i = 0; i < MAX_EQ; i++) {
            if (x->pg->eq->vEq[i] == NULL)
                continue;
            else printf("Slot %d - %s\n", i, x->pg->eq->vEq[i]->name);
        }
    }
}

int checkDup(inv_t **vEq, char *eqName) {
    for (int i = 0; i < MAX_EQ; i++) {
        if (vEq[i] != NULL) {
            if (strcmp(vEq[i]->name, eqName) == 0)
                return 1;
        }
    }
    return 0;
}

void printStatsWithEq (linkPg x, tabInv_t *tabInv) {
    if (x == NULL) {
        printf("Codice personaggio non trovato\n");
        return;
    }
    int stats[S] = {x->pg->b_stat->hp,
                    x->pg->b_stat->mp,
                    x->pg->b_stat->atk,
                    x->pg->b_stat->def,
                    x->pg->b_stat->mag,
                    x->pg->b_stat->spr};
    for (int i = 0; i < MAX_EQ; i++) {
        if (x->pg->eq->vEq[i] == NULL)
            continue;
        else {
            stats[0] += x->pg->eq->vEq[i]->stats->hp;
            stats[1] += x->pg->eq->vEq[i]->stats->mp;
            stats[2] += x->pg->eq->vEq[i]->stats->atk;
            stats[3] += x->pg->eq->vEq[i]->stats->def;
            stats[4] += x->pg->eq->vEq[i]->stats->mag;
            stats[5] += x->pg->eq->vEq[i]->stats->spr;
        }
    }
    for (int i = 0; i < S; i++) {
        if (stats[i] < 0)
            stats[i] = 0;
    }
    fprintf(stdout, "Statistiche personaggio con equipaggiamento:\n%s %s %s [hp=%d mp=%d atk=%d def=%d mag=%d spr=%d]\n", x->pg->cod, x->pg->name, x->pg->class, stats[0], stats[1], stats[2], stats[3], stats[4], stats[5]);
}
