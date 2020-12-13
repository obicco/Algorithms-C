//
//  main.c
//  DalProblemaAlProgramma
//
//  Created by Oskar Bich on 07/10/2020.
//

#include <stdio.h>
#include <math.h>

/*
int main(int argc, const char * argv[]) {
    
//  Scambio di valori tra variabili
    int a = 1;
    int b = 2;
    int tmp;
    
    tmp = a;
    a = b;
    b = tmp;
    
    
//  Accesso a vettori e matrici
    int V[10];      //Vetttore di 10 elementi
    float M[12][5]; //Matrice di 12 righe e 5 colonne
    
    //Assegna ad un vetorie la sequenza 1, 2, 3 ..., 10
    V[0] = 1;
    for (int i = 1; i < 10; i++) {
        V[i] = V[i - 1] + 1;
        printf("%d\n", V[i]);
    }
    //Incrementa di 1 gli elementi di una matrice
    for (int i = 0; i < 12; i++)
    for (int j = 0; j < 5; j++) {
        M[i][j]++;
    }
    
    //Apertura file "myfile.txt"
    FILE *fp;
    fp = fopen("myfile.txt", "r");
    //...
    fclose(fp);
            
    printf("%d , %d", a, b);
    return 0;
}
*/


// PROBLEMI NUMERICI
// Problema non iterativo - Risoluzione di equazioni di II grado
/*
int main(int argc, const char * argv[]) {
    float a, b, c, delta, x0, x1, re, im;
    
    printf("Coefficienti (a b c): ");
    scanf("%f%f%f", &a, &b, &c);
    if (a == 0 && b == 0 && c == 0)
        printf("Equazione indetermianta\n");
    if (a == 0 && b == 0 && c != 0)
        printf("Equazione impossibile\n");
    if (a == 0 && b!= 0) {
        printf("Equazione di primo grado\n");
        printf("Soluzione: %f\n", -c/b);
    }
    if (a != 0) {
        delta = b * b - 4 * a * c;
        if (delta == 0) {
            x0 = (-b) / (2 * a);
            x1 = (-b) / (2 * a);
            printf("Due soluzioni reali coincidenti: %f %f\n", x0, x1);
        }
        if (delta > 0) {
            x0 = (-b - sqrt(delta)) / (2 * a);
            x1 = (-b + sqrt(delta)) / (2 * a);
            printf("Due soluzioni reali distinte: %f %f\n", x0, x1);
        }
        if (delta < 0) {
            re = -b / (2 * a);
            im = sqrt(-delta) / (2 * a);
            printf("Due soluzioni complesse coniugate: ");
            printf("x0 = %f - i * %f \t x1 = %f + i * %f\n", re, im, re, im);
        }
    }
    return 0;
}*/

// Problema iterativo - Valutazione della ridotta n-esima di una serie armonica
int main(void) {
    int n, i;
    float HN;
    
    printf("Numero di termini (<= 0 per finire)");
    scanf("%d", &n);
    
    while (n > 0) {
        HN = 0.0;
        for (i = 1; i <= n; i++) {
            HN = HN + 1.0 / ((float)i);
        }
        printf("Risultato: %f\n", HN);
        printf("num. di termini (<= 0 = FINE): ");
        scanf("%d", &n);
    }
}
