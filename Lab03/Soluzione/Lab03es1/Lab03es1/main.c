//
//  main.c
//  Lab02es1
//
//  Created by Oskar Bich on 01/11/2020.
//

#include <stdio.h>
#define maxN 50

typedef struct {int nr ,nc;} dim;
typedef struct {int r ,c, h, b, a;} matrix;

void leggiMatrice (FILE *fp, int mat[maxN][maxN], int *nr, int *nc);
void stampaMatrice (int mat[maxN][maxN], int nr, int nc);
void individuaRegioni (int mat[maxN][maxN], int nr, int nc);
int riconosciRegione(int mat[maxN][maxN],int nr,int nc,int r,int c,int *b, int *h);
matrix assegnaRegione (int b, int h, int r, int c);

int main(int argc, const char * argv[]) {
    int nr, nc;
    int mat[maxN][maxN];
    FILE *fIN = fopen("mat.txt", "r");
    
    leggiMatrice(fIN, mat, &nr, &nc);
    stampaMatrice(mat, nr, nc);
    
    individuaRegioni(mat, nr, nc);
    
    return 0;
}

void individuaRegioni (int mat[maxN][maxN], int nr, int nc) {
    matrix regioneMB = {0}, regioneMH = {0}, regioneMA = {0};
    int b, h;
    
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            b = 0; h = 0;
            if(riconosciRegione(mat, nr, nc, i, j,&b, &h)) {
                if (regioneMB.b < b)
                    regioneMB = assegnaRegione(b, h, i, j);
                if (regioneMH.h < h)
                    regioneMH = assegnaRegione(b, h, i, j);
                if (regioneMA.a < (b*h))
                    regioneMA = assegnaRegione(b, h, i, j);
                j += b;
            }
        }
    }
    printf("\nMax Base: estr. sup. SX = <%d,%d> b = %d, h = %d, Area = %d", regioneMB.r, regioneMB.c, regioneMB.b, regioneMB.h, regioneMB.a);
    printf("\nMax Area: estr. sup. SX = <%d,%d> b = %d, h = %d, Area = %d", regioneMA.r, regioneMA.c, regioneMA.b, regioneMA.h, regioneMA.a);
    printf("\nMax Altezza: estr. sup. SX = <%d,%d> b = %d, h = %d, Area = %d\n", regioneMH.r, regioneMH.c, regioneMH.b, regioneMH.h, regioneMH.a);
}

matrix assegnaRegione (int b, int h, int r, int c) {
    matrix current = {0};
    current.b = b;
    current.h = h;
    current.a = (b*h);
    current.r = r;
    current.c = c;
    return current;
}

void leggiMatrice (FILE *fp, int mat[maxN][maxN], int *nr, int *nc) {
    fscanf(fp, "%d%d", nr, nc);
    for (int i = 0; i < *nr; i++) {
        for (int j = 0; j < *nc; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);
}

void stampaMatrice (int mat[maxN][maxN], int nr, int nc) {
    for (int i = 0; i < nr; i++) {
        for(int j = 0; j < nc; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int riconosciRegione(int mat[maxN][maxN],int nr,int nc,int r,int c,int *b, int *h) {
    int i = 0, j = 0;
    if(mat[r][c] == 0)
        return 0;
    while (i < nr && mat[r][c+i] == 1) {
        *b += 1;
        i++;
    }
    while (j < nr && mat[r+j][c] == 1) {
        *h += 1;
        j++;
    }
    return 1;
}
