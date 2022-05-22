//
//  main.c
//  AP_Exam012019
//
//  Created by Oskar Bich on 29/5/21.
//

#include <stdio.h>
#include <stdlib.h>
#define N 4
#define M 3

typedef struct node *link;

struct node {
    int val;
    link next;
};

int minmaxdiff(int **A, int n, int m);
link createEx(int num);
void printList(link head);
link newnode(void);
void splice (link L1, link L2, int start, int num);


int main(int argc, const char * argv[]) {
    int **A = malloc(N*sizeof(int *));
    int m[N][M] = {
        {15, 13, 7},
        {6, 18, 4},
        {11, 4, 12},
        {13, 9, 5}
    };
    link L1 = createEx(1);
    link L2 = createEx(2);
    
    printf("%d\n", L1[1].val);
    
    printf("Lista iniziale L1:\n");
    printList(L1);
    printf("\nLista iniziale L2:\n");
    printList(L2);
    
    splice(L1, L2, 1, 2);
    
    printf("\nLista finale L1:\n");
    printList(L1);
    printf("\nLista finale L2:\n");
    printList(L2);
    printf("\n");
    
    for (int i = 0; i < N; i++) {
            A[i] = malloc(M*sizeof(int));
            for (int j = 0; j < M; j++) {
                A[i][j] = m[i][j];
            }
        }
    
    printf("Indice risultante: %d\n", minmaxdiff(A, M, N));
    
    return 0;
}

int minmaxdiff(int **A, int n, int m) {
    int jMax = -1, diff, diffMax = 0;
    
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n-1; i++) {
            diff = abs(A[i][j] - A[i+1][j]);
            if (diff > diffMax) {
                diffMax = diff;
                jMax = j;
            }
            
        }
    }
    printf("Differenza massima: %d\n", diffMax);
    return jMax;
}

link newnode(void) {
    link x = malloc(sizeof(*x));
    x->val = -1;
    x->next = NULL;
    return x;
}

void printList(link head) {
    link curr = head, prev = NULL;
    while (curr != NULL) {
        printf("%d ", curr->val);
        prev = curr;
        curr = curr->next;
    }
}

link createEx(int num) {
    link head = newnode();
    switch (num) {
        case 1:
            head->val = 1;
            head->next = newnode();
            head->next->val = 3;
            head->next->next = newnode();
            head->next->next->val = 5;
            head->next->next->next = newnode();
            head->next->next->next->val = 7;
            break;
        case 2:
            head->val = 7;
            head->next = newnode();
            head->next->val = 4;
            head->next->next = newnode();
            head->next->next->val = 9;
    }
    return head;
}

void splice (link L1, link L2, int start, int num) {
    link curr1 = L1[start].next, curr2= L2, nextmp;
    for (int i = 0; i < num; i++) {
        nextmp = curr1->next;
        curr1->next = curr2;
        curr2 = curr2->next;
        curr1->next = nextmp;
        curr1 = curr1->next;
    }
    L2 = curr2;
}

