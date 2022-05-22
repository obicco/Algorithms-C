//
//  main.c
//  AP_Exam012016_18pt
//
//  Created by Oskar Bich on 15/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

#define INT_MAX 100000000
#define NMAX 31
#define DIR "/Users/oskar/Library/Mobile\ Documents/com\~apple\~CloudDocs/Development/C/AP/Exams/AP_Exam012016_18pt/AP_Exam012016_18pt/in.txt"

ST readFile(FILE *in, int *N) {
    ST st;
    int n, pop, dist;
    char name[NMAX];
    fscanf(in, "%d\n", &n);
    *N = n;
    st = Stinit(n);
    while(fscanf(in, "%s %d %d", name, &pop, &dist) == 3) {
        STinsert(st, ItemCreate(name, pop, dist));
    }
    return st;
}

int **distance(ST st, int N) {
    int **dist = malloc(N*sizeof(int*));
    for (int i = 0; i < N; i++) {
        dist[i] = calloc(N, sizeof(int));
        for (int j = 0; j < N; j++) {
            dist[i][j] = abs(STgetbyindex(st, i).dist - STgetbyindex(st, j).dist);
        }
    }
    return dist;
}

void printM (int **M, int N) {
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j++) printf("%d ", M[i][j]);
        printf("\n");
    }
    printf("\n\n");
}

int SD(int *sol, int **dist, int k, int N, ST st) {
    int d, *distMin = malloc(N*sizeof(*distMin));
    for (int i = 0; i < N; i++) distMin[i] = INT_MAX;
    for (int i = 0; i < k; i++) distMin[sol[i]] = 0;
    for (int i = 1; i < N; i++) {
        if (distMin[i-1] == INT_MAX)
            continue;
        d = distMin[i-1] + dist[i-1][i];
        distMin[i] = (d < distMin[i]) ? d : distMin[i];
    }
    for(int i = N-2; i>= 0; i--){
        if(distMin[i+1] == INT_MAX)
            continue;
        d = distMin[i+1] + dist[i+1][i];
        distMin[i] = (d < distMin[i]) ? d : distMin[i];
    }
    for (int i = 0, d = 0; i < N; i++) d += distMin[i]*STgetbyindex(st, i).pop;
    free(distMin);
    return d;
}

void comb_semplici(int pos, int **dist, int *sol, int *bestsol, int N, int k, int start, int *bestVal, ST st) {
    int tmpval;
    if (pos == k) {
        tmpval = SD(sol, dist, k, N, st);
        if (tmpval < *bestVal) {
            *bestVal = tmpval;
            for (int i = 0; i < k; i ++) bestsol[i] = sol[i];
        }
        return;
    }
    for (int i = start; i < N; i++) {
        sol[pos] = i;
        comb_semplici(pos+1, dist, sol, bestsol, N, k, i+1, bestVal, st);
    }
}

void generateSolutions(ST st, int **dist, int N, int k) {
    int *sol, *bestsol, bestVal = INT_MAX;
    sol = calloc(k, sizeof(*sol));
    bestsol = calloc(k, sizeof(bestsol));
    comb_semplici(0, dist, sol, bestsol, N, k, 0, &bestVal, st);
    printf("Soluzione ottima a valore %d:\n", bestVal);
    for (int i = 0; i < k; i++) printf("%s\t ", STgetbyindex(st, bestsol[i]).name);
    printf("\n\n");
}

int main(int argc, const char * argv[]) {
    FILE *in = fopen(DIR, "r");
    int N, **dist;
    ST st = readFile(in, &N);
    fclose(in);
    dist = distance(st, N);
    printM(dist, N);
    STprint(st);
    generateSolutions(st, dist, N, 4);
    return 0;
}
