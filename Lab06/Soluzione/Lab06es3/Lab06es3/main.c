//
//  main.c
//  Lab02es5
//
//  Created by Oskar Bich on 28/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000
#define MAXS 31
#define CMD 8
#define FILE_IN "log.txt"

typedef enum {NONE, DATE, COD, DEPARTURE, ARRIVAL} orderKey;

typedef struct {
    int y;
    int m;
    int d;
} date;

typedef struct {
    int h;
    int m;
    int s;
} time;

typedef struct{
    char *cod;
    char *dep;
    char *arr;
    date date;
    time dep_t;
    time arr_t;
    int delay;
} line;

typedef struct {
    int n;
    line *lines;
    line **lineDATE, **lineCOD, **lineDEP, **lineARR;
} table;

table *readLog(char *file);
void printLine(line line, char* file);
void printSortedLines(table *t, orderKey k, char* file);
void printInstructions(char *instructions[], int *sel);
void sort(line **l, int n, orderKey k);
int compareDate(date d1, date d2);
int compareTime(time t1, time t2);
int compareLines(line *l1, line *l2, orderKey k);
void searchDepDicotomic(table *t, char* dep, int l);
void freeTable(table *t);

int main(int argc, const char * argv[]) {
    char *instructions[] = {"Uscita", "Lettura log", "Stampa", "Ordina per data", "Ordina per codice", "Ordina per stazione di partenza", "Ordina per stazione di arrivo", "Ricerca per stazione di partenza"}, fn[MAXS], dep[MAXS];
    int go = 1, sel;
    table *tab = readLog(FILE_IN);
    
    do {
        printInstructions(instructions, &sel);
        switch(sel) {
            case 0:
                go = 0;
                break;
            case 1:
                printf("Inserire nome file log:\n");
                scanf("%s", fn);
                freeTable(tab);
                tab = readLog(fn);
                break;
            case 2:
                printf("Inserire nome file output ('t' per stampare su terminale):\n");
                scanf("%s", fn);
                for(int i = 0; i < tab->n; i++) {
                printLine(tab->lines[i], fn);
                }
                break;
            case 3:
                printf("Elenco ordinato per data\n");
                printSortedLines(tab, DATE, NULL);
                break;
            case 4:
                printf("Elenco ordinato per codice\n");
                printSortedLines(tab, COD, NULL);
                break;
            case 5:
                printf("Elenco ordinato per stazione di partenza\n");
                printSortedLines(tab, DEPARTURE, NULL);
                break;
            case 6:
                printf("Elenco ordinato per stazione di arrivo\n");
                printSortedLines(tab, ARRIVAL, NULL);
                break;
            case 7:
                printf("Inserire stazione di partenza:\n");
                scanf("%s", dep);
                searchDepDicotomic(tab, dep,(int) strlen(dep));
                break;
      default:
                printf("Scelta non valida\n");
                break;
        }
    } while(go);
    return 0;
}

table *readLog(char *file) {
    table *t = (table*) calloc(1, sizeof(table));
    char tmp_date[11], tmp_t1[9], tmp_t2[9], tmp_cod[MAXS], tmp_dep[MAXS], tmp_arr[MAXS];
    FILE *fIN = fopen(file, "r");
    if (fIN == NULL)
        exit (-1);
    
    fscanf(fIN, "%d", &t->n);
    
    t->lines = (line*)  calloc(t->n, sizeof(line));
    t->lineDATE = (line**)  calloc(t->n, sizeof(line*));
    t->lineCOD = (line**)  calloc(t->n, sizeof(line*));
    t->lineDEP = (line**)  calloc(t->n, sizeof(line*));
    t->lineARR = (line**)  calloc(t->n, sizeof(line*));
    
    for (int i = 0; i < t->n; i++) {
        fscanf(fIN, "%s %s %s %s %s %s %d", tmp_cod, tmp_dep, tmp_arr, tmp_date, tmp_t1, tmp_t2, &t->lines[i].delay);
        t->lines[i].cod = strdup(tmp_cod);
        t->lines[i].dep = strdup(tmp_dep);
        t->lines[i].arr = strdup(tmp_arr);
        sscanf(tmp_date, "%d/%d/%d", &t->lines[i].date.y, &t->lines[i].date.m, &t->lines[i].date.d);
        sscanf(tmp_t1, "%d:%d:%d", &t->lines[i].dep_t.h, &t->lines[i].dep_t.m, &t->lines[i].dep_t.s);
        sscanf(tmp_t2, "%d:%d:%d", &t->lines[i].arr_t.h, &t->lines[i].arr_t.m, &t->lines[i].arr_t.s);
    }
    fclose(fIN);
    
    for (int i = 0; i < t->n; i++) {
        t->lineDATE[i] = &t->lines[i];
        t->lineCOD[i] = &t->lines[i];
        t->lineDEP[i] = &t->lines[i];
        t->lineARR[i] = &t->lines[i];
    }
    
    sort(t->lineDATE, t->n, DATE);
    sort(t->lineCOD, t->n, COD);
    sort(t->lineDEP, t->n, DEPARTURE);
    sort(t->lineARR, t->n, ARRIVAL);
    
    return t;
}

