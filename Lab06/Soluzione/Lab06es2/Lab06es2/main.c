//
//  main.c
//  Lab06es2
//
//  Created by Oskar Bich on 28/11/20.
// mat.txt

#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int *nr, int *nc);
void malloc2dP(int ***mat, int *nr, int *nc);
void separate(int **mat, int nr, int nc, int **vb, int **vw, int *nb, int *nw);
void print(int *v, int n);

int main(int argc, const char * argv[]) {
    int **mat, nr, nc, *vblack, *vwhite, nb, nw;
    
//    mat = malloc2dR(&nr, &nc);
    malloc2dP(&mat, &nr, &nc);
    
    separate(mat, nr, nc, &vblack, &vwhite, &nb, &nw);
    print(vblack, nb);
    print(vwhite, nw);
    
    return 0;
}

void separate(int **mat, int nr, int nc, int **vb, int **vw, int *nb, int *nw) {
    int bcnt = 0, wcnt = 0;
    *nb = ((nr*nc)/2)+((nr*nc)%2);
    *nw =(nr*nc)/2;
    *vb = (int *) calloc(*nb, sizeof(int));
    *vw = (int *) calloc(*nw, sizeof(int));
    for(int i = 0; i < nr; i++) {
        for(int j = 0; j < nc; j++) {
            if((i+j)%2)
                (*vw)[wcnt++] = mat[i][j];
            else
                (*vb)[bcnt++] = mat[i][j];
        }
    }
}

void print(int *v, int n) {
    for(int i = 0; i < n; i++) {
            printf("%d ", v[i]);
    }
    printf("\n");
}


int **malloc2dR(int *nr, int *nc) {
    int **mat;
    FILE *fIN = fopen("mat.txt", "r");
    
    fscanf(fIN, "%d%d", nr, nc);
    mat = (int**) calloc(*nr, sizeof(int*));
    
    for(int i = 0; i < *nr; i++) {
        mat[i] = (int*) calloc(*nc, sizeof(int));
        for (int j = 0; j < *nc; j++) {
            fscanf(fIN, "%d", &mat[i][j]);
        }
    }
    fclose(fIN);
    return mat;
}

void malloc2dP(int ***mat, int *nr, int *nc) {
    FILE *fIN = fopen("mat.txt", "r");
    
    fscanf(fIN, "%d%d", nr, nc);
    *mat = (int**) calloc(*nr, sizeof(int*));
    for(int i = 0; i < *nr; i++) {
        (*mat)[i] = (int*) calloc(*nc, sizeof(int));
        for (int j = 0; j < *nc; j++) {
            fscanf(fIN, "%d", &(*mat)[i][j]);
        }
    }
    fclose(fIN);
}
