//
//  main.c
//  AP_Exam032021
//
//  Created by Oskar Bich on 15/6/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LIST.h"
#define N 6

void f(int **m, int n, int k);
void split(LIST l, char *str, char sep);

int main(int argc, const char * argv[]) {
    //ESERCIZIO 1
    int M[N][N] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 1},
        {1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 1},
        {0, 1, 1, 1, 0, 1},
        {0, 1, 0, 1, 1, 0}
    };
    int k = 2;
    int **m = malloc(N*sizeof(int*));
    for(int i = 0; i < N; i++) {
        m[i] = malloc(N*sizeof(int));
        for (int j = 0; j < N; j++) {
            m[i][j] = M[i][j];
        }
    }
    printf("E1 - Elenco relazioni di amicizia:\n");
    f(m, N, k);
    printf("\n");
    
    //ESERCIZIO 2
    LIST l = newLIST(NEWnode("", NULL));
    
    split(l, "ramarro", 'r');
    printf("\nE2 - Lista split:\n");
    printLIST(l);
    
    return 0;
}

void f(int **m, int n, int k) {
    int cnt;
    for (int x = 0; x < n; x++) {
        for (int i = x+1; i < n; i++) { //Cambiato punto di partenza a x+1 per non ripetere gli amici già relazionati, tolto quindi if (x != i)
            cnt = 0;
            for (int j = 0; j < n; j++) {
                if (m[x][j] == 1 && m[x][j] == m[i][j]) //Dimenticato il termine di confronto con 1
                    cnt++;
            }
            if (cnt >= k)
                printf("(%d, %d) ", x, i);
        }
    }
}

void split(LIST l, char *str, char sep) {
    int i = 0, len = (int) strlen(str), cnt = 0; //Variabile lunghezza stringa chiamata come la variabile lista per distrazione/abitudine
    char tmp[len];
    while(str[i] != '\0') {
        if (str[i] == sep && cnt != 0) {
            tmp[cnt+1] = '\0';
            addNode(l, tmp);
            cnt = 0;
        }
        else if (str[i] == sep && str[i+1] == sep) { //aggiunto caso doppio sep consecutivo
            tmp[cnt+1] = '\0';
            addNode(l, tmp);
            i++;
        } else tmp[cnt++] = str[i++];
    }
    tmp[cnt] = '\0'; //aggiunta iterazione all'uscita del while
    addNode(l, tmp); //
}
