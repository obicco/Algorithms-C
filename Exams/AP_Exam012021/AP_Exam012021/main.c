//
//  main.c
//  AP_Exam012021
//
//  Created by Oskar Bich on 16/1/22.
//

#include <stdio.h>
#include <stdlib.h>

#define R 3
#define C 4
#define N 6

typedef struct list *link;

struct list {
    int n;
    link next;
} list_t;

int **initMat(void);
link initList(void);
link addNode(int n, link next);
void printM(int **m);
void change(int **m, int r, int c);
void f(link list, int *v, int n);
void printL(link list);

int main(int argc, const char * argv[]) {
    int **m = initMat();
    link list = initList();
    int v[R] = {1, 2, 3};
    printf("Matrice iniziale:\n");
    printM(m);
    printf("\nMatrice finale:\n");
    change(m, R, C);
    printf("\nLista iniziale:\n");
    printL(list);
    f(list, v, R);
    return 0;
}

int **initMat(void) {
    int **m = malloc(R*sizeof(*m));
    int mat[R][C] = {1, 1, 3, 0, 2, 4, 6, 8, 1, 2, 1, 1};
    for (int i = 0; i < R; i++) {
        m[i] = malloc(C*sizeof(**m));
        for (int j = 0; j < C; j++) m[i][j] = mat[i][j];
    }
    return m;
}

link initList(void) {
    link x = addNode(3, addNode(10, addNode(6, addNode(3, addNode(1, addNode(4, NULL))))));
    return x;
}

link addNode(int n, link next) {
    link x = malloc(sizeof(list_t));
    x->n = n;
    x->next = next;
    return x;
}

void printL(link list) {
    for (link x = list; x != NULL; x = x->next) {
        printf("%d ", x->n);
    }
    printf("\n");
}

void f(link list, int *v, int n) {
    link curr = list, prev = NULL;
    int match;
    while (curr != NULL) {
        match = 0;
        for (int i = 0; i < n; i++) {
            if (v[i] == curr->n) {
                match = 1;
                break;
            }
        }
        if (!match) {
            if (prev == NULL) {
                list = curr->next;
                free(curr);
                curr = list;
            } else {
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
            }
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    printf("\nLista finale:\n");
    printL(list);
}

void printM(int **m) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void change(int **m, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (m[i][j] != 3 && m[i][j]%3 == 0 ) {
                for (int k = 0; k < r; k++) m[k][j] = 3;
                for (int k = 0; k < c; k++) m[i][k] = 3;
                break;
            } else continue;
        }
    }
    printM(m);
}
