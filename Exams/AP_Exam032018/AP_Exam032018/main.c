//
//  main.c
//  AP_Exam032018
//
//  Created by Oskar Bich on 2/6/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 16

typedef struct node *link;

struct node {
    int val;
    link sx, dx;
};

void printVoc (char *str, int n);
int diameter (link root);
link newnode(int val, link sx, link dx);
void printBST(link root, int level);
void diameterR(link root, int cnt, int level,int *max);

int maxsub(int *X, int n);
void powerset(int pos, int *val, int *sol, int k,int *lun);
int check(int *sol,int *val, int k,int *ok);

int main(int argc, const char * argv[]) {
    int X[N] = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
    int k = maxsub(X, N);
    printf("%d\n", k);
    char S[11] = "forExample";
    int n = 4;
    
    link root = newnode(1, newnode(2, newnode(4, newnode(6, NULL, NULL), newnode(7, NULL, NULL)), NULL), newnode(3, NULL, newnode(5, NULL, NULL)));
    
    printBST(root, n);
    
    printf("Diametro maggiore: %d\n", diameter(root));
    
    printVoc(S, n);
    
    return 0;
}

void printVoc (char *str, int n) {
    int l = (int) strlen(str), end = 0, cnt;
    
    while (!end) {
        cnt = 0;
        for (int i = 0; i < n; i++) {
            if (toupper(str[i])=='A' || toupper(str[i])=='E' || toupper(str[i])=='I' || toupper(str[i])=='O' || toupper(str[i])=='U')
                cnt++;
            if (str[i] == '\0')
                end = 1;
        }
        if (cnt == 2) {
            for (int i = 0; i < n; i++) printf("%c ", str[i]);
            printf("\n");
        }
        str++;
    }
    str = str-l+n;
}

link newnode(int val, link sx, link dx) {
    link x = malloc(sizeof(*x));
    x->val = val;
    x->dx = dx;
    x->sx = sx;
    return x;
}

void printBST(link root, int level) {
    if (root == NULL)
        return;
    for (int i = 0; i < level; i++) printf(i == level - 1 ? "| " : "  ");
    printf("%d\n", root->val);
    printBST(root->sx, level + 1);
    printBST(root->dx, level + 1);
}

int diameter (link root) {
    int sum = 0, max = 0;
    diameterR(root->sx, 1, N, &max);
    printf(" sx: %d\n", max);
    sum = max;
    max = 0;
    diameterR(root->dx, 1, N, &max);
    printf(" dx: %d\n", max);
    sum += max;
    return sum;
}

void diameterR(link root, int cnt, int level, int *max) {
    if (root == NULL)
        return;
    if (root->sx == NULL && root->dx == NULL) {
        if (cnt > *max)
            *max = cnt;
    }
    diameterR(root->sx, cnt+1, N, max);
    diameterR(root->dx, cnt+1, N, max);
}

int maxsub(int *X, int n) {
    int *sol = calloc(N, sizeof(int));
    int lun = 0;
    powerset(0, X, sol, N, &lun);
    return lun;
}

void powerset(int pos, int *val, int *sol, int k,int *lun) {
    int ok, z;
    if (pos >= k)
    {
        ok = 0;
        z= check(sol, val, k, &ok);
        if (ok != 0)
        {
            if (z > *lun)
            {
                *lun = z;
            }
        }
        return;
    }
    sol[pos] = 0;
    powerset(pos + 1, val, sol, k,lun);
    sol[pos] = 1;
    powerset(pos + 1, val, sol, k,lun);
}

int check(int *sol,int *val, int k,int *ok) {
    int *vet;
    int i,j = 0,count = 0;
    for (i = 0; i < k; i++)
    {
        if (sol[i] != 0)
            count++;
    }
    if (count == 0||count==1)
        return 0;
    *ok = 1;
    vet = malloc(count * sizeof(int));
    for (i = 0; i < k; i++)
    {
        if (sol[i] != 0)
        {
            vet[j++] = val[i];
        }
    }
    for (i = 1; i < count; i++)
    {
        if (vet[i] < vet[i - 1])
        {
            *ok = 0;
            break;
        }
    }
    if (*ok == 0)
        return 0;
    else
        return count;
}
