//
//  main.c
//  Exams
//
//  Created by Oskar Bich on 26/01/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct persona {
    char *nome;
    char *cognome;
} Persona;

typedef struct listNode *link;

struct listNode {
    Persona p;
    link next;
};

typedef struct l_t {
    link head;
} lista_t;

//Es1 appello 06.02.2014
int *merge3(int *a, int *b, int *c, int na, int nb, int nc) {
    int *v, tot = na + nb + nc, i = 0, j = 0, k = 0;
    
    v = malloc(tot * sizeof(int));
    for (int l = 0; l < tot; l++) {
        if (i > na && j > nb)
            v[l] = c[k++];
        else if (i > na && k > nc)
            v[l] = b[j++];
        else if (k > nc && j > nb)
            v[l] = a[i++];
        else if (a[i] <= b[j] && a[i] <= c[k])
            v[l] = a[i++];
        else if (b[j] <= a[i] && b[j] <= c[k])
            v[l] = b[j++];
        else
            v[l] = c[k++];
    }
    return v;
}

//Es2 appello 06.02.2014
int inserisciInOrdine (lista_t *lista, char *cognome, char *nome) {
    link prev = NULL, curr = lista->head, new = malloc(sizeof(*new));
    new->p.cognome = strdup(cognome);
    new->p.nome = strdup(nome);
    new->next = NULL;
    
    while ((curr != NULL && strcmp(curr->p.cognome, cognome) < 0) || (strcmp(curr->p.cognome, cognome) == 0 && strcmp(curr->p.nome, nome) <= 0)) {
        prev = curr;
        curr = curr->next;
    }
    
    if (strcmp(curr->p.cognome, cognome) == 0 && strcmp(curr->p.nome, nome) == 0) {
        printf("Elemento gia' presente\n");
        free(new->p.cognome);
        free(new->p.nome);
        free(new);
        return 0;
    }
    if (prev == NULL) {
        new->next = curr;
        lista->head = new;
        return 1;
    } else {
        prev->next = new;
        if (curr != NULL)
            new->next = curr;
        return 1;
    }
}

//Es3 appello 06.02.2014
int checkSol(int *min_diff, int *sol, int *v, int n, int *opt_sol) {
    int tot = 0, max = 0, min = 0;
    
    for (int i = 0; i < n; i++) {
        tot += sol[i];
        if (tot > max)
            max = tot;
        if (tot < min)
            min = tot;
    }
    if (max - min < *min_diff) {
        *min_diff = max - min;
        return 1;
    }
    return 0;
}

void balance(int *v, int *mark, int *sol, int pos, int n, int *min_diff, int *opt_sol) {
    if (pos >= n) {
        if (checkSol(min_diff, sol, v, n, opt_sol)) {
            for (int i = 0; i < n; i++)
                opt_sol[i] = sol[i];
            return;
        }
    }
    
    for (int j = 0; j < n; j++) {
        if (mark[j] == 0) {
            mark[j] = 1;
            sol[pos] = v[j];
            balance(v, mark, sol, pos+1, n, min_diff, opt_sol);
            mark[j] = 0;
        }
    }
    return;
}

//Es1 appello 24.02.2014
void rotate(int *v, int n, int d) {
    int tmp[n];
    for (int i = 0; i < n-d; i++) {
        tmp[d+i] = v[i];
        printf("\nElemento %d: %d", i+d, tmp[d+i]);
    }
    for (int i = 0; i < d; i++) {
        tmp[i] = v[n-d+i];
        printf("\nElemento %d: %d", i, tmp[i]);
    }
    for (int i = 0; i < n; i++)
        v[i] = tmp[i];
}

//Es1 appello 23.02.2015
void invertSequence (int *v1, int n, int *v2) {
    int i = 0, cnt = 0, tmp;
    while (i != n) {
        if (v1[i] < v1[i+1])
            cnt++;
        else {
            v2[i-cnt] = cnt;
            cnt = 0;
        }
        i++;
    }
    for (i = 0; i < n; i++) {
        tmp = v2[i];
        for (int j = tmp; j >= 0; j--) v2[i+tmp-j] = v1[i+j];
        i += tmp;
    }
}

//Es1 appello 22.02.2016
int areaTot(FILE *fp) {
    int M[100][100] = {0};
    int x1, y1, x2, y2;
    int area = 0;
    while (fscanf(fp, "%d%d%d%d", &x1, &y1, &x2, &y2) == 4) {
        for (int i = x1; i < x2; i++) {
            for (int j = y1; j < y2; j++) {
                M[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            area += M[i][j];
        }
    }
    return area;
}

int main() {
    int v[10] = {1,2,3,4,5,0,12,13,14,2}, n = 10, d = 3;
    int v2[10] = {0};
    FILE *fp = fopen("mat.txt", "r");
    int area = areaTot(fp);
    printf("Area totale %d\n\n", area);
    printf("Vettore originale: ");
    for (int i = 0; i < n; i++)
    printf("%d ", v[i]);
    invertSequence(v, n, v2);
    printf("\nVettore invertito: ");
    for (int i = 0; i < n; i++)
    printf("%d ", v2[i]);
    printf("\n");
}
