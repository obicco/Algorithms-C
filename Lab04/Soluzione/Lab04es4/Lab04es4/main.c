//
//  main.c
//  Lab02es4
//
//  Created by Oskar Bich on 04/11/2020.
//

#include <stdio.h>
#include <string.h>
#define MAXN 1000
#define MAXS 31
#define CMD 7

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
    char cod[MAXS];
    char dep[MAXS];
    char arr[MAXS];
    date date;
    time dep_t;
    time arr_t;
    int delay;
} line;

typedef struct {
    int n;
    line lines[MAXN];
    orderKey k;
} table;

table readLog(void);
void printLine(line line, char* file);
void printInstructions(char *instructions[], int *sel);
void sort(table *t, orderKey k);
int compareDate(date d1, date d2);
int compareTime(time t1, time t2);
int compareLines(line l1, line l2, orderKey k);
void searchDepLinear(table t, char* dep, int l);
void searchDepDicotomic(table t, char* dep, int l);

int main(int argc, const char * argv[]) {
    char *instructions[] = {"Uscita", "Stampa", "Ordina per data", "Ordina per codice", "Ordina per stazione di partenza", "Ordina per stazione di arrivo", "Ricerca per stazione di partenza"}, fn[MAXS], dep[MAXS];
    int go = 1, sel;
    table tab;
    
    tab = readLog();
    
    do {
        printInstructions(instructions, &sel);
        switch(sel) {
            case 0:
                go = 0;
                break;
            case 1:
                printf("Inserire nome file output ('t' per stampare su terminale):\n");
                scanf("%s", fn);
                for(int i = 0; i < tab.n; i++) {
                printLine(tab.lines[i], fn);
                }
                break;
            case 2:
                sort(&tab, DATE);
                printf("Elenco ordinato per data\n");
                for(int i = 0; i < tab.n; i++) {
                printLine(tab.lines[i], NULL);
                }
                break;
            case 3:
                sort(&tab, COD);
                printf("Elenco ordinato per codice\n");
                for(int i = 0; i < tab.n; i++) {
                printLine(tab.lines[i], NULL);
                }
                break;
            case 4:
                sort(&tab, DEPARTURE);
                printf("Elenco ordinato per stazione di partenza\n");
                for(int i = 0; i < tab.n; i++) {
                printLine(tab.lines[i], NULL);
                }
                break;
            case 5:
                sort(&tab, ARRIVAL);
                printf("Elenco ordinato per stazione di arrivo\n");
                for(int i = 0; i < tab.n; i++) {
                printLine(tab.lines[i], NULL);
                }
                break;
            case 6:
                printf("Inserire stazione di partenza:\n");
                scanf("%s", dep);
                if(tab.k == DEPARTURE)
                    searchDepDicotomic(tab, dep,(int) strlen(dep));
                else searchDepLinear(tab, dep,(int) strlen(dep));
                break;
      default:
                printf("Scelta non valida\n");
        }
    } while(go);
    return 0;
}

table readLog() {
    table t;
    char tmp_date[11], tmp_t1[9], tmp_t2[9];
    FILE *fIN = fopen("log.txt", "r");
    
    fscanf(fIN, "%d", &t.n);
    for (int i = 0; i < t.n; i++) {
        fscanf(fIN, "%s %s %s %s %s %s %d", t.lines[i].cod, t.lines[i].dep, t.lines[i].arr, tmp_date, tmp_t1, tmp_t2, &t.lines[i].delay);
        sscanf(tmp_date, "%d/%d/%d", &t.lines[i].date.y, &t.lines[i].date.m, &t.lines[i].date.d);
        sscanf(tmp_t1, "%d:%d:%d", &t.lines[i].dep_t.h, &t.lines[i].dep_t.m, &t.lines[i].dep_t.s);
        sscanf(tmp_t2, "%d:%d:%d", &t.lines[i].arr_t.h, &t.lines[i].arr_t.m, &t.lines[i].arr_t.s);
    }
    fclose(fIN);
    return t;
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

void sort(table *t, orderKey k) {
    line tmp;
    for(int i = (t->n)-1; i > 0; i--) {
        for (int j = 0; j < i; j++ ) {
            if(compareLines(t->lines[j], t->lines[j+1], k) > 0) {
                tmp = t->lines[j];
                t->lines[j] = t->lines[j+1];
                t->lines[j+1] = tmp;
            }
        }
    }
    t->k = k;
}

int compareLines(line l1, line l2, orderKey k) {
    int cmp = 0;
    switch (k) {
        case DATE:
            cmp = compareDate(l1.date, l2.date);
            if (cmp == 0) return compareTime(l1.dep_t, l2.dep_t);
            return cmp;
            break;
        case COD:
            return strcmp(l1.cod, l2.cod);
            break;
        case DEPARTURE:
            return strcmp(l1.dep, l2.dep);
            break;
        case ARRIVAL:
            return strcmp(l1.arr, l2.arr);
            break;
        default:
            break;
    }
    return cmp;
}

void searchDepLinear(table t, char* dep, int l) {
    int found = 0;
    for(int i = 0; i < t.n; i++) {
        if(!strncmp(t.lines[i].dep, dep, l)) {
            printLine(t.lines[i], NULL);
            found = 1;
        }
    }
    if (!found)
        printf("Stazione di partenza non trovata\n");
}

void searchDepDicotomic(table t, char* dep, int l) {
    int left = 0, right = t.n-1, a, cmp, found = 0;
    while (left <= right && !found) {
        a = (left + right)/2;
        cmp = strncmp(t.lines[a].dep, dep, l);
        if (cmp == 0) {
            found = 1;
            do {
                printLine(t.lines[a], NULL);
                a++;
            } while (!strncmp(t.lines[a].dep, dep, l));
        }
        else if(cmp < 0)
            left = a + 1;
        else right = a - 1;
    }
    if (!found)
        printf("Stazione di partenza non trovata\n");
}
