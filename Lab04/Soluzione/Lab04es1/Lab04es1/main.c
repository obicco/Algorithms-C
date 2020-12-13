//
//  main.c
//  Lab04es1
//
//  Created by Oskar Bich on 14/11/20.
//

#include <stdio.h>

int gcd(int a, int b);
void swap(int *a, int *b);
int iseven(int a);

int main(int argc, const char * argv[]) {
    int a, b;
    printf("Inserire due numeri interi:\n");
    scanf("%d %d", &a, &b);

    if (b > a)
        swap(&a, &b);
    
    printf("Il massimo comun divisore è %d\n", gcd(a, b));
    
    return 0;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int gcd(int a, int b) {
    if(a == b || b == 0)
        return a;
    if (iseven(a) && iseven(b))
        return 2 * gcd((a/2), (b/2));
    if (!iseven(a) && iseven(b))
        return gcd(a, b/2);
    if (iseven(a) && !iseven(b))
        return gcd(a/2, b);
    if (!iseven(a) && !iseven(b))
        return gcd((a-b)/2, b);
    else
        return 1;
}

int iseven(int a) {
    if (a % 2 == 0)
        return 1;
    else
        return 0;
}
