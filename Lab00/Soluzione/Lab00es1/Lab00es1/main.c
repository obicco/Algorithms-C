//
//  main.c
//  Lab00es1
//  Sia V un  vettore di N interi(N < 30).  Si  scriva  un  programma  in  C  che,  una  volta  acquisito da tastiera tale  vettore, visualizzi tutti  i  sottovettori  di  dimensione  massima  formati  da  celle  contigue contenenti dati non nulli.
//
//  Esempio: dato il vettore [1 3 4 0 1 0 9 4 2 0], i due sottovettori di dimensione massima (3) contenenti dati non nulli sono [1 3 4] e [9 4 2].
//
//  Created by Oskar Bich on 06/10/2020.
//

#include <stdio.h>
#define N 30

int main(int argc, const char * argv[]) {
    int v[N];
    int l, i, dim = 0, cnt = 0, flag;
    printf("Inserire lunghezza vettore:\n");
    scanf("%d", &l);
    printf("Inserire elementi vettore\n");
    
    for (i = 0; i < l; i++) {
        scanf("%d", &v[i]);
        if (v[i] != 0)
            cnt++;
        else {
            if (cnt > dim)
                dim = cnt;
            cnt = 0;
        }
    }
    
    printf("\nSottovettori di dimensione massima:\n");
    for (i = 0; i < l; i++) {
        flag = 0;
        for (int j = 0; j < dim && flag != 1; j++) {
            if (v[i+j] == 0) {
                i += j;
                flag = 1;
            }
            else if (j == dim-1) {
                for (int k = 0; k < dim; k++) {
                    printf("%d", v[i+k]);
                }
                i += dim;
                flag = 1;
                printf("\n");
            }
        }
    }
    return 0;
}


