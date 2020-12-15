//
//  main.c
//  Lab08es1
//
//  Created by Oskar Bich on 07/12/20.
// very_very_easy_test_set.txt very_easy_test_set.txt easy_test_set.txt hard_test_set.txt
// easy_test_set_result.txt hard_test_set_result.txt

#include <stdio.h>
#include <stdlib.h>

#define N 4
#define FNAME "hard_test_set.txt"

int disp_rip(int pos, int *dispgem, int *sol, int n, int k, int prev);

int main(int argc, const char * argv[]) {
    int n, gem_num[N], dispgem[N], *sol, l, res, min, max, k;
    char gem[N] = {'Z', 'R', 'T', 'S'};
    char *names[N] = {"Zaffiro", "Rubino", "Topazio", "Smeraldo"};
    FILE *fp = fopen(FNAME, "r");
    if (fp == NULL)
        return -1;

    fscanf(fp, "%d", &n);
    for(int i = 0; i < n; i++) {
        l = 0;
        min = 0;
        res = 0;
        printf("TEST #%d\n", i+1);
        for (int j = 0; j < N; j++) {
            fscanf(fp, "%d", &gem_num[j]);
            printf("%s = %d, ", names[j], gem_num[j]);
            l += gem_num[j];
        }
        printf("TOT = %d \n", l);
        sol = malloc(l * sizeof(int));
        max = l;
        
        while (min <= max) {
            k = min + (max-min)/2;
            for(int i = 0; i < N; i++)
                dispgem[i] = gem_num[i];
            if (disp_rip(0, dispgem, sol, N, k, -1)) {
                res = k;
                min = k+1;
            } else max = k-1;
        }
        printf("Collana massima di lunghezza = %d\nPossibile soluzione: ", res);
        for( int i = 0; i < res; i++) {
            printf("%c", gem[sol[i]]);
        }
        printf("\n");
        free(sol);
    }
    fclose(fp);
    return 0;
}

int disp_rip(int pos, int *dispgem, int *sol, int n, int k, int prev) {
    if (pos >= k)
        return 1;
    for (int i = 0; i < n; i++) {
        if (dispgem[i] > 0) {
            if (prev != -1) {
                if (((sol[prev] == 0) || (sol[prev] == 2)) && (i != 0) && (i != 1))
                    continue;;
                if (((sol[prev] == 1) || (sol[prev] == 3)) && (i != 2) && (i != 3))
                    continue;
            }
            dispgem[i]--;
            sol[pos] = i;
            if (disp_rip(pos+1, dispgem, sol, n, k, pos))
                return 1;
            dispgem[i]++;
        }
    }
    return 0;
}
