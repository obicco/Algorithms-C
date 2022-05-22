//
//  main.c
//  AP_Exam012014
//
//  Created by Oskar Bich on 2/5/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define N 4

typedef struct persona {
    char *nome;
    char *cognome;
}Persona;

typedef struct listNode *link;

struct listNode {
    Persona p;
    link next;
};

typedef struct l_t{
    link head;
}lista_t;

void contoCorrente(int *vett, int *mark, int *sol, int pos, int n, int *diff_min, int *opt_sol);
int checkSol(int *diff_min, int *sol, int *vett, int n, int *opt_sol);
int inserisciInOrdine(lista_t *lista, char *cognome, char *nome);
void stampaLista(lista_t *lista);
int *merge3(int *a, int *b, int *c, int na, int nb, int nc);

int main(int argc, const char * argv[]) {
    int a[N] = {1, 4, 7, 9}, b[N] = {2, 5, 8, 30}, c[N] = {3, 6, 10, 20}, *v;
    int *vett, *opt_sol,*mark, *sol, n,diff_min = INT_MAX;
    char cognome[20];
    char nome[20];
    int result;
    lista_t *lista;

    lista = malloc(sizeof(*lista));
    lista->head = NULL;
    
    printf("inserisci n: ");
        scanf("%d", &n);
        vett = malloc(n*sizeof(int));
        mark = malloc(n*sizeof(int));
        sol = malloc(n*sizeof(int));
        opt_sol = malloc(n*sizeof(int));

        printf("\n");

        for(int i = 0; i < n; i++){
            printf("inserisci vett[%d]: ", i);
            scanf("%d", &vett[i]);
            mark[i] = 0;
        }
        printf("\n");

        contoCorrente(vett, mark, sol, 0, n, &diff_min, opt_sol);

        printf("\nsoluzione: \n");
        for(int i = 0; i < n; i++){
            printf("%d ", opt_sol[i]);
        }

    for(int i = 0; i < 5; i++){
        printf("Inserisci cognome: ");
        scanf("%s", cognome);
        printf("Inserisci nome: ");
        scanf("%s", nome);

        result = inserisciInOrdine(lista, cognome, nome);
        printf("%d\n", result);

    }

    stampaLista(lista);
    
    v = merge3(a, b, c, N, N, N);
    for (int i = 0;i < (3*N); i++)
        printf("%d ", v[i]);
    printf("\n");
    return 0;
}

int *merge3(int *a, int *b, int *c, int na, int nb, int nc) {
    int n = na+nb+nc, i = 0, j = 0, k = 0;
    int *v = malloc(n*sizeof(int));
    for(int l = 0; l < n; l++){
            if(i >= na && j >= nb)
                v[l]=c[k++];
            else if(i >= na && k >= nc)
                v[l]=b[j++];
            else if(k >= nc && j >= nb)
                v[l]=a[i++];
            else if(a[i] <= b[j] && a[i] <= c[k] && i < na)
                v[l]=a[i++];
            else if(b[j] <= c[k] && b[j] <= a[i] && j < nb)
                v[l]=b[j++];
            else
                v[l]=c[k++];
        }
    return v;
}

int inserisciInOrdine(lista_t *lista, char *cognome, char *nome){
    link x,t,p;
    x=malloc(sizeof(*x));

    x->p.cognome = strdup(cognome);
    x->p.nome = strdup(nome);
    x->next = NULL;

    t = lista->head;
    p = t;

    while(t != NULL && (strcmp(t->p.cognome,cognome) < 0 || (strcmp(t->p.cognome,cognome) == 0 && strcmp(t->p.nome,nome) < 0))){
        p = t;
        t = t->next;
    }

    if(t == lista->head){
        printf("t = head");
        x->next = lista->head;
        lista->head = x;
        return 1;
    }

    printf("else");

    p->next = x;
    if(t != NULL)
        x->next = t;

    return 1;
}

void stampaLista(lista_t *lista){
    link t;

    for(t=lista->head; t != NULL; t = t->next){
        printf("%s %s \n", t->p.cognome, t->p.nome);
    }
    return;
}

void contoCorrente(int *vett, int *mark, int *sol, int pos, int n, int *diff_min, int *opt_sol){
    int i,j;

    if(pos>=n){
       if(checkSol(diff_min, sol, vett,n,opt_sol)){
            for(i = 0; i < n; i++){
                opt_sol[i]=sol[i];
            }
            printf("\n");
            return;
       }
    }

    for(j = 0; j < n; j++){
        if(mark[j]==0){
            mark[j] = 1;
            sol[pos] = vett[j];
            contoCorrente(vett,mark,sol,pos+1,n,diff_min,opt_sol);
            mark[j]=0;
        }
    }

    return;
}

int checkSol(int *diff_min, int *sol, int *vett, int n, int *opt_sol){
    int saldo_corrente = 0, saldo_corrente_max = 0, saldo_corrente_min = INT_MAX, i;

    for(i = 0; i < n; i++){
        saldo_corrente += sol[i];
        if(saldo_corrente >= saldo_corrente_max)
            saldo_corrente_max = saldo_corrente;
        if(saldo_corrente <= saldo_corrente_min)
            saldo_corrente_min = saldo_corrente;
    }

    if(saldo_corrente_max - saldo_corrente_min < *diff_min ){
        for(i = 0; i < n; i++)
            printf("%d ", sol[i]);
        printf("\nsaldo corrente min: %d", saldo_corrente_min);
        printf("\nsaldo corrente max: %d", saldo_corrente_max);
        printf("\ndifferenza: %d", saldo_corrente_max - abs(saldo_corrente_min));
        *diff_min = saldo_corrente_max - abs(saldo_corrente_min);
        return 1;
    }

    return 0;
}