void freeTable(table *t) {
    if (t == NULL)
        return;
    free(t->lineDATE);
    free(t->lineCOD);
    free(t->lineDEP);
    free(t->lineARR);
    for (int i = 0; i < t->n; i++) {
        free(t->lines[i].cod);
        free(t->lines[i].dep);
        free(t->lines[i].arr);
    }
    free(t->lines);
    free(t);
}

void printSortedLines(table *t, orderKey k, char* file) {
    switch (k) {
        case DATE:
            for(int i = 0; i < t->n; i++) printLine(*(t->lineDATE[i]), file);
            break;
        case COD:
            for(int i = 0; i < t->n; i++) printLine(*(t->lineCOD[i]), file);
            break;
        case DEPARTURE:
            for(int i = 0; i < t->n; i++) printLine(*(t->lineDEP[i]), file);
            break;
        case ARRIVAL:
            for(int i = 0; i < t->n; i++) printLine(*(t->lineARR[i]), file);
            break;
        default:
            printf("Errore in printSortedLines\n");
            break;
    }
}

void printLine(line line, char* file) {
    FILE *fp;
    if (file == NULL || !strcmp(file, "t"))
        fp = stdout;
    else fp = fopen(file, "a");
    
    fprintf(fp, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n", line.cod, line.dep, line.arr, line.date.y, line.date.m, line.date.d, line.dep_t.h, line.dep_t.m, line.dep_t.s, line.arr_t.h, line.arr_t.m, line.arr_t.s, line.delay);
    
    if (file != NULL && strcmp(file, "t"))
        fclose(fp);
}

void printInstructions(char *instructions[], int *sel) {
    printf("\nMENU\n");
    for (int i = 0; i < CMD; i++) {
        printf("%d - %s\n", i, instructions[i]);
    }
    printf("Comando > ");
    scanf("%d", sel);
}
             
int compareDate(date d1, date d2) {
    if (d1.y != d2.y)
        return (d1.y-d2.y);
    else if (d1.m != d2.m)
        return (d1.m-d2.m);
    else if (d1.d != d2.d)
        return (d1.d-d2.d);
    else return 0;
}

int compareTime(time t1, time t2) {
    if (t1.h != t2.h)
        return (t1.h-t2.h);
    else if (t1.m != t2.m)
        return (t1.m-t2.m);
    else if (t1.s != t2.s)
        return (t1.s-t2.s);
    else return 0;
}

void sort(line **l, int n, orderKey k) {
    line *tmp;
    for(int i = n-1; i > 0; i--) {
        for (int j = 0; j < i; j++ ) {
            if(compareLines(l[j], l[j+1], k) > 0) {
                tmp = l[j];
                l[j] = l[j+1];
                l[j+1] = tmp;
            }
        }
    }
}

int compareLines(line *l1, line *l2, orderKey k) {
    int cmp = 0;
    switch (k) {
        case DATE:
            cmp = compareDate(l1->date, l2->date);
            if (cmp == 0) return compareTime(l1->dep_t, l2->dep_t);
            return cmp;
            break;
        case COD:
            return strcmp(l1->cod, l2->cod);
            break;
        case DEPARTURE:
            return strcmp(l1->dep, l2->dep);
            break;
        case ARRIVAL:
            return strcmp(l1->arr, l2->arr);
            break;
        default:
            break;
    }
    return cmp;
}

void searchDepDicotomic(table *t, char* dep, int l) {
    int left = 0, right = t->n-1, a, cmp, found = 0;
    while (left <= right && !found) {
        a = (left + right)/2;
        cmp = strncmp(t->lineDEP[a]->dep, dep, l);
        if (cmp == 0) {
            found = 1;
            do {
                printLine(*(t->lineDEP[a]), NULL);
                a++;
            } while (a < t->n &&!strncmp(t->lineDEP[a]->dep, dep, l));
        }
        else if(cmp < 0)
            left = a + 1;
        else right = a - 1;
    }
    if (!found)
        printf("Stazione di partenza non trovata\n");
}
