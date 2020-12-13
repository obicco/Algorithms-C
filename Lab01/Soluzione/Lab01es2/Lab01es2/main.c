//
//  main.c
//  Lab01es2
//
//  Created by Oskar Bich on 26/10/2020.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define LEN 201
#define NUM 30

typedef struct {
    char cod[LEN];
    char ph[LEN];
} entry;

int leggiDizionario(FILE *fp, entry diz[]);

int confronta(char riga[], int inizio, char parola[], int l);

int main(int argc, const char * argv[]) {
    int n, len, match;
    entry diz[NUM];
    FILE *fp1 = fopen("sorgente.txt", "r"), *fp2 = fopen("dizionario.txt", "r"), *fp3 = fopen("ricodificato.txt", "w");
    char phrase[LEN];
    
    n = leggiDizionario(fp2, diz);
    
    printf("Dizionario:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %s\n", diz[i].cod, diz[i].ph);
    }
    
    while (fgets(phrase, LEN, fp1) != NULL) {
        for (int i = 0; i < strlen(phrase); i++) {
            match = 0;
            for (int j = 0; j < n; j++) {
                len = (int) strlen(diz[j].ph);
                if (confronta(phrase, i, diz[j].ph, len)) {
                    fprintf(fp3,"%s", diz[j].cod);
                    i += len-1;
                    match = 1;
                    break;
                }
            }
            if (!match)
                fprintf(fp3, "%c", phrase[i]);
        }
    }
    
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}

int leggiDizionario(FILE *fp, entry diz[]) {
    int n;
    
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%s%s", diz[i].cod, diz[i].ph);
    }
    return n;
}

int confronta(char psorgente[], int inizio, char pdiz[], int l){
    for (int i = 0; i < l; i++) {
        if (psorgente[inizio+i] != pdiz[i])
            return 0;
    }
    return 1;
}
