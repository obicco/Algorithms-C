//
//  main.c
//  AP_Exam012017
//
//  Created by Oskar Bich on 23/11/21.
//

#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 3

typedef struct node *link;

struct node{
    int val;
    link r, l;
};

//ES 1
void sommaCornici (int **mat, int n, int **vet);
void printM (int **m, int n);
int **load(void);

//ES 2
link mirror(link root);
link createTree(void);
link createNode(int val, link l, link r);
void printTree(link root);
void printNode(link x);
link specularTree(link root);

//ES 3
int **loadM3(void);
void findbestSol(int** m, int n);
int check(int **m, int *selR, int *selC, int n);
void searchR(int pos, int **m, int *flagF, int n, int maxS, int selActual, int *selR, int *selC);

int main(int argc, const char * argv[]) {
    int **m = load();
    printM(m, N);
    printf("\n\n");
    int **M3 = loadM3();
    printM(M3, M);
    printf("\n\n");
    findbestSol(m, M);
    printf("\n\n");
    int *v = calloc(((N+1)/2),sizeof(int));
    link tree = createTree();
    printTree(tree);
    link sTree = specularTree(tree);
    printf("\n\n");
    printTree(sTree);
    printf("\n\n");
    sommaCornici(m, N, &v);
    for (int i = 0; i < ((N+1)/2); i++) printf("%d\n", v[i]);
//  printM(m);
    return 0;
}

int **load(void) {
    int v[N*N] = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,1,1,1,1};
    int **m = malloc(N*sizeof(int*));
    
    for (int i = 0, k = 0; i < N; i++) {
        m[i] = malloc(N*sizeof(**m));
        for (int j = 0; j < N; j++, k++) {
            m[i][j] = v[k];
        }
    }
    return m;
}

void printM(int **m, int n) {
    for(int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void sommaCornici(int **mat, int n, int **vet) {
    for (int k = 0; k < (n+1)/2; k++) {
        for(int i=k; i<n-k; i++) (*vet)[k] += mat[k][i];
        for(int i=k+1; i<n-k; i++) (*vet)[k] += mat[i][n-k-1];
        for(int i=n-k-2; i>=k; i--) (*vet)[k] += mat[n-k-1][i];
        for(int i=n-k-2; i>k; i--)  (*vet)[k] += mat[i][k];
    }
}

link createNode(int val, link l, link r) {
    link x = malloc(sizeof(*x));
    x->val = val;
    x->l = l;
    x->r = r;
    return x;
}

link createTree(void) {
    link x = createNode(15, createNode(6, createNode(3, createNode(2, NULL, NULL), createNode(4, NULL, NULL)), createNode(7, NULL, NULL)), createNode(18, createNode(17, NULL, NULL), createNode(20, NULL, NULL)));
    return x;
}

void printTree(link root) {
    if (root != NULL) {
        printTree(root->l);
        printNode(root);
        printTree(root->r);
    }
}

void printNode(link x) {
    printf("%d ", x->val);
}

link specularTree(link root) {
    link x = NULL;
    if (root != NULL) {
        x = createNode(root->val, specularTree(root->r), specularTree(root->l));
    }
    return x;
}

int **loadM3(void) {
    int v[M*M] = {0,1,0,1,0,1,0,1,0};
    int **m = malloc(M*sizeof(int*));
    for (int i = 0, k = 0; i < M; i++) {
        m[i] = malloc(M*sizeof(**m));
        for (int j = 0; j < M; j++, k++) {
            m[i][j] = v[k];
        }
    }
    return m;
}

void findbestSol(int** m, int n){
    int *switchR = calloc(n, sizeof(int));
    int *switchC = calloc(n, sizeof(int));
    int flagF = 0;
    for (int i = 0; i < n*n && !flagF; i++) searchR(0, m, &flagF, n, i, 0, switchR, switchC);
    if(!flagF) printf("Non e' stato possibile trovare una soluzione.\n");
    free(switchC);
    free(switchR);
    return;
}

void searchR(int pos, int **m, int *flagF, int n, int maxS, int selActual, int *selR, int *selC) {
    if (*flagF) return;
    if (pos > n || selActual == maxS) {
        if (check(m, selR, selC, n)) {
            *flagF = 1;
            printf("Trovata una soluzione.\n");
            printf("Righe: ");
            for (int i = 0; i < n; i++) {
                if (selR[i])
                    printf("%d ", i);
            }
            printf("Colonne: ");
            for (int i = 0; i < n; i++) {
                if (selC[i])
                    printf("%d ", i);
            }
        }
        return;
    }
    selR[pos] = 1; // 1 0
    searchR(pos+1, m, flagF, n, maxS, selActual+1, selR, selC);
    selC[pos] = 1; // 1 1
    searchR(pos+1, m, flagF, n, maxS, selActual+2, selR, selC);
    selR[pos] = 0; // 0 1
    searchR(pos+1, m, flagF, n, maxS, selActual+1, selR, selC);
    selC[pos] = 0; // 0 0
    searchR(pos+1, m, flagF, n, maxS, selActual, selR, selC);
}

int check(int **m, int *selR, int *selC, int n) {
    int **falseM = malloc(n*sizeof(int*));
    for (int i = 0; i < n; i++) {
        falseM[i] = malloc(n*sizeof(int));
        for (int j = 0; j < n; j++) falseM[i][j] = m[i][j];
    }
    
    for (int i = 0; i < n; i++) {
        if (selR[i]) for (int j = 0; j < n; j++) falseM[i][j] = !m[i][j];
    }
    for (int i = 0; i < n; i++) {
        if (selC[i]) for (int j = 0; j < n; j++) falseM[j][i] = !m[j][i];
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!falseM[i][j]) {
                for (i = 0; i < n; i++) free(falseM[i]);
                free(falseM);
                return 0;
            }
        }
    }
    for (int i = 0; i < n; i++) free(falseM[i]);
    free(falseM);
    return 1;
}
