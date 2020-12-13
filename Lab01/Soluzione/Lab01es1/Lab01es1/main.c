//
//  main.c
//  Lab01es1
//
//  Created by Oskar Bich on 24/10/2020.
//

#include <stdio.h>
#define MAXN 20

void capolista(int mat[MAXN][MAXN], int n, int m);
int cercaMax(int v[MAXN],int n);

int main(int argc, const char * argv[]) {
    int mat[MAXN][MAXN], m, n;
    FILE *fp;
    fp = fopen("mat.txt", "r");
    fscanf(fp, "%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);
    
    capolista(mat, n, m);
    
    return 0;
}

void capolista(int mat[MAXN][MAXN], int n, int m) {
    int v[MAXN] = {0};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            v[j] += mat[j][i];
        }
        printf("La squadra capolista per la giornata %d è la numero %d\n", i+1, cercaMax(v, n));
    }
}

int cercaMax(int v[MAXN],int n) {
    int max = -1, index = -1;
    for (int i = 0; i < n; i++) {
        if (v[i] > max) {
            max = v[i];
            index = i+1;
        }
    }
    return index;
}
