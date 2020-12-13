//
//  main.c
//  Lab01es3
//
//  Created by Oskar Bich on 26/10/2020.
//

#include <stdio.h>
#include <string.h>
#define maxN 30

typedef struct {int r; int c;} dim;

void ruota (int v[maxN], int N, int P, int dir);
dim leggiMatrice (FILE *fp, int mat[maxN][maxN]);
void stampaMatrice (FILE *fp,int mat[maxN][maxN], dim dimensioni);
void ruotaMatrice(int mat[maxN][maxN], dim dimensioni, char sel[9],int index, char dir[9], int pos);

int main(int argc, const char * argv[]) {
    int mat[maxN][maxN], index, pos;
    dim dimensioni;
    char fname[20], sel[9], dir[9];
    
    printf("Inserire nome file\n");
    scanf("%s", fname);
    
    FILE *fp = fopen(fname, "r");
    
    dimensioni = leggiMatrice(fp, mat);
    stampaMatrice(stdout, mat, dimensioni);
    do {
    printf("Inserire comando:\n[Formato <selettore> <indice> <direzione> <posizioni>]\n");
    scanf("%s %d %s %d", sel, &index, dir, &pos);
        if ((strcmp(sel, "riga") == 0 || strcmp(sel, "colonna") == 0 || strcmp(sel, "fine") == 0) && (strcmp(dir, "destra") == 0 || strcmp(dir, "sinistra") == 0 || strcmp(dir, "su") == 0|| strcmp(dir, "giu")== 0)){
            printf("Input valido\n");
            ruotaMatrice(mat, dimensioni, sel, index, dir, pos);
        }
        
    else printf("Input non valido, indicare i seguenti comandi:\nSelettore: riga - colonna - fine\nDirezione: destra - sinistra - su - giu");
        
    } while (strcmp(sel, "fine") != 0);
}

//da implementare
void ruotaMatrice(int mat[maxN][maxN], dim dimensioni, char sel[9],int index, char dir[9], int pos) {
    
}

dim leggiMatrice (FILE *fp, int mat[maxN][maxN]) {
    int nr, nc;
    dim dimensioni;
    
    fscanf(fp, "%d%d", &nr, &nc);
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);
    dimensioni.r = nr;
    dimensioni.c = nc;
    return dimensioni;
}

void stampaMatrice (FILE *fp,int mat[maxN][maxN], dim dimensioni) {
    for (int i = 0; i < dimensioni.r; i++) {
        for (int j = 0; j < dimensioni.c; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void ruota (int v[maxN], int N, int P, int dir) {
    int tmpV[N];
    for (int i = 0; i < N; i++){
        tmpV[i] = 0;
    }
    if (dir == 1 && P != 0) {
    for (int i = 0; i < N; i++) {
        if (i+P < N)
            tmpV[i] = v[i+P];
        else
            tmpV[i] = v[i+P-N];
        }
    }
    else if (dir == -1 && P != 0) {
        for (int i = 0; i < N; i++) {
            if (N-P+i < N)
                tmpV[N-P+i] = v[i];
            else
                tmpV[i-P] = v[i];
            }
    }
    for (int i = 0; i < N; i++) {
        printf("%d", tmpV[i]);
    }
}

