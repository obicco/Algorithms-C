//
//  main.c
//  AP_Exam042021
//
//  Created by Oskar Bich on 1/9/21.
//

#include <stdio.h>
#include <stdlib.h>

void f(int *v1, int *v2, int d1, int d2, int ***m);

int main(int argc, const char * argv[]) {
    int d1 = 3, d2 = 4;
    int ***m = malloc(d1*sizeof(***m));
    int *v1 = malloc(d1*sizeof(int));
    int *v2 = malloc(d2*sizeof(int));
    
    v1[0] = 2;
    v1[1] = 4;
    v1[2] = 6;
    
    v2[0] = 1;
    v2[1] = 3;
    v2[2] = 5;
    v2[3] = 7;
    
    f(v1, v2, d1, d2, m);
    
    for (int i = 0; i < d1; i++) {
        for (int j = 0; j < d2; j++) {
            printf("%d ", *m[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

void f(int *v1, int *v2, int d1, int d2, int ***m) {
    *m = malloc(d1*sizeof(**m));
    for (int i = 0; i < d1; i++) {
        *m[i] = malloc(d2*sizeof(***m));
        for (int j = 0; j < d2; j++) {
            *m[i][j] = v1[i] + v2[j]; //Dimenticato asterisco puntatore
        }
    }
}
