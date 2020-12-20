//
//  main.c
//  Lab09es1
//
//  Created by Oskar Bich on 20/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#define F_IN "att1.txt"

typedef struct {
    int s;
    int f;
} att;

att *readFile(char *fname, int *n);
void attSel(int N, att *v);
void attSelR(int pos, att *val, int *sol, int *bestsol, int n, int currD, int *bestD);
int check (int n, att *val, int *sol, int pos);

int main(int argc, const char * argv[]) {
    int n;
    att *v = readFile(F_IN, &n);
    attSel(n, v);
    free(v);
    return 0;
}

att *readFile(char *fname, int *n) {
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
        exit(-1);
    fscanf(fp, "%d", n);
    att *v = calloc(*n, sizeof(att));
    for (int i = 0; i < *n; i++)
        fscanf(fp, "%d%d", &v[i].s, &v[i].f);
    return v;
}

void attSel(int N, att *v) {
    int *sol = calloc(N, sizeof(int));
    int *bestsol = calloc(N, sizeof(int));
    int duration = 0;
    attSelR(0, v, sol, bestsol, N, 0, &duration);
    
    printf("Soluzione migliore di durata massima %d:\n", duration);
    for (int i = 0; i < N; i++) {
        if (bestsol[i])
            printf("(%d %d)\n", v[i].s, v[i].f);
    }
    free(sol);
    free(bestsol);
}

void attSelR(int pos, att *val, int *sol, int *bestsol, int n, int currD, int *bestD) {
    if (pos >= n) {
        if(currD > *bestD) {
            *bestD = currD;
            for (int i = 0; i < pos; i++) {
                bestsol[i] = sol[i];
            }
        }
        return;
    }
    sol[pos] = 0;
    attSelR(pos+1, val, sol, bestsol, n, currD, bestD);
    if (!check(n, val, sol, pos)) {
        sol[pos] = 1;
        attSelR(pos+1, val, sol, bestsol, n, currD+(val[pos].f - val[pos].s), bestD);
    }
}

int check (int n, att *val, int *sol, int pos) {
    for (int i = 0; i < pos; i++) {
        if (sol[i] != 0) {
            if (val[i].s < val[pos].f && val[pos].s < val[i].f)
                return 1;
        }
    }
    return 0;
}
