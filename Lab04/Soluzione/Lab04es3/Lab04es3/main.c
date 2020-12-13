//
//  main.c
//  Lab04es3
//
//  Created by Oskar Bich on 20/11/20.
//

#include <stdio.h>
#include <string.h>

char *cercaRegexp(char *src, char *regexp);
char *dot(char *src, char *regexp, int l);
int checkKey(char *src,char *regexp,int l);
int reglen(char *regexp);

int main(int argc, const char * argv[]) {
    char *p = NULL;
    char src[] = "Ai fini";
    char regexp[] = ".zrc";
    
    printf("Espressione regolare: ");
    p = cercaRegexp(src, regexp);
    if (p == NULL)
        printf("non trovata");
    
    return 0;
}

// complete all cases
char *cercaRegexp(char *src, char *regexp) {
    int len;
    char *p = NULL;
    do {
        switch (*regexp) {
            case '.':
                len = reglen(regexp+1);
                p = dot(src, regexp+1, len);
                if (p != NULL) {
                    for (int i = 0; i < len; i++, p++) {
                        printf("%c", *p);
                    }
                    return p;
                }
                regexp += len;
                break;
            case '[':
                
                
            default:
                regexp++;
                break;
        }
    } while(*regexp != '\0');
    return p;
}

char *dot(char *src, char *regexp, int l) {
    while (*src != '\0') {
        if (*src == *regexp && checkKey(src, regexp, l))
            return src;
        else src++;
    }
    return NULL;
}

int checkKey(char *src,char *regexp,int l) {
    int cnt = 0;
    for (int i = 0; i < l; i++, src++, regexp++) {
        if (*src == *regexp)
            cnt++;
        else return 0;
    }
    if (cnt == l)
        return 1;
    else return 0;
}

int reglen(char *regexp) {
    int len = 0;
    while (*regexp != '.' && *regexp != '[' && *regexp != '/' && *regexp != '\0') {
        len++;
        regexp++;
    }
    return len;
}
