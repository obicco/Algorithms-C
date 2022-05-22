//
//  Graph.h
//  AP_Exam012019_18pt
//
//  Created by Oskar Bich on 22/3/22.
//

#ifndef Graph_h
#define Graph_h

#include <stdio.h>

typedef struct {int v, w;}Edge;
typedef struct grafo *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
void GRAPHinsertE(Graph G, int id1, int id2);
void GRAPHremoveE(Graph G, int id1, int id2);
Graph GRAPHreadFile(FILE *in);
void GRAPHprintmatrix(Graph G);
int GRAPHedges(Graph G, int *v, int i);
int GRAPHgetE(Graph G);
int GRAPHgetV(Graph G);

int isKernel(Graph G, int *sol, int dim);
int *kernelRead(FILE *in,Graph G, int *dim);
void GRAPHminimumKernel(FILE *out, Graph G);

#endif /* Graph_h */
