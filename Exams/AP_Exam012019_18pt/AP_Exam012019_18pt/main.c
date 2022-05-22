//
//  main.c
//  AP_Exam012019_18pt
//
//  Created by Oskar Bich on 22/3/22.
//

#include <stdio.h>
#include <stdlib.h>

#include "ST.h"
#include "Graph.h"

int main(int argc, const char * argv[]) {
    Graph G;
    int *sol, dim=0;
    FILE *in;
    in = fopen(argv[1], "r");
    G = GRAPHreadFile(in);
    fclose(in);
    GRAPHprintmatrix(G);
    in = fopen(argv[2], "r");
    sol = kernelRead(in, G, &dim);
    if(isKernel(G, sol, dim))
        printf("La soluzione proposta e' un kernel di G\n");
    else
        printf("La soluzione proposta non e' un kernel di G\n");
    fclose(in);
    GRAPHminimumKernel(stdout, G);
}
