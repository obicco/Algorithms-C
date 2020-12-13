//
//  main.c
//  Lab02es4
//
//  Created by Oskar Bich on 08/11/2020.
//

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define MAXN 100
#define filein "sort.txt"

void selectionSort(int A[], int N) {
    int l = 0, r = N-1, min, tmp;
    int cnti = 0, cntj = 0, cntswap = 0;
    
    for(int i = l; i < r; i++) {
        cnti++;
        min = i;
        for(int j = i+1; j <= r; j++) {
            cntj++;
            if (A[j] < A[min])
                min = j;
        }
        if (min != i) {
            tmp = A[min];
            A[min] = A[i];
            A[i] = tmp;
            cntswap++;
        }
    }
    printf("Outer = %d, Inner = %d, Swap = %d\n", cnti, cntj, cntswap);
}

void insertionSort(int A[], int N) {
    int j, l = 0, r = N-1, x;
    int cnti = 0, cntj = 0, cntswap = 0;
    
    for (int i = l+1; i <= r; i++) {
        cnti++;
        x = A[i];
        j = i-1;
        while (j >= l && x < A[j]) {
            cntj++;
            A[j+1] = A[j];
            cntswap++;
            j--;
        }
        A[j+1] = x;
    }
    printf("Outer loop = %d, Inner loop = %d, Assignments = %d\n", cnti, cntj, cntswap);
}

void shellSort(int A[], int N) {
    int j, h = 1, l = 0, r = N-1, tmp;
    int cntot = 0, cnti = 0, cntj = 0, cntswap = 0;
    
    while (h < N/3)
        h = 3*h + 1;
    
    while (h >= 1) {
        for (int i = l + h; i <= r; i++) {
            cnti++;
            tmp = A[i];
            j = i;
            while (j >= l+h & tmp < A[j-h]) {
                A[j] = A[j-h];
                j -= h;
                cntj++;
                cntswap++;
            }
            A[j] = tmp;
        }
        printf("Outer for loop for h ) %d: %d\n", h, cnti);
        h = h/3;
        cntot += cnti;
        cnti = 0;
    }
    printf("Outer for loop = %d, Inner loop = %d, Assignments = %d\n", cntot, cntj, cntswap);
}

void printArray(int A[], int N) {
    for(int i = 0; i < N; i ++) {
        printf("%d", A[i]);
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    int A[MAXN] = {0}, s, N;
    
//  InsertionSort
    FILE *fp = fopen(filein, "r");
    fscanf(fp, "%d", &s);
    printf("InsertionSort\n");
    for(int i = 0; i < s; i++) {
        fscanf(fp, "%d", &N);
        for (int j = 0; j < N; j++) {
            fscanf(fp, "%d", &A[j]);
        }
        insertionSort(A, N);
    }
    fclose(fp);
    printf("\n");
    
//  SelectionSort
    fp = fopen(filein, "r");
    fscanf(fp, "%d", &s);
    printf("SelectionSort\n");
    for(int i = 0; i < s; i++) {
        fscanf(fp, "%d", &N);
        for (int j = 0; j < N; j++) {
            fscanf(fp, "%d", &A[j]);
        }
        selectionSort(A, N);
    }
    fclose(fp);
    printf("\n");
    
//  ShellSort
        fp = fopen(filein, "r");
        fscanf(fp, "%d", &s);
        printf("ShellSort\n");
        for(int i = 0; i < s; i++) {
            fscanf(fp, "%d", &N);
            for(int j = 0; j < N; j++) {
                fscanf(fp, "%d", &A[j]);
            }
            shellSort(A, N);
        }
        fclose(fp);
        printf("\n");
    
    return 0;
}
