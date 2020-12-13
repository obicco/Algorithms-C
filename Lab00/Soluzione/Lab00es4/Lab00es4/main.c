//
//  main.c
//  Lab00es4
//
//  Created by Oskar Bich on 24/10/2020.
//

#include <stdio.h>
#define MAX 20

// Presi da soluzione
int matSommaStampa(int mat[MAX][MAX], int nr, int nc, int D, int r0, int c0) {
  int sum = 0;
  for(int r = r0; r < r0+D; r++) {
    for(int c = c0; c < c0+D; c++) {
      /* Stampa */
      printf("%d ", mat[r][c]);
      sum += mat[r][c];
    }
    printf("\n");
  }
  printf("Matrice %dx%d a somma %d\n\n", D, D, sum);
  return sum;
}

void matDxD(int mat[MAX][MAX], int nr, int nc, int dim) {
  int sum, maxsum, max_i0 = -1, max_j0 = -1;
  if (dim <= 0 || dim > nr || dim > nc)
    return;
  printf("Matrici di dimensione %dx%d\n", dim, dim);
  /* Per tutti i punti [i,j] in cui può iniziare una matrice quadrata DxD */
  for(int i=0; i <= nr-dim; i++) {
    for(int j=0; j<= nc-dim; j++) {
      sum = matSommaStampa( mat, nr, nc, dim, i, j);
      /* Per tutte le celle di tale matrice */
      if (((max_i0 == -1)&&(max_j0 == -1)) || maxsum < sum) {
        maxsum = sum;
        max_i0 = i;
        max_j0 = j;
      }
    }
  }

  printf("Matrice di dimensione %dx%d a somma massima\n", dim, dim);
  sum = matSommaStampa( mat, nr, nc, dim, max_i0, max_j0);

}

int main(int argc, const char * argv[]) {
    int nr, nc, mat[MAX][MAX], dim;
    char fname[MAX];
    FILE *fp;
    printf("Inserire nome file:\n");
    scanf("%s", fname);
    
//  Acquisizione dati file
    fp = fopen(fname, "r");
    fscanf(fp, "%d%d", &nr, &nc);
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    
    do {
        printf("\nDimensione: ");
        if (scanf("%d", &dim) !=1)
            return 1;
        matDxD(mat, nr, nc, dim);
    } while (dim > 0 && dim <= nr && dim <= nc);
    return 0;
}
