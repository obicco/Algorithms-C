//
//  main.c
//  Lab11es1
//
//  Created by Oskar Bich on 07/01/21.
// elementi.txt testset_e_risultati
// to subsequence dir_out (elem_1) = dir_in (elem_2)
// start always front

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define F_IN "elementi.txt"
#define MAXL 100
#define NDIAG 3
#define MAXE 5

#define DD 7
#define DP 30

typedef struct{
    char *name;
    int type; //2 forward, 1 backward, 0 transition
    int dir_in, dir_out; //1 front, 0 back
    int prevex; //0 can be the first element, 1 can't
    int ending; //1 must be the last one, 0 not
    float val;
    int difficulty;
} element_t;

typedef struct{
    int *elements;
    int ne;
    int diff;
    float val;
}diagonal_t;

typedef struct {
    diagonal_t *vd;
    int nd;
    int maxd;
} diagonals_t;

typedef struct {
    element_t *velem;
    int ne;
} elements_t;


elements_t *loadFile(char *fname);
diagonals_t *initDiagonals(void);
void generateDiagonals(elements_t *t, diagonals_t *d, int max);
void generatePrograms(elements_t *t, diagonals_t *d, int max);
void printElement(element_t *e);
void dispRip(elements_t *t, diagonals_t *d, int max, int pos, int diff, int acro, int dir, int fin, int *diag);
void combRip(elements_t *t, diagonals_t *d, int max, int pos, int *prog, int diff, int *bestprog, float *bestval, int *bestbonus, int *numd, int start);
int check(elements_t *E, diagonals_t *D, int *prog, int nd, float *val, int *B);

int main(int argc, const char * argv[]) {
    elements_t *t = loadFile(F_IN);
    diagonals_t *d = initDiagonals();
    generateDiagonals(t, d, DD);
    printf("Sono disponibili %d diagonali\n", d->nd);
    generatePrograms(t, d, DP);
    return 0;
}

elements_t *loadFile(char *fname) {
    char tmp[MAXL];
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
        exit(-1);
    elements_t *t = malloc(sizeof(elements_t));
    fscanf(fp, "%d", &t->ne);
    t->velem = calloc(t->ne, sizeof(element_t));
    for (int i = 0; i < t->ne; i++) {
        fscanf(fp, "%s%d%d%d%d%d%f%d", tmp, &t->velem[i].type, &t->velem[i].dir_in, &t->velem[i].dir_out, &t->velem[i].prevex, &t->velem[i].ending, &t->velem[i].val, &t->velem[i].difficulty);
        t->velem[i].name = strdup(tmp);
    }
    fclose(fp);
    
    return t;
}

diagonals_t *initDiagonals(void) {
    diagonals_t *d = malloc(sizeof(diagonals_t));
    d->vd = calloc(1, sizeof(diagonal_t));
    d->nd = 0;
    d->maxd = 1;
    return d;
}

void printElement (element_t *e) {
    fprintf(stdout, "%s %d %d %d %d %d %f %d\n", e->name, e->type, e->dir_in, e->dir_out, e->prevex, e->ending, e->val, e->difficulty);
}

void generateDiagonals(elements_t *t, diagonals_t *d, int max) {
    int *diag = calloc(MAXE, sizeof(int));
    dispRip(t, d, DD, 0, 0, 0, 1, 0, diag);
}

void generatePrograms(elements_t *t, diagonals_t *d, int max) {
    int bonus, diag, numd = 0;
    int *prog = malloc (NDIAG*sizeof(int));
    int *bestprog = malloc(NDIAG*sizeof(int));
    float bestval = -1.0;
    combRip(t, d, DP, 0, prog, 0, bestprog, &bestval, &bonus, &numd, 0);
    if (numd > 0) {
        printf("TOT = %.2f\n", bestval);
        for (int i = 0; i < numd; i++) {
            diag = bestprog[i];
            printf("DIAG %d > %.2f %s\n", diag, d->vd[diag].val, ((bonus == i) ? "* 1.5 (BONUS)" : ""));
            for (int j = 0; j < d->vd[diag].ne; j++) printf("%s ", t->velem[d->vd[diag].elements[j]].name);
            printf("\n");
        }
    }
}

void dispRip(elements_t *t, diagonals_t *d, int max, int pos, int diff, int acro, int dir, int fin, int *diag) {
    if (pos > 0) {
        if (acro > 0) {
            if (d->nd == d->maxd) {
                d->maxd *= 2;
                d->vd = realloc(d->vd, d->maxd * sizeof(diagonal_t));
                if (d->vd == NULL)
                    exit(-1);
            }
            d->vd[d->nd].diff = diff;
            d->vd[d->nd].ne = pos;
            d->vd[d->nd].elements = malloc(pos*sizeof(int));
            d->vd[d->nd].val = 0.0;
            for (int i = 0; i < pos; i++) {
                d->vd[d->nd].val += t->velem[diag[i]].val;
                d->vd[d->nd].elements[i] = diag[i];
            }
            d->nd++;
        }
    }
    if (pos >= MAXE || fin)
        return;
    
    for (int i = 0; i < t->ne; i++) {
        if (diff+t->velem[i].difficulty > DD) continue;
        if (dir != t->velem[i].dir_in) continue;
        if (pos == 0 && t->velem[i].prevex) continue;
        diag[pos] = i;
        dispRip(t, d, max, pos+1, diff+t->velem[i].difficulty, acro+t->velem[i].type, t->velem[i].dir_out, t->velem[i].ending, diag);
    }
}

void combRip(elements_t *t, diagonals_t *d, int max, int pos, int *prog, int diff, int *bestprog, float *bestval, int *bestbonus, int *numd, int start) {
    int bonus;
    float val = 0.0;
    if (pos >= NDIAG) {
        if(check(t, d, prog, pos, &val, &bonus)) {
            if (val > *bestval) {
                *numd = pos;
                *bestval = val;
                *bestbonus = bonus;
                memcpy(bestprog, prog, pos*sizeof(int));
            }
        }
        return;
    }
    
    for(int i = start; i < d->nd; i++) {
        if (diff+d->vd[i].diff > DP) continue;
        prog[pos] = i;
        combRip(t, d, max, pos+1, prog, diff+d->vd[i].diff, bestprog, bestval, bestbonus, numd, i);
    }
}

int check(elements_t *E, diagonals_t *D, int *prog, int nd, float *val, int *B) {
  int bonus = -1;
  int fwd = 0, bwd = 0, seq = 0;
  for(int i = 0; i < nd; i++) {
    int dseq = 0;
    for(int j = 0; j < D->vd[prog[i]].ne; j++) {
      if (E->velem[D->vd[prog[i]].elements[j]].type == 2) {
        fwd = 1;
        dseq++;
      } else if (E->velem[D->vd[prog[i]].elements[j]].type == 1) {
        bwd = 1;
        dseq++;
      } else {
        dseq = 0;
      }
      if (j == (D->vd[prog[i]].ne-1) && E->velem[D->vd[prog[i]].elements[j]].type > 0 && E->velem[D->vd[prog[i]].elements[j]].difficulty > 7) {
        if (bonus == -1 || (D->vd[prog[bonus]].val < D->vd[prog[i]].val))
            bonus = i;
      }
      if (dseq >= 2)
          seq = 1;
    }
  }
  if (fwd && bwd && seq) {
    for(int i = 0; i < nd; i++) {
      (*val) += D->vd[prog[i]].val * ((i==bonus) ? 1.50 : 1.00);
    }
    *B = bonus;
    return 1;
  }
  return 0;
}
