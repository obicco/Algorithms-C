//
//  main.c
//  Lab06es1
//
//  Created by Oskar Bich on 24/11/20.
// brani.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXS 256

typedef struct {
    int ns;
    char **song;
} friend;

friend* readFile(int *nf);
void princ_molt(int pos, friend *a, int *sol, int n, int *count);

int main(int argc, const char * argv[]) {
    friend *friends;
    int *sol, nf, count = 0;
    
    friends = readFile(&nf);
    
    sol = calloc(nf, sizeof(int));
    princ_molt(0, friends, sol, nf, &count);
    
    for (int i = 0; i < nf; i++) {
        free(friends[i].song);
    }
    free(friends);
    
    return 0;
}

friend* readFile(int *nf) {
    friend *a;
    char tmp[MAXS];
    FILE *fIN = fopen("brani.txt", "r");
    
    fscanf(fIN, "%d", nf);
    
    a = calloc(*nf, sizeof(friend));
    if (a == NULL) {
        printf("Error during array allocation");
        exit(-1);
    }
    
    for(int i = 0; i < *nf; i++, a++) {
        fscanf(fIN, "%d", &a->ns);
        a->song = calloc(a->ns, sizeof(char*));
        for(int j = 0; j < a->ns; j++, a->song++) {
            fscanf(fIN, "%s", tmp);
            *(a->song) = strdup(tmp);
        }
        a->song -= a->ns;
    }
    fclose(fIN);
    
    return a - *nf;
}

void princ_molt(int pos, friend *a, int *sol, int n, int *count) {
    if (pos >= n) {
        printf("Playlist %d:\n", ++(*count));
        for (int i = 0; i < pos; i++) {
            printf(" * %s", a[i].song[sol[i]]);
        }
        printf("\n");
        return;
    }
    for(int i = 0; i < a[pos].ns; i++) {
        sol[pos] = i;
        princ_molt(pos+1, a, sol, n, count);
    }
    return;
}
