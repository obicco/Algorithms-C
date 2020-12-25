//
//  main.c
//  Lab09es3
//
//  Created by Oskar Bich on 25/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pg.h"
#include "inv.h"
#define CMD 7
#define pg_file "pg.txt"
#define inv_file "inventario.txt"

void printInstructions(char *instructions[], int *sel);

int main(int argc, const char * argv[]) {
    char *instructions[] = {"Uscita", "Stampa personaggi", "Stampa inventario", "Aggiungere personaggio", "Rimuovere personaggio", "Aggiungere/rimuovere equipaggiamento personaggio", "Calcolare statistiche personaggio"};
    int end = 0, sel, flag;
    char tmpString[51];
    tabPg_t *tabPg = loadFilePg(pg_file);
    tabInv_t *tabInv = loadFileInv(inv_file);
    do {
        printInstructions(instructions, &sel);
        switch (sel) {
            case 0:
                end = 1;
                break;
            case 1:
                printTabPg(tabPg);
                break;
            case 2:
                printTabInv(tabInv);
                break;
            case 3:
                printf("Inserire personaggio [Codice Nome Classe hp mp atk def mag spr]\n");
                readPg(stdin, tabPg);
                printf("\n- Aggiornamento -\n");
                printTabPg(tabPg);
                break;
            case 4:
                printf("Inserire codice personaggio da eliminare:\n");
                scanf("%s", tmpString);
                if(deletePgCod(tabPg, tmpString)) {
                    printf("\n- Aggiornamento -\n");
                    printTabPg(tabPg);
                } else printf("Errore cancellazione - Codice non trovato\n");
                break;
            case 5:
                printf("1 - Aggiungere equipaggiamento\n2 - Rimuovere equipaggiamento\nComando > ");
                scanf("%d", &flag);
                if (flag != 1 && flag != 2)
                    printf("Scelta non valida\n");
                else attributeEquip(tabPg, tabInv, flag);
                break;
            case 6:
                printf("Inserire codice personaggio da visualizzare:\n");
                scanf("%s", tmpString);
                printStatsWithEq(searchPgCod(tabPg, tmpString), tabInv);
                break;
            default:
                printf("Scelta non valida\n");
                break;
        }
    } while(!end);
    freeTabPg(tabPg);
    freeTabInv(tabInv);
    return 0;
}

void printInstructions(char *instructions[], int *sel) {
    printf("\nMENU\n");
    for (int i = 0; i < CMD; i++) {
        printf("%d - %s\n", i, instructions[i]);
    }
    printf("Comando > ");
    scanf("%d", sel);
}
