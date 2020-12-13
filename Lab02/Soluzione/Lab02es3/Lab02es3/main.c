//
//  main.c
//  Lab02es3
//
//  Created by Oskar Bich on 07/11/2020.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXN 20
#define MAXC 6
#define MAXP 10
#define MAXW 25

typedef struct {
    char key[MAXN];
    int pos[MAXP];
    char word[MAXP][MAXW];
    int cnt;
} key;

int leggiFIle(key keys[MAXN]);
void cercaOccorrenze(key keys[MAXN], int n);
int wordMatch(char key[MAXN], char w_tmp[MAXW], int l, int i);
void stampaOccorrenze(key keys[MAXN], int n);

int main(int argc, const char * argv[]) {
    key keys[MAXN];
    int n;
    
    n = leggiFIle(keys);
    cercaOccorrenze(keys, n);
    stampaOccorrenze(keys, n);
    
    return 0;
}

int leggiFIle(key keys[MAXN]) {
    FILE *fp = fopen("sequenze.txt", "r");
    int n;
    fscanf( fp, "%d", &n);
    for(int i = 0; i < n; i++) {
        fscanf(fp, "%s", keys[i].key);
        keys[i].cnt = 0;
    }
    fclose(fp);
    return n;
}

void cercaOccorrenze(key keys[MAXN], int n) {
    FILE *fp = fopen("testo.txt", "r");
    char w_tmp[MAXW];
    int pos = 0;
    
    while (fscanf(fp, "%s", w_tmp) != EOF) {
        pos++;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < strlen(w_tmp); j++) {
                if(wordMatch(keys[i].key, w_tmp, (int) strlen(keys[i].key), j) && keys[i].cnt < 10) {
                    keys[i].pos[keys[i].cnt] = pos;
                    strcpy(keys[i].word[keys[i].cnt], w_tmp);
                    keys[i].cnt++;
                    j += (int) strlen(keys[i].key)-1;
                }
            }
        }
    }
    fclose(fp);
}

int wordMatch(char key[MAXN], char w_tmp[MAXW], int l, int i) {
    int cnt = 0;
    for(int j = 0; j < l; j++) {
        if (tolower(w_tmp[i+j]) == tolower(key[j])) {
            cnt++;
        } else return 0;
        if (cnt == l)
            return 1;
    }
    return 0;
}

void stampaOccorrenze(key keys[MAXN], int n) {
    for (int i = 0; i < n; i++) {
        if (keys[i].cnt > 0)
            printf("La sequenza <%s> è contenuta in:\n", keys[i].key);
        for(int j = 0; j < keys[i].cnt; j++) {
            printf("%s --(parola in posizione %d)\n", keys[i].word[j], keys[i].pos[j]);
        }
        printf("\n");
    }
}
