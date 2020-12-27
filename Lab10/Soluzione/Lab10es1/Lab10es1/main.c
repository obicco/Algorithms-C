//
//  main.c
//  Lab10es1
//
//  Created by Oskar Bich on 27/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#define F_IN "att2.txt"

typedef struct {
    int s;
    int f;
} att;

att *readFile(char *fname, int *n);
void attSelDP (int N, att *v);
void Merge (att *A, att *B, int l, int q, int r);
void MergeSortR (att *A, att *B, int l, int r);
void MergeSort (att *A, int N);
int simpleCheck (int N, att *v, int i, int j);
int max (int A, int B);
void displaySol(int pos, att *v, int *opt, int *q);

int main(int argc, const char * argv[]) {
    int n;
    att *v = readFile(F_IN, &n);
    MergeSort(v, n);
    attSelDP(n, v);
    free(v);
    return 0;
}

att *readFile(char *fname, int *n) {
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
        exit(-1);
    fscanf(fp, "%d", n);
    att *v = calloc((*n+1), sizeof(att));
    for (int i = 1; i <= *n; i++)
        fscanf(fp, "%d%d", &v[i].s, &v[i].f);
    fclose(fp);
    return v;
}

int simpleCheck (int N, att *v, int i, int j) {
    if(v[i].s < v[j].f && v[j].s < v[i].f)
        return 1;
    return 0;
}

void attSelDP(int N, att *v) {
    int *opt = calloc((N+1), sizeof(int));
    int *q = calloc((N+1), sizeof(int));
    
    for (int i = 2; i <= N; i++) {
        for (int j = 1; j < i; j++) {
            if (!simpleCheck(N, v, i, j))
                q[i] = j;
        }
    }
    
    opt[0] = 0;
    for (int i = 1; i <= N; i++) {
        opt[i] = max((v[i].f - v[i].s) + opt[q[i]], opt[i-1]);
    }
    
    displaySol(N, v, opt, q);
    printf("\nlunghezza massima %d\n", opt[N]);
    return;
}
    
int max(int A, int B) {
  if (A > B)
    return A;
  return B;
}

void Merge(att *A, att *B, int l, int q, int r) {
  int i, j, k;
  i = l;
  j = q+1;
  for(k = l; k <= r; k++)
    if (i > q)
      B[k] = A[j++];
    else if (j > r)
      B[k] = A[i++];
    else if (A[i].f <= A[j].f)
      B[k] = A[i++];
    else
      B[k] = A[j++];
  for ( k = l; k <= r; k++ )
    A[k] = B[k];
  return;
}

void MergeSortR(att *A, att *B, int l, int r) {
  int q;
  if (r <= l)
    return;
  q = (l + r)/2;
  MergeSortR(A, B, l, q);
  MergeSortR(A, B, q+1, r);
  Merge(A, B, l, q, r);
}

void MergeSort(att *A, int N) {
  int l=1, r=N-1;
  att *B = (att *)malloc((N+1)*sizeof(att));
  if (B == NULL) {
    printf("Memory allocation error\n");
    exit(1);
  }
  MergeSortR(A, B, l, r);
}

void displaySol(int pos, att *v, int *opt, int *q){

  if (pos==0)
    return;

  if ((v[pos].f - v[pos].s)+opt[q[pos]] >= opt[pos-1]) {
    displaySol(q[pos], v, opt, q);
    printf("(%d %d) ", v[pos].s, v[pos].f);
  }
  else
    displaySol(pos-1, v, opt, q);

}
