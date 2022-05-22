//
//  main.c
//  AP_Exam042016
//
//  Created by  on 31/8/21.
//

#include <stdio.h>
#include <stdlib.h>
#define R 3
#define C 4

int subMatMax (int **mat, int r, int c, int n);
int calcSum (int **mat, int r, int c, int n);


int main(int argc, const char * argv[]) {
    int M[R][C] = {
        {5, 2, 3, 1},
        {3, 1, 6, 4},
        {3, 0, 5, 2}
    };
    
    int **m = malloc(R*sizeof(int*));
    for(int i = 0; i < R; i++) {
        m[i] = malloc(C*sizeof(int));
        for (int j = 0; j < C; j++) {
            m[i][j] = M[i][j];
        }
    }
    printf("Somma sottomatrice di lato %d massima: %d\n", 2, subMatMax(m, R, C, 2));
    return 0;
}

int subMatMax (int **mat, int r, int c, int n) {
    int max = 0, curr;
    for (int i = 0; i < r-n+1; i++) {
        for (int j = 0; j < c-n+1; j++) {
            curr = calcSum (mat, i, j, n);
            if (curr > max)
                max = curr;
        }
    }
    return max;
}

int calcSum (int **mat, int r, int c, int n) {
    int sum = 0;
    for (int i = r; i < r+n; i++) {
        for (int j = c; j < c+n; j++) {
            sum += mat[i][j];
        }
    }
    return sum;
}
