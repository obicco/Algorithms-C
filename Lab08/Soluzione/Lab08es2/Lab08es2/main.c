//
//  main.c
//  Lab08es2
//
//  Created by Oskar Bich on 12/12/20.
// very_very_easy_test_set.txt test_set.txt test_set_result.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define FNAME "test_set.txt"

typedef struct {
    char *name;
    int val;
    int disp;
    int num;
}Gem;

int disp_rip(int pos, int val, Gem *g, int *sol, int *best_val, int max_rip, int n, int k, int prev);
int readSequence(FILE *fp, Gem *g, int *max_rip);
void printStats(Gem *g, int testnum, int l, int max_rip);

// CAPIRE PERCHE' NEL CASO CON DISP 1 O MAXRIP 1 NON ESCE RIUSLTATO DESIDERATO
int main(int argc, const char * argv[]) {
    int n, *sol, l, res, min, max, max_rip, best_val;
    char *names[N] = {"Zaffiro", "Rubino", "Topazio", "Smeraldo"};
    FILE *fp = fopen(FNAME, "r");
    if (fp == NULL)
        return -1;
    
    Gem *gem = calloc(N, sizeof(Gem));
    for (int i = 0; i < N; i++)
        gem[i].name = strdup(names[i]);

    fscanf(fp, "%d", &n);
    for(int i = 0; i < n; i++) {
        min = 0;
        res = 0;
        best_val = 0;
        l = readSequence(fp, gem, &max_rip);
        printStats(gem, i+1, l, max_rip);
        sol = malloc(l * sizeof(int));
        max = l;
        
        for (int k = 1; k <= l; k++) {
            for (int i = 0; i < N; i++)
                gem[i].disp = gem[i].num;
            if (disp_rip(0, 0, gem, sol, &best_val, max_rip, N, k, -1))
                res = k;
        }
        printf("Soluzione ottima di valore %d usando %d gemma/e\nComposizione collana: ",best_val, res);
        for( int i = 0; i < res; i++) {
            printf("%c", gem[sol[i]].name[0]);
        }
        printf("\n");
        free(sol);
    }
    fclose(fp);
    for (int i = 0; i < N; i++)
        free(gem[i].name);
    return 0;
}

int disp_rip(int pos, int val, Gem *g, int *sol, int *best_val, int max_rip, int n, int k, int prev) {
    if (pos >= k) {
        if ((g[0].num - g[0].disp) <= (g[3].num - g[3].disp) && val > *best_val) {
            *best_val = val;
            return 1;
        } else return 0;
    }
    for (int i = 0; i < n; i++) {
        if (g[i].disp > 0) {
            if (prev != -1) { //Controllo parametri
                if (((sol[prev] == 0) || (sol[prev] == 2)) && (i != 0) && (i != 1))
                    continue;;
                if (((sol[prev] == 1) || (sol[prev] == 3)) && (i != 2) && (i != 3))
                    continue;
            }
            if ((prev-max_rip) > 0) {  //Controllo ripetizione
                for (int j = 0; j < max_rip; j++) {
                    if ((sol[pos-j] == i) && j == (max_rip-1))
                        return 0;
                }
            }
            g[i].disp--;
            sol[pos] = i;
            val += g[i].val;
            if (disp_rip(pos+1, val, g, sol, best_val, max_rip, n, k, pos))
                return 1;
            g[i].disp++;
            val -= g[i].val;
        }
    }
    return 0;
}


int readSequence(FILE *fp, Gem *g, int *max_rip) {
    int l = 0;
    for (int i = 0; i < N; i++) {
        fscanf(fp, "%d", &g[i].num);
        l += g[i].num;
    }
    for (int i = 0; i < N; i++)
        fscanf(fp, "%d", &g[i].val);
    fscanf(fp, "%d", max_rip);
    return l;
}

void printStats(Gem *g, int testnum, int l, int max_rip) {
    printf("TEST #%d\n", testnum);
    for (int i = 0; i < N; i++)
        printf("%s = %d [%d], ", g[i].name, g[i].num, g[i].val);
    printf("TOT = %d {max_rip = %d}\n", l, max_rip);
}
