//
//  Graph.h
//  AP_Exam042022_18pt
//
//  Created by Oskar Bich on 27/6/22.
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
void GRAPHprintmatrix(Graph G);

Graph GRAPHload(FILE *fin);
int verify(FILE *fin, Graph G);

#endif /* Graph_h */
