//
//  main.c
//  AP_Exam032016
//
//  Created by Oskar Bich on 13/6/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define R 3
#define C 4
#define N 1000

void matMax (int **m, int r, int c);
int check(int **m, int x, int y, int val);
int separaParole(char *frase, char ***parole);

int main(int argc, const char * argv[]) {
    int M[R][C] = {
        {5, 2, 3, 1},
        {4, 1, 6, 4},
        {3, 0, 5, 2}
    };
    char frase[N] = "Ciao mi chiamo Oskar", **parole;
    
    int n = separaParole(frase, &parole);
    
    printf("Elenco parole:\n");
    
    for (int i = 0; i < n; i++) printf("%s\n", parole[i]);
    
    int **m = malloc(R*sizeof(int*));
    for(int i = 0; i < R; i++) {
        m[i] = malloc(C*sizeof(int));
        for (int j = 0; j < C; j++) {
            m[i][j] = M[i][j];
        }
    }
    
    for(int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    
    matMax(m, R, C);
    
    return 0;
}

void matMax (int **m, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (check(m, i, j, m[i][j]))
                printf("Elemento strettamente maggiore agli adiacenti in posizione: (%d, %d)\n", i, j);
        }
    }
}

int check(int **m, int x, int y, int val) {
    int ok = 1;
    for (int i = x-1; i < x+2; i++) {
        for (int j = y-1; j < y+2; j++) {
            if (i < 0 || j < 0 || i > R-1 || j > C-1)
                continue;
            if (m[i][j] > val) {
                ok = 0;
                break;
            }
        }
    }
    return ok;
}

int separaParole(char *frase, char ***parole) {
    int n = 0, i = 0, k = 0;
    char parola[N];
    while (frase[i] != '\0') {
        sscanf(frase + i, "%s", parola);
        n++;
        i += strlen(parola)+1;
    }
    *parole = malloc(n*sizeof(char*));
    i = 0;
    while (frase[i] != '\0') {
        sscanf(frase + i, "%s", parola);
        (*parole)[k++] = strdup(parola);
        i += strlen(parola)+1;
    }
    return n;
}
