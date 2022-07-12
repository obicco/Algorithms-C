//
//  main.c
//  AP_Exam032022
//
//  Created by bicco on 21/6/22.
//

#include <stdio.h>
#include <stdio.h>
#include <string.h>

#define N 256

typedef struct {
    int key;
    struct node *children[N];
}node;

void searchStr (char *str, int *start, int *l, int dim);

int main(int argc, const char * argv[]) {
    int start = 0, l = 0;
    char *str = "aabcdeefghhik";
    searchStr(str, &start, &l, (int) strlen(str));
    printf(" %d %d\n", start, l);
    return 0;
}

void searchStr (char *str, int *start, int *l, int dim) {
    char res[N] = {};
    int cnt = 0;
    for (int i = 1; i < dim; i++) { //Scandisco l'intera stringa
        if (str[i] != str[i-1])
            cnt++;
        else if (cnt > *l) {
            for (int j = i-cnt-1; j < i; j++) res[j] = str[i-cnt+j];
            res[cnt] = '\0';
            *l = cnt;
            *start = i-cnt;
            cnt = 1;
            }
        else cnt = 1;
    }
    printf("%s ", res);
}

