//
//  main.c
//  Lab03es2
//
//  Created by Oskar Bich on 13/11/20.
//

#include <stdio.h>

int endianCheck(void);
void stampaCodifica(void *p, int size, int bigEndian);

int main(int argc, const char * argv[]) {
    float af;
    double ad;
    long double ald;
    int bigEndian = endianCheck();
    printf("Il sistema è: %s ENDIAN\n", bigEndian ? "BIG":"LITTLE");
    
    printf("Dimensioni:\naf = %d byte (%d bit)\tad = %d byte (%d bit)\tald = %d byte (%d bit)\n", (int)sizeof(af), 8*(int)sizeof(af), (int)sizeof(ad), 8*(int)sizeof(ad), (int)sizeof(ald), 8*(int)sizeof(ald));
    
    printf("Inserire numero decimale (compatibile con float, double e long double)");
    scanf("%f", &af);
    
    ad = (double) af;
    ald = (long double) af;
    
//    To-Do: correct binary printing
    stampaCodifica((void *)&af, sizeof(af), bigEndian);
    stampaCodifica((void *)&ad, sizeof(ad), bigEndian);
    stampaCodifica((void *)&ald, sizeof(ald), bigEndian);
    
    return 0;
}

int endianCheck() {
    int test = 1;
    char *pchar = (char *) &test;
    return (*pchar == 0);
}

void stampaCodifica(void *p, int size, int bigEndian) {
    char *pchar;
    pchar = p;
    if (!bigEndian) {
        for (int i = size; i >= 0; i--)
          {
              printf("%d", *pchar+i);
          }

          printf("\n");


    }
}
