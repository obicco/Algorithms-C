//
//  main.c
//  AP_Exam022018
//
//  Created by Oskar Bich on 21/1/22.
//

#include <stdio.h>
#include <stdlib.h>
#define R 2
#define C 3

typedef struct node *link;

struct node {
    int n;
    link l, r;
};

int **loadM(int r, int c);
void printM(int **m, int r, int c);
void displaySquare (int **A, int n, int m);

link addNode(int n, link l, link r);
link loadT1(void);
link loadT2(void);
void printL(link l);
int subTree(link root1, link root2);
void subTreeR(link root1, link root2, int *f, int *cnt);
void check(link root1, link root2, int *f);

int main(int argc, const char * argv[]) {
    link t1 = loadT1(), t2 = loadT2();
    int **m = loadM(R, C);
    printM(m, R, C);
    displaySquare(m, R, C);
  
    printf("2.\tBST T1 di partenza (in-order view):\t");
    printL(t1);
    printf("\n\tBST T2 di partenza (in-order view):\t");
    printL(t2);
    if (subTree(t1, t2))
        printf("\n\tIl BST T2 e' sotto-albero del BST T1.\n");
    else printf("\n\tIl BST T2 non e' sotto-albero del BST T1.\n");
    return 0;
}

int **loadM(int r, int c) {
    int v[6] = {1, 2, 3, 4, 5, 6};
    int **m = malloc(r*sizeof(*m));
    for (int i = 0, k = 0; i < r; i++) {
        m[i] = malloc(c*sizeof(**m));
        for (int j = 0; j < c; j++, k++) {
            m[i][j] = v[k];
        }
    }
    return m;
}

void printM(int **m, int r, int c) {
    printf("1.\tMatrice di partenza:\n");
    for (int i = 0; i < r; i++) {
        printf("\t");
        for (int j = 0; j < c; j++) printf("%d ", m[i][j]);
        printf("\n");
    }
}

void displaySquare (int **A, int n, int m) {
    int dim, k = 1;
    if (n > m)
        dim = m;
    else dim = n;
    while (k <= dim) {
        printf("\tMatrice quadrata di dimensione %d:\n", k);
        for(int x = 0; x <= n-k ; x++)
            for(int y = 0; y <= m - k; y++ )
            {
                for(int i = 0 + x; i < k + x; i++)
                {
                    printf("\t");
                    for(int j = 0 + y; j < k + y ;j++)
                    {
                        printf("%d", A[i][j]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
        k++;
    }
}

link addNode(int n, link l, link r) {
    link x = malloc(sizeof(*x));
    x->n = n;
    x->l = l;
    x->r = r;
    return x;
}

link loadT1(void) {
    link x = addNode(3, addNode(7, addNode(2, NULL, NULL), addNode(2, addNode(9, NULL, NULL), NULL)), addNode(1, NULL, addNode(0, NULL, NULL)));
    return x;
}

link loadT2(void) {
    link x = addNode(7, addNode(2, NULL, NULL), addNode(2, addNode(9, NULL, NULL), NULL));
    return x;
}

void printL(link l) {
    if (l == NULL)
        return;
    printL(l->l);
    printf("%d ", l->n);
    printL(l->r);
}

int subTree(link root1, link root2) {
    int found = 0, cnt = 0;
    subTreeR(root1, root2, &found, &cnt);
    return cnt;
    
}

void subTreeR(link root1, link root2, int *f, int *cnt) {
    if (root1 == NULL)
        return;
    if (root1->n == root2->n) {
        check(root1, root2, f);
        if (*f)
            *cnt = 1;
        return;
    }
    else {
        subTreeR(root1->l, root2, f, cnt);
        subTreeR(root1->r, root2, f, cnt);
    }
}

void check(link root1, link root2, int *f) {
    if (root1 == NULL && root2 == NULL)
        return;
    if (root1->n == root2->n) {
        *f = 1;
        check(root1->l, root2->l, f);
        check(root1->r, root2->r, f);
    } else {
        *f = 0;
        return;
    }
}
