//
//  main.c
//  Lab08es3
//
//  Created by Oskar Bich on 13/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 51
#define MAX_EQ 8
#define CMD 7
#define S 6
#define pg_file "pg.txt"
#define inv_file "inventario.txt"

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

void printInstructions(char *instructions[], int *sel);
tabPg_t *loadFilePg(char *file);
int readPg(FILE *fp, tabPg_t *tabPg);
linkPg allocateNodePg(tabPg_t *tabPg);
tabInv_t *loadFileInv(char *file);
void insertSorted(nodePg_t *x,tabPg_t *tabPg);
void printTabPg(tabPg_t *tabPg);
void printTabInv(tabInv_t *tabInv);
void printPg(pg_t *pg);
void printInv(inv_t inv);
void freeTabPg(tabPg_t *tabPg);
void freeNodePg(linkPg x);
void freeTabInv(tabInv_t *tabInv);
void freeInv(inv_t Inv);
void readInv(inv_t *inv, FILE *fp);
void addPg(tabPg_t *tabPg);
int deletePgCod(tabPg_t *tabPg, char *cod);
linkPg searchPgCod(tabPg_t *tabPg, char *cod);
void attributeEquip(tabPg_t *tabPg, tabInv_t *tabInv, int flag);
int checkDup(inv_t **vEq, char *eqName);
void printStatsWithEq (linkPg x, tabInv_t *tabInv);

int main(int argc, const char * argv[]) {
    char *instructions[] = {"Uscita", "Stampa personaggi", "Stampa inventario", "Aggiungere personaggio", "Rimuovere personaggio", "Aggiungere/rimuovere equipaggiamento personaggio", "Calcolare statistiche personaggio"};
    int end = 0, sel, flag;
    char tmpString[N];
    tabPg_t *tabPg = loadFilePg(pg_file);
    tabInv_t *tabInv = loadFileInv(inv_file);
    do {
        printInstructions(instructions, &sel);
        switch (sel) {
            case 0:
                end = 1;
                break;
            case 1:
                printTabPg(tabPg);
                break;
            case 2:
                printTabInv(tabInv);
                break;
            case 3:
                printf("Inserire personaggio [Codice Nome Classe hp mp atk def mag spr]\n");
                readPg(stdin, tabPg);
                printf("\n- Aggiornamento -\n");
                printTabPg(tabPg);
                break;
            case 4:
                printf("Inserire codice personaggio da eliminare:\n");
                scanf("%s", tmpString);
                if(deletePgCod(tabPg, tmpString)) {
                    printf("\n- Aggiornamento -\n");
                    printTabPg(tabPg);
                } else printf("Errore cancellazione - Codice non trovato\n");
                break;
            case 5:
                printf("1 - Aggiungere equipaggiamento\n2 - Rimuovere equipaggiamento\nComando > ");
                scanf("%d", &flag);
                if (flag != 1 && flag != 2)
                    printf("Scelta non valida\n");
                else attributeEquip(tabPg, tabInv, flag);
                break;
            case 6:
                printf("Inserire codice personaggio da visualizzare:\n");
                scanf("%s", tmpString);
                printStatsWithEq(searchPgCod(tabPg, tmpString), tabInv);
                break;
            default:
                printf("Scelta non valida\n");
                break;
        }
    } while(!end);
    freeTabPg(tabPg);
    freeTabInv(tabInv);
    return 0;
}

void printInstructions(char *instructions[], int *sel) {
    printf("\nMENU\n");
    for (int i = 0; i < CMD; i++) {
        printf("%d - %s\n", i, instructions[i]);
    }
    printf("Comando > ");
    scanf("%d", sel);
}

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
