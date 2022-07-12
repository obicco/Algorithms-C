//
//  main.c
//  AP_Exam042022_18pt
//
//  Created by Oskar Bich on 27/6/22.
//

#include <stdio.h>
#include <stdlib.h>
#define FILE1 "/Users/oskar/Library/Mobile Documents/com~apple~CloudDocs/Development/C/AP/Exams/AP_Exam042022_18pt/AP_Exam042022_18pt/g.txt"
#define FILE2 "/Users/oskar/Library/Mobile Documents/com~apple~CloudDocs/Development/C/AP/Exams/AP_Exam042022_18pt/AP_Exam042022_18pt/proposta.txt"

#include "Graph.h"

int main(int argc, const char * argv[]) {
    Graph G;
    FILE *in;
    in = fopen(FILE1, "r");
    G = GRAPHload(in);
    fclose(in);
    GRAPHprintmatrix(G);
    in = fopen(FILE2, "r");
    if(verify(in, G))
        printf("La soluzione proposta e' una domatic partition di G\n");
    else
        printf("La soluzione proposta NON e' una domatic partition di G\n");
    fclose(in);
    GRAPHfree(G);
}
