//
//  main.c
//  AP_Exam022022
//
//  Created by Oskar Bich on 10/2/22.
//

#include <stdio.h>
#include <stdlib.h>
#define R 3
#define C 4
#define N 4
#define K 2

//ESERCIZIO 1
void f(int **M, int r, int c, int ***Mout, int *nr, int *nc);
int **loadEx1(void);

//ESERCIZIO 3
void friends(int **M, int n, int k);
void disp_sempl(int pos, int **M, int *sol, int *bestsol, int *mark, int n, int k, int *max);
int check(int **M, int *sol, int n, int k);
int **loadEx3(void);

int main(int argc, const char * argv[]) {
    int **m1 = loadEx1();
    int **Mout, nr, nc;
    
    int **m3 = loadEx3();
    
    f(m1, R, C, &Mout, &nr, &nc);
    
    printf("Esercizio 1 - matrice di output:\n");
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%d ", Mout[i][j]);
        }
        printf("\n");
    }
    
    friends(m3, N, K);
    printf("\n\n");
    return 0;
}

void f(int **M, int r, int c, int ***Mout, int *nr, int *nc) {
    *nr = 0;
    *nc = 0;
    *Mout = malloc((r/2)*sizeof(**Mout));
    for (int i = 0; i < r; i++) {
        if (i % 2 == 0) { //Distrazione messo r al posto di i, caso analogo, ma corretto successivo con 'j % 2'
            (*Mout)[*nr] = malloc((c/2)*sizeof(***Mout));
            for (int j = 0; j < c; j++) {
                if (j % 2 == 0) {
                    (*Mout)[*nr][*nc] = M[i][j];
                    (*nc)++;
                }
            }
            *nc = 0;
            (*nr)++;
        }
    }
    *nc = c/2;
}



int **loadEx1(void) {
    int v[R*C] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2};
    int **m = malloc(R*sizeof(*m));
    for (int i = 0, k = 0; i < R; i++) {
        m[i] = malloc(C*sizeof(**m));
        for (int j = 0; j < C; j++, k++) {
            m[i][j] = v[k];
        }
    }
    return m;
}

void friends(int **M, int n, int k) {
    int *sol = malloc(n*sizeof(*sol));
    int max = k-1;
    int *bestsol = malloc(n*sizeof(*bestsol));
    int *mark = calloc(n, sizeof(*mark));
    disp_sempl(0, M, sol, bestsol, mark, n, k, &max);
    printf("\nEsercizio 2 - Insieme massimo di amici:\n");
    for (int i = 0; i < n; i++) {
        if (bestsol[i])
            printf("p%d ", i);
    }
}

void disp_sempl(int pos, int **M, int *sol, int *bestsol, int *mark, int n, int k, int *max) {
    int cnt;
    if (pos >= k) {
        cnt = check(M, sol, n, k);
        if (cnt >= k && cnt > *max) {
            for (int i = 0; i < n; i++){
                bestsol[i] = sol[i];
                printf("%d ", bestsol[i]);
            }
            *max = cnt;
        }
    }
    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[i] = 1;
            disp_sempl(pos+1, M, sol, bestsol, mark, n, k, max);
            mark[i] = 0;
            sol[i] = 0;
        }
    }
}

int check(int **M, int *sol, int n, int k) {
    int cnt = 0, max = 0;
    for (int i = 0; i < n; i++) {
        cnt = 0;
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;
            else {
                if (M[i][j] && sol[i])
                    cnt++;
            }
        }
        if (cnt >= k)
            max++;
    }
    return max;
}

int **loadEx3(void) {
    int v[N*N] = {1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1};
    int **m = malloc(N*sizeof(*m));
    for (int i = 0, k = 0; i < N; i++) {
        m[i] = malloc(N*sizeof(**m));
        for (int j = 0; j < N; j++, k++) {
            m[i][j] = v[k];
        }
    }
    return m;
}
