//
//  main.c
//  Lab07es2
//
//  Created by Oskar Bich on 05/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXS 50
#define CMD 7

typedef struct {int dd, mm, yyyy;} Date;

typedef struct {
    char *cod;
    char *name;
    char *surname;
    Date date;
    char *address;
    char *city;
    int cap;
} Item;

typedef struct Node *link;

struct Node {
    Item *val;
    link next;
};

void printInstructions(char *instructions[], int *sel);
link loadFile(link head, char* file);
Item* readItem(FILE *fp);
link insertSorted(link head, Item* val);
int compareDate(Date d1, Date d2);
void printList(link head, char *file);
void printItem(Item *val, FILE *file);
Item* searchItemCod(link head, char *cod);
link add(link head);
void freeItem(Item *val);
Item* deleteItemCod(link *head, char *cod);
Item* deleteItemDate(link *head, Date d1, Date d2);

int main(int argc, const char * argv[]) {
    char *instructions[] = {"Uscita", "Inserimento elemento da tastiera", "Inserimento elementi da file", "Ricerca per codice", "Cancellazione elemeto per codice", "Cancellazione elementi tra date", "Stampa lista su file"};
    link head = NULL;
    Item *val = NULL;
    int end = 0, sel, flag = 0;
    char fn[MAXS], cod[MAXS], tmp_d1[11], tmp_d2[11];
    Date d1, d2;
    
    do {
        printInstructions(instructions, &sel);
        switch (sel) {
            case 0:
                end = 1;
                break;
            case 1:
                printf("Inserire anagrafica nel seguente formato:\n");
                head = add(head);
                printf("\nELENCO AGGIORNATO\n");
                printList(head, NULL);
                break;
            case 2:
                printf("Inserisci nome file:\n");
                scanf("%s", fn);
                head = loadFile(head, fn);
                printf("\nELENCO AGGIORNATO\n");
                printList(head, NULL);
                break;
            case 3:
                printf("Inserisci codice ricerca:\n");
                scanf("%s", cod);
                if ((val = searchItemCod(head, cod)) != NULL)
                    printItem(val, stdout);
                else printf("Codice non trovato\n");
                break;
            case 4:
                printf("Inserisci codice da eliminare:\n");
                scanf("%s", cod);
                if ((val = deleteItemCod(&head, cod)) != NULL) {
                    printf("Elemento eliminato: ");
                    printItem(val, stdout);
                    printf("\nELENCO AGGIORNATO\n");
                    printList(head, NULL);
                }
                else printf("Errore eliminazione - Codice non trovato\n");
                freeItem(val);
                break;
            case 5:
                printf("Inserire data inizio intervallo eliminazione [gg/mm/aaaa]\n");
                scanf("%s", tmp_d1);
                printf("Inserire data fine intervallo eliminazione [gg/mm/aaaa]\n");
                scanf("%s", tmp_d2);
                sscanf(tmp_d1, "%d/%d/%d", &d1.dd, &d1.mm, &d1.yyyy);
                sscanf(tmp_d2, "%d/%d/%d", &d2.dd, &d2.mm, &d2.yyyy);
                if (compareDate(d1, d2) > 0) {
                  Date tmp;
                  tmp = d1;
                  d1 = d2;
                  d2 = tmp;
                }
                while((val = deleteItemDate(&head, d1, d2)) != NULL) {
                    printf("Elemento eliminato: ");
                    printItem(val, stdout);
                    freeItem(val);
                    flag = 1;
                }
                if (!flag) printf("Errore eliminazione - Nessun elemento trovato nell'intervallo date\n");
                printf("\nELENCO AGGIORNATO\n");
                printList(head, NULL);
                flag = 0;
                break;
            case 6:
                printf("Inserire nome file output\n");
                scanf("%s", fn);
                printList(head, fn);
                break;
            default:
                printf("Scelta non valida\n");
                break;
        }
    } while(!end);
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

link loadFile(link head, char* file) {
    FILE *fIN = fopen(file, "r");
    Item *val;
    if (fIN == NULL)
        exit(-1);
    
    while ((val = readItem(fIN)) != NULL) {
        head = insertSorted(head, val);
    }
    fclose(fIN);
    return head;
}

Item* readItem(FILE *fp) {
    Item *val = NULL;
    int tmp_cap;
    char tmp_cod[MAXS], tmp_name[MAXS], tmp_surname[MAXS], tmp_date[11], tmp_address[MAXS], tmp_city[MAXS];
    if (fscanf(fp, "%s%s%s%s%s%s%d", tmp_cod, tmp_name, tmp_surname, tmp_date, tmp_address, tmp_city, &tmp_cap) == 7){
        val = (Item *) malloc(sizeof(Item));
        if(val == NULL)
            return NULL;
        sscanf(tmp_date, "%d/%d/%d", &val->date.dd, &val->date.mm, &val->date.yyyy);
        val->cod = strdup(tmp_cod);
        val->name = strdup(tmp_name);
        val->surname = strdup(tmp_surname);
        val->address = strdup(tmp_address);
        val->city = strdup(tmp_city);
        val->cap = tmp_cap;
    }
    return val;
}

link insertSorted(link head, Item* val) {
    link prev = NULL, curr = head, newnode;
    
    while (curr != NULL && compareDate(val->date, curr->val->date) >= 0) {
        prev = curr;
        curr = curr->next;
    }
    newnode = malloc(sizeof(link*));
    if (prev == NULL) {
        newnode->val = val;
        newnode->next = curr;
        return newnode;
    } else {
        prev->next = newnode;
        newnode->val = val;
        newnode->next = curr;
    }
    return head;
}

int compareDate(Date d1, Date d2) {
    if (d1.yyyy != d2.yyyy)
        return (d1.yyyy-d2.yyyy);
    else if (d1.mm != d2.mm)
        return (d1.mm-d2.mm);
    else if (d1.dd != d2.dd)
        return (d1.dd-d2.dd);
    else return 0;
}

void printList(link head, char *file) {
    link prev = NULL, curr = head;
    FILE *fOUT;
    if (file == NULL)
        fOUT = stdout;
    else fOUT = fopen(file, "w");
    while (curr != NULL) {
        printItem(curr->val, fOUT);
        prev = curr;
        curr = curr->next;
    }
    if (file != NULL) fclose(fOUT);
}

void printItem(Item *val, FILE* file) {
    fprintf(file, "%s %s %s %d/%d/%d %s %s %d\n", val->cod, val->name, val->surname, val->date.dd, val->date.mm, val->date.yyyy, val->address, val->city, val->cap);
}

link add(link head) {
    Item *val = NULL;
    printf("codice nome cognome data[gg/mm/yyyy] via citta' cap\n");
    if ((val = readItem(stdin)) !=NULL)
        head = insertSorted(head, val);
    else printf("Errore inserimento elemento\n");
    return head;
}

Item* searchItemCod(link head, char *cod) {
    link curr = head;
    while (curr != NULL && strcmp(curr->val->cod, cod) != 0) {
        curr = curr->next;
    }
    if (curr == NULL)
        return NULL;
    else return curr->val;
}

void freeItem(Item *val) {
    if (val == NULL)
        return;
    free(val->cod);
    free(val->name);
    free(val->surname);
    free(val->address);
    free(val->city);
    free(val);
}

Item* deleteItemCod(link *head, char *cod) {
    Item *val;
    link prev = NULL, curr = *head;
    while (curr != NULL && strcmp(curr->val->cod, cod) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL)
        return NULL;
    val = curr->val;
    if (prev == NULL)
        *head = curr->next;
    else prev->next = curr->next;
    free(curr);
    return val;
}

Item* deleteItemDate(link *head, Date d1, Date d2) {
    Item *val;
    link prev = NULL, curr = *head;
    while (curr != NULL && compareDate(d1, curr->val->date) >= 0) {
        prev = curr;
        curr = curr->next;
    }
    if (compareDate(d2, curr->val->date) >= 0) {
        val = curr->val;
        if (prev == NULL)
            *head = curr->next;
        else prev->next = curr->next;
        free(curr);
        return val;
    }
    return NULL;
}
