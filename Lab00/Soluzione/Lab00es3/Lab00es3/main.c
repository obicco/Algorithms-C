//
//  main.c
//  Lab00es3
//
//  Created by Oskar Bich on 24/10/2020.
//

#include <stdio.h>
#define maxN 30

void ruota (int v[maxN], int N, int P, int dir);

int main(int argc, const char * argv[]) {
    int N, P = 1, dir, v[maxN], exit = 0;
    
    printf("Inserire lunghezza vettore:\n");
    scanf("%d", &N);
    
    printf("Inserire elementi vettore:\n");
    for (int i = 0; i < N; i++) {
        scanf("%d", &v[i]);
    }
    
    while (P != 0) {
        printf("Inserire\n- # elementi da spostare [0 per terminare]: ");
        scanf("%d", &P);
        if (P == 0)
            return 0;
        printf("- direzione[-1 dx, 1 sx]: ");
        scanf("%d", &dir);
        ruota(v, N, P, dir);
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
