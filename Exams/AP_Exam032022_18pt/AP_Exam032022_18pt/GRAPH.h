//
//  GRAPH.h
//  AP_Exam032022_18pt
//
//  Created by Oskar Bich on 7/4/22.
//

#ifndef GRAPH_h
#define GRAPH_h

#include <stdio.h>

typedef struct {int v, w, wt;}Edge;
typedef struct graph *Graph;

Graph GRAPHinit(int V);
void GRAPHstore(Graph G, FILE *fin);
void GRAPHgetIndex(Graph G, char *label);
void GRAPHinsertE(Graph G, int id1, int id2, int wt);
void GRAPHloadST(FILE *fin, Graph G);
void GRAPHloadM(FILE *fin, Graph G);
int GRAPHcheck1(Graph G, int max, int max_all);
void output(Graph G);

#endif /* GRAPH_h */
