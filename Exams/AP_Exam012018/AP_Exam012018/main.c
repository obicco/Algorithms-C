//
//  main.c
//  AP_Exam012018
//
//  Created by Oskar Bich on 28/12/21.
//

#include <stdio.h>
#include <stdlib.h>
#define N 10
#define M 6

typedef struct node *link;
typedef struct a {
    int si, fi;
}att;

struct node {
    int val;
    link next;
};

//ES 1
void Vsequence(int* v, int n);

//ES 2
link addNode(int val, link next);
int completeList(link head);
void printList(link head);

//ES 3
att *initAtt(void);
void printAtt(att *arr, int n);
void checkSol(int pos, int n, int *sol, int *p_max, int *final_sol, att *v);
void powerset(int pos, att *v, int *sol, int n, int *p_max, int *final_sol);
void intervSel(int n, att *v);

int main(int argc, const char * argv[]) {
    int v[N] = {1, 3, 4, 0, 1, 0, 9, 4, 2, 0}, n;
    link head = addNode(4, addNode(7, addNode(10, NULL)));
    att *arr = initAtt();
    
    Vsequence(v, N);
    
    printf("2.\tLista originale:\n");
    printList(head);
    printf("\tNumero di inserzioni in lista: %d\n\tLista completa:\n", n = completeList(head));
    printList(head);
    
    printf("3.\tSottoinsieme intervalli:\n");
    printAtt(arr, M);
    intervSel(M, arr);
    
    return 0;
}

void Vsequence(int* v, int n) {
    int cnt = 0, max = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] != 0)
            cnt++;
        else cnt = 0;
        if (cnt > max)
            max = cnt;
    }
    if (max == 0) {
        printf("Vettore nullo.\n");
        return;
    } else printf("1.\tSottovettori non nulli di dimensione massima:\n");
    for (int i = 0; i < n; i++) {
        if (v[i] != 0)
            cnt++;
        else if (cnt == max) {
            printf("\t");
            for (int j = i-max; j < i; j++) printf("%d ", v[j]);
            printf("\n");
            cnt = 0;
        }
        else cnt = 0;
    }
}

link addNode(int val, link next) {
    link x = malloc(sizeof(link*));
    x->val = val;
    x->next = next;
    return x;
}

int completeList(link head) {
    int cnt = 0;
    for (link x = head; x->next != NULL; x = x->next) {
        if (x->val+1 != x->next->val) {
            x->next = addNode(x->val+1, x->next);
            cnt++;
        }
    }
    return cnt;
}
void printList(link head) {
    printf("\t");
    for (link x = head; x != NULL; x = x->next) {
        printf("%d ", x->val);
    }
    printf("\n");
}

att *initAtt(void) {
    att* arr = malloc(M*sizeof(att*));
    int in[M] = {1, 2, 2, 3, 5, 6}, fi[M] = {2, 4, 5, 5, 7, 8};
    for(int i = 0; i < M; i++) {
        arr[i].si = in[i];
        arr[i].fi = fi[i];
    }
    return arr;
}

void printAtt(att *arr, int n) {
    for(int i = 0; i < n; i++) printf("\t(%d, %d)\n", arr[i].si, arr[i].fi);
}

void intervSel(int n, att *v) {
    int *final_sol = malloc(n*sizeof(int)), *sol = malloc(n*sizeof(int)), max = 0;
    powerset(0, v, sol, n, &max, final_sol);
    printf("\tSottoinsieme di intervalli compatibili con somma delle durate massimizzata:\n\t{");
    for (int i = 0; i < n; i++) if(final_sol[i] != 0) printf("(%d, %d)", v[i].si, v[i].fi);
    printf("}\n\n");
}

void powerset(int pos, att *v, int *sol, int n, int *p_max, int *final_sol) {
    if (pos == n) {
        checkSol(pos, n, sol, p_max, final_sol, v);
        return;
    }
    sol[pos] = 0;
    powerset(pos+1, v, sol, n, p_max, final_sol);
    sol[pos] = 1;
    powerset(pos+1, v, sol, n, p_max, final_sol);
    return;
}

void checkSol(int pos, int n, int *sol, int *p_max, int *final_sol, att *v) {
    int local_max = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (i != j && sol[j] != 0 && sol[i] != 0) {
                if ((v[i].si < v[j].fi) && (v[j].si < v[i].fi))
                    return;
            }
        }
    }
    
    for (int j = 0; j < n; j++) if (sol[j] != 0) local_max += v[j].fi - v[j].si;
    if(local_max > *p_max) {
        *p_max = local_max;
        for (int j = 0; j < n; j++) {
            final_sol[j] = sol[j];
        }
    }
}
