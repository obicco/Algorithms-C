//
//  main.c
//  Lab04es2
//
//  Created by Oskar Bich on 15/11/20.
//

#include <stdio.h>
#define MAXN 7

int majority( int *a, int N);
void show(int x[], int l, int r);
int majorityR(int *a, int n, int l, int r);
int count(int *a, int n, int res);

int main(int argc, const char * argv[]) {
    int v[MAXN] = {3, 3, 9, 4, 3, 5, 3}, maj;

    if ((maj = majority(v, MAXN)) != -1)
        printf("L'elemento maggioritario è %d\n", maj);
    else
        printf("L'elemento maggioritario non esiste\n");

    return 0;
}

// To-Do: Recursive function
int majority( int *a, int N) {
    int l = 0, r = N-1;
    int res = majorityR(a, N, l, r);
    if (res != -1)
        return res;
    else return -1;
}

int majorityR(int *a, int n, int l, int r) {
    int resLeft, resRight, resLeftCnt, resRightCnt;
    int m = (l+r)/2;
    if (l == r)
        return a[l];
    
    resLeft = majorityR(a, n, l, m);
    resRight = majorityR(a, n, m+1, r);
    
    if (resLeft == resRight)
        return resLeft;
    
    resLeftCnt = count(a, n, resLeft);
    resRightCnt = count(a, n, resRight);
    
    if (resLeftCnt > n/2)
        return resLeft;
    if (resRightCnt > n/2)
        return resRight;
    return -1;
}

int count(int *a, int n, int res) {
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (a[i] == res)
            cnt++;
    return cnt;
}
