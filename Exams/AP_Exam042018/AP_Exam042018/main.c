//
//  main.c
//  AP_Exam042018
//
//  Created by Oskar Bich on 4/8/21.
//

#include <stdio.h>
#include <stdlib.h>
#define ROW 4
#define COL 3
#define N 3
#define TARGET 268
#define DIM 4

typedef struct list1 list1_t, *link1;
typedef struct list2 list2_t, *link2;

struct list1 {
    int n;
    link1 next;
};

struct list2 {
    int n, r;
    link2 next;
};

typedef struct elem {
    int cod, peso, qnt;
} paste;

void displayRanking( int **C, int n, int m);
link2 comprimi(link1 head);
list2_t *addList2(int n, int r, link2 next);
list1_t *addList1(int n, link1 next);
list1_t *list_init_example(void);
void print_list2(link2 head);
paste *initLab (int dim);
void printInv(paste *p, int dim);
void solve(paste *p, int dim, int target);
void loadV(int *val,int i,int pos, int qnt);
void solveR(int pos, paste *p, int *val, int *sol, int *bestsol, int *max, int target, int dim, int k);
int check (int *val, paste *p, int *sol, int dim, int k);

int main(int argc, const char * argv[]) {
    link1 list = list_init_example();
    link2 compressed_list = comprimi(list);
    paste *p = initLab(DIM);
    int M[ROW][COL] = {
        {3, 1, 0},
        {0, 1, 1},
        {1, 1, 1},
        {1, 1, 3}
    };
    
    int **m = malloc(ROW*sizeof(int*));
    for(int i = 0; i < ROW; i++) {
        m[i] = malloc(COL*sizeof(int));
        for (int j = 0; j < COL; j++) {
            m[i][j] = M[i][j];
        }
    }
    
    printf("1.\tCapolista per turno:\n");
    displayRanking(m, ROW, COL);
    printf("\n2.\tLista compressa:\n");
    
    print_list2(compressed_list);
    
    printInv(p, DIM);
    solve(p, DIM, TARGET);
    
    return 0;
}

void displayRanking( int **C, int n, int m) {
    int v[n], index = 0, max = 0;
    for (int i = 0; i < n; i++) v[i] = 0;
    
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            v[i] += C[i][j];
            if (v[i] > max) {
                max = v[i];
                index = i;
            }
        }
        printf("\tTurno %d capolista squadra %d con %d punti\n", j, index, max);
    }
}

link2 comprimi(link1 head) {
    link2 head2 = NULL, y = NULL;
    int cnt;
    
    for (link1 x = head; x != NULL; x = x->next) {
        cnt = 1;
        while (x->next != NULL && (x->n == x->next->n)) {
            cnt++;
            x = x->next;
        }
        if (head2 == NULL) {
            head2 = addList2(x->n, cnt, NULL);
            y = head2;
        } else {
            y->next = addList2(x->n, cnt, NULL);
            y = y->next;
        }
    }

    return head2;
}

list2_t *addList2(int n, int r, link2 next) {
    list2_t *x = malloc(sizeof(list2_t));
    x->n = n;
    x->r = r;
    x->next = next;
    return x;
}

list1_t *addList1(int n, link1 next) {
    list1_t *x = malloc(sizeof(list1_t));
    x->n = n;
    x->next = next;
    return x;
}

list1_t *list_init_example(void) {
    list1_t *x = NULL;
    
    x = addList1(3, addList1(3, addList1(3, addList1(3, addList1(2, addList1(2, addList1(3, addList1(5, addList1(5, addList1(5, NULL))))))))));
    
    return x;
}

void print_list2(link2 head) {
    printf("\t(");
    for(link2 x = head; x != NULL; x = x->next) {
        printf("(%d,%d)", x->n, x->r);
    }
    printf(")\n");
}

paste *initLab (int dim) {
    paste *p = malloc(dim*sizeof(*p));
    p[0].cod = 1; p[0].peso = 3; p[0].qnt = 6;
    p[1].cod = 2; p[1].peso = 17; p[1].qnt = 7;
    p[2].cod = 3; p[2].peso = 21; p[2].qnt = 5;
    p[3].cod = 4; p[3].peso = 33; p[3].qnt = 4;
    return p;
}

void printInv(paste *p, int dim) {
    printf("\nINVENTARIO LABORATORIO:\n");
    for (int i = 0; i < dim; i++) printf("\tCodice pasticcino %d dal peso di %dgr disponibile in %d qnt\n", p[i].cod, p[i].peso, p[i].qnt);
}

void solve(paste *p, int dim, int target) {
    int l = 0, max = 0;
    int *sol, *bestsol, *val;
    for (int i = 0; i < dim; i++) l += p[i].qnt;
    sol = malloc(l*sizeof(*sol));
    bestsol = malloc(l*sizeof(*bestsol));
    val = malloc(l*sizeof(*val));
    for (int i = 0, pos = 0; i < dim; i++, pos += p[i-1].qnt) loadV(val, i, pos, p[i].qnt);
    solveR(0, p, val, sol, bestsol, &max, target, dim, l);
    printf("\n3.\tIl vassoio e' composto da :\n");
    for (int i = 0; i < l; i++) {
        if (bestsol[i])
            printf("\tpasticcino %d dal peso di %dgr\n", p[val[i]].cod, p[val[i]].peso);
    }
    printf("\tper un peso complessivo di %dgr su %dgr\n", max, target);
}

void loadV(int *val,int i,int pos, int qnt) {
    for (int k = pos; k < pos+qnt; k++) val[k] = i;
}

void solveR(int pos, paste *p, int *val, int *sol, int *bestsol, int *max, int target, int dim, int k) {
    int maxloc = check(val, p, sol, dim, k);
    if (pos >= k) {
        if (maxloc > *max && maxloc <= target) {
            *max = maxloc;
            for (int i = 0; i < k; i++) bestsol[i] = sol[i];
        }
        return;
    }
    sol[pos] = 0;
    solveR(pos + 1, p, val, sol, bestsol, max, target, dim, k);
    sol[pos] = 1;
    solveR(pos + 1, p, val, sol, bestsol, max, target, dim, k);
}

int check (int *val, paste *p, int *sol, int dim, int k) {
    int maxloc = 0;
    for (int i = 0; i < k; i++) {
        if (sol[i]) {
            maxloc += p[val[i]].peso;
        }
    }
    return maxloc;
}
