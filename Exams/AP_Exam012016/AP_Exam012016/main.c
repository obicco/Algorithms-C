//
//  main.c
//  AP_Exam012016
//
//  Created by Oskar Bich on 21/11/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matr matr_t, *link;

struct link {
    float **m;
    link next;
};

struct matr_t {
    int r,c;
    link head;
};

char *charErase (char *str, int *pos);
void MatrWrite (matr_t *M, float d, int r, int c);

int main(int argc, const char * argv[]) {
    char str[13] = "ThisIsAString";
    int pos[6] = {7, 4, 2, 0, 11, -1}, i = 0;
    char *strout = charErase(str, pos);
    
    printf("Stringa di output:\t");
    while(strout[i] != '\0') {
        printf("%c", strout[i]);
        i++;
    }
    printf("\n");
    return 0;
}

char *charErase (char *str, int *pos) {
    int i = 0, cnt = 0, l = (int) strlen(str);
    char *strout;
    while (pos[i] != -1) {
        str[pos[i]] = '^';
        cnt++;
        i++;
    }
    strout = malloc((l-cnt)*sizeof(int));
    for (i = 0, cnt = 0; i < l-1 ; i++) {
        if (str[i] != '^') {
            strout[cnt] = str[i];
            cnt++;
        }
        else continue;
    }
    return strout;
}

void MatrWrite (matr_t *M, float d, int r, int c) {
    
}


