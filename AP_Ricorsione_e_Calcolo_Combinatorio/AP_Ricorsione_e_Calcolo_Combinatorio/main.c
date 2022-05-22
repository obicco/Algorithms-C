//
//  main.c
//  AP_Ricorsione_e_Calcolo_Combinatorio
//
//  Created by Oskar Bich on 25/8/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 26
#define N 6
#define num_cifre 6

void stampa(void);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

//5.2.1 Menu ristorante - principio di moltiplicazione

typedef struct portata_ {
    int np;
    char *piatti;
} portata;

void stampa(void) {}

//vettore menu di ineru corrisponde al vettore sol
int generaMenuR(portata *p, int pos, int n, int *menu, int cnt) {
    if (pos >= n) {
        stampa();
        return cnt+1;
    }
    for (int i = 0; i < p[pos].np; i++) {
        menu[pos] = i;
        cnt = generaMenuR(p, pos+1, n, menu, cnt);
    }
    return cnt;
}

void generaMenu(portata *p, int n) {
    int *menu, cnt;
    menu = calloc(n, sizeof(int));
    if (menu == NULL)
        exit(-1);
    cnt = generaMenuR(p, 0, n, menu, 0);
    free(menu);
    printf("Ci sono %d possibili menu\n", cnt);
}

//5.2.2 Composizione di stringhe - disposizioni semplici

typedef struct stringSet_ {
    int n;
    char **stringhe;
} strSet;

int vocale(char c) {return 1;} //esempio

int check(char *curr_string, int len, int cm, int vm, int lm) {
    int v = 0, c = 0;
    if (len > lm)
        return 0;
    for (int i = 0; i < len; i++) {
        if (vocale(curr_string[i])) {
            v++;
            c = 0;
            if (v > vm)
                return 0;
        } else {
            c++;
            v = 0;
            if (c > cm)
                return 0;
        }
    }
    return 1;
}

void disp_sempl(strSet *ss, int pos, int *val, int *sol, int *mark, int n, int k, int cm, int vm, int lm) {
    int i, len;
    char *curr_string = calloc(n*LEN, sizeof(char));
    if(curr_string == NULL)
        exit(-1);
    
    if (pos >= k) {
        for (i = 0; i < k; i++) {
            strcat(curr_string, ss->stringhe[sol[i]]);
        }
        len = (int) strlen(curr_string);
        if (check(curr_string, len, cm, vm, lm))
            printf("%s\n", curr_string);
        free(curr_string);
        return;
    }
    for (i = 0; i < n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            disp_sempl(ss, pos+1, val, sol, mark, n, k, cm, cm, lm);
            mark[i] = 0;
        }
    }
    free(curr_string);
    return;
}

void gen (strSet *ss, int n, int k, int cm, int vm, int lm) {
    int i, *val, *sol, *mark;
    val = malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        val[i] = i;
    }
    sol = calloc(k, sizeof(int));
    mark = calloc(n, sizeof(int));
    
    disp_sempl(ss, 0, val, sol, mark, n, k, cm, vm, lm);
    
    free(val);
    free(sol);
    free(mark);
}

//5.2.3 Decomposizione di stringhe - disposizioni ripetute
void decomponiR (char *str, int lunghstr, int pos, int *lunghezze, int nstr, int *sol, int indsol) {
    int i, k = 0;
    if (pos == lunghstr) {
        printf("Decomposizione: ");
        for (i = 0; i < indsol; i++) {
            printf("%.*s ", lunghezze[sol[i]], str+k);
            k += lunghezze[sol[i]];
        }
        printf("\n");
        return;
    }
    for (i = 0; i < nstr; i++) {
        if (pos + lunghezze[i] <= lunghstr) //pruning{
            sol[indsol] = i;
        decomponiR(str, lunghstr, pos+lunghezze[i], lunghezze, nstr, sol, indsol+1);
    }
}

void decomponi(char *str, int nstr, int *lunghezze) {
    int lunghstr = (int) strlen(str);
    int *sol = calloc(lunghstr, sizeof(int));
    decomponiR(str, lunghstr, 0, lunghezze, nstr, sol, 0);
    free(sol);
}

//5.2.4 Addizioni ignote - permutazioni semplici

int check2(int numero_cifre, int *sol, char *n1, char *n2, char *n3) {
    int i, j, k = 0, ok = 0;
    int add1, add2, sum;
    char **nums = malloc(3*sizeof(char*));
    if (nums == NULL)
        return ok;
    nums[0] = strdup(n1);
    nums[1] = strdup(n2);
    nums[2] = strdup(n3);

    if (nums[0] == NULL || nums[1] == NULL || nums[2] == NULL)
        return ok;
    
    for (i = 0; i < 3 && k < N; i++) {
        for (j = 0; j < numero_cifre && k < N; j++) {
            if (nums[i][j] == '_')
                nums[i][j] = sol[k++]+'0';
        }
    }
    add1 = atoi(nums[0]);
    add2 = atoi(nums[1]);
    sum = atoi(nums[2]);
    
    free(nums[0]);
    free(nums[1]);
    free(nums[2]);
    free(nums);
    
    ok = ((add1 + add2) == sum);
    if (ok)
        printf("Una soluzione e': %d + %d = %d\n", add1, add2, sum);
    return ok;
}

int perm_sempl (int pos, int *val, int *sol, int *mark, int n, char *n1, char *n2,  char *n3) {
    if (pos >= N)
        return check2(num_cifre, sol, n1, n2, n3);
    
    for (int i = 0; i < N; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            if (perm_sempl(pos+1, val, sol, mark, num_cifre, n1, n2, n3) == 1)
                return 1;
            mark[i] = 0;
        }
    }
    return 0;
}

//5.2.5 Spellcasting - permutazioni con ripetizione
int check3 (char *sol) {
    if (sol[0] == 'R' || sol[1] == 'R' || sol[5] == 'R')
        return 0;
    return 1;
}

void perm_rip(int pos, char *dist_val, char *sol, int *mark, int n, int n_dist) {
    if (pos >= n) {
        if (check3(sol)) {
            printf("%s\n", sol);
            return;
        }
        return;
    }
    for (int i = 0; i < n_dist; i++) {
        if (mark[i] > 0) {
            sol[pos] = dist_val[i];
            mark[i]--;
            perm_rip(pos+1, dist_val, sol, mark, n, n_dist);
            sol[pos] = '\0';
            mark[i]++;
        }
    }
    return;
}

//5.2.6 Cover set - combinazioni semplici
int check4 (int S[][10], int *sol, int k) {
    int *occ, i, j, ok = 1;
    occ = calloc(9+1, sizeof(int));
    if (occ == NULL)
        exit(-1);
    for (i = 0; i < k; i++) {
        j = 0;
        while (S[sol[i]][j] && j < 10) {
            occ[S[sol[i]][j++]] = 12;
        }
    }
    for ( i = 1; i <= 9 && ok; i++) {
        if (!occ[i])
            ok = 0;
    }
    free(occ);
    return ok;
}

int comb(int pos, int S[][10], int *sol, int n, int k, int start) {
    if (pos >= k) {
        if (check4(S, sol, k))
            return 1;
        else return 0;
    }
    
    for (int i = start; i < n; i++) {
        sol[pos] = start;
        if (comb(pos+1, S, sol, n, k, i+1))
            return 1;
    }
    return 0;
}
