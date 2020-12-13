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

dim leggiMatrice (FILE *fp, int mat[maxN][maxN]);
void stampaMatrice (int mat[maxN][maxN], dim d);
void individuaRegioni (int mat[maxN][maxN], dim d);
int individuaB (int mat[maxN][maxN],dim index, int nr);
int individuaH (int mat[maxN][maxN],dim index, int nc);
matrix leggiRegione (int b, int h);

int main(int argc, const char * argv[]) {
    int mat[maxN][maxN];
    dim dimensioni;
    FILE *fIN = fopen("mappa.txt", "r");
    
    dimensioni = leggiMatrice(fIN, mat);
    stampaMatrice(mat, dimensioni);
    
    individuaRegioni(mat, dimensioni);
    
    return 0;
}

void individuaRegioni (int mat[maxN][maxN], dim d) {
    matrix current, regioneMB = {0}, regioneMH = {0}, regioneMA = {0};
    
    for (int i = 0; i < d.nr; i++) {
        for (int j = 0; j < d.nc; j++) {
            if (mat[i][j] == 1) {
                dim index = {i, j};
                current = leggiRegione(individuaB(mat, index, d.nr), individuaH(mat, index, d.nc));
                current.r = i; current.c = j;
                j += current.b;
                if (regioneMB.b < current.b)
                    regioneMB = current;
                if (regioneMH.h < current.h)
                    regioneMH = current;
                if (regioneMA.a < current.a)
                    regioneMA = current;
            }
        }
    }
    printf("\nMax Base: estr. sup. SX = <%d,%d> b = %d, h = %d, Area = %d", regioneMB.r, regioneMB.c, regioneMB.b, regioneMB.h, regioneMB.a);
    printf("\nMax Area: estr. sup. SX = <%d,%d> b = %d, h = %d, Area = %d", regioneMA.r, regioneMA.c, regioneMA.b, regioneMA.h, regioneMA.a);
    printf("\nMax Altezza: estr. sup. SX = <%d,%d> b = %d, h = %d, Area = %d\n", regioneMH.r, regioneMH.c, regioneMH.b, regioneMH.h, regioneMH.a);
}

int individuaB (int mat[maxN][maxN],dim index, int nr) {
    int cnt = 0;
    for(int i = 0; i < nr; i++) {
        if (mat[index.nr][index.nc+i] == 1) {
            cnt++;
        } else return cnt;
    }
    return cnt;
}

int individuaH (int mat[maxN][maxN],dim index, int nc) {
    int cnt = 0;
    for(int j = 0; j < nc; j++) {
        if (mat[index.nr+j][index.nc] == 1) {
            cnt++;
        } else return cnt;
    }
    return cnt;
}

matrix leggiRegione (int b, int h) {
    matrix current = {0};
    current.b = b;
    current.h = h;
    current.a = (b*h);
    return current;
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
    dimensioni.nr = nr;
    dimensioni.nc = nc;
    return dimensioni;
}

void stampaMatrice (int mat[maxN][maxN], dim d) {
    for (int i = 0; i < d.nr; i++) {
        for(int j = 0; j < d.nc; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
