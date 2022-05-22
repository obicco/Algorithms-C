//
//  main.c
//  AP_Exam012022
//
//  Created by Oskar Bich on 27/1/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "BT.h"
#define R 3
#define C 3

int **allocateM(int r, int c);
void loadEx1(int **m);
void simplify(int **M, int r, int c, int ***nM, int *nr, int *nc);

int main(int argc, const char * argv[]) {
    int **m = allocateM(R, C), **nm, nr = 0, nc = 0;
    BT t = BTinit();
    
    loadEx1(m);
    simplify(m, R, C, &nm, &nr, &nc);
    
    loadEx2(t);
    if(checkBT(t))
        printf("Non e' un BT\n");
    else printf("E' un BT\n");
    return 0;
}

int **allocateM(int r, int c) {
    int **m = malloc(r*sizeof(*m));
    for (int i = 0; i < r; i++) m[i] = malloc(c*sizeof(**m));
    return m;
}

void simplify(int **M, int r, int c, int ***nM, int *nr, int *nc) { //AGG - Aggiunti argomenti per la memorizzazione della nuova matrice
    int vr[R] = {0};
    int vc[C] = {0};
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (M[i][j] == 0) {
                vr[i] = 1;
                vc[j] = 1;
            }
        }
        if (!vr[i]) { //AGG - Conteggio delle sezioni valide della matrice finale
            (*nr)++;
            (*nc)++;
        }
    }
    *nM = allocateM(*nr, *nc); //AGG - Alloco la matrice finale della dimensione corretta
    for (int i = 0, k = 0; i < r; i++) {
        for (int j = 0, z = 0; j < c; j++) {
            if (vr[i] == 0 && vc[j] == 0)
                *nM[k][z++] = M[i][j]; //AGG - Al posto di stampare memorizzo
        }
        if (!vr[i])
            k++; //AGG - Incremento se la righa scansionata era valida
    }
    
        
        
}

void loadEx1(int **m) {
    int v[9] = {1, 2, 3, 4, 0, 9, 7, 8, 9};
    for (int i = 0, k = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) m[i][j] = v[k++];
    }
}
