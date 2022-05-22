//
//  main.c
//  AP_Exam032017
//
//  Created by Oskar Bich on 11/6/21.
//

#include <stdio.h>
#include <stdlib.h>
#define N 8

typedef struct bst_t *linkBST;
typedef struct list_t *linkL;

struct bst_t {
    char *model;
    linkL l;
};

struct list_t {
    char *vendor;
    float price;
};

float my_atof (char *s);
void bst2list (bst_t *bst, list_t **head, list_t **tail);

int main(int argc, const char * argv[]) {
    char s[N] = "+123.45";
    float f = my_atof(s);
    printf("Numero reale %f\n", f);
    return 0;
}

float my_atof (char *s) {
    float f = 0, n = 1, d = 1;
    int i = 0, cnt = 1;
    if (*s == '-')
        n = -1;
    s++;
    while (s[i] != '.') {
        d *= 10;
        i++;
    }
    cnt = i;
    for (i = 0; i < cnt; i++) {
        d /= 10;
        f += (float) (((int) (s[i]-'0'))*d);
    }
    d = 0.1f;
    s += (int) cnt+1;
    i = 0;
    while (s[i] != '\0') {
        d *= 0.1f;
        i++;
    }
    cnt = i;
    for (i = 0; i < cnt; i++) {
        d *= 10;
        f += (float) (((int) (s[cnt-i-1]-'0'))*d);
    }
    
    f *= n;
    
    return f;
}

void bst2list (bst_t *bst, list_t **head, list_t **tail) {
    
}
