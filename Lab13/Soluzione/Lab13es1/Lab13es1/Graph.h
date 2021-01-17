#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#define MAXL 31

typedef struct edge { int v; int w; int wt; } Edge;
typedef struct { char name[MAXL]; } Vertex;
typedef struct G *Graph;

Edge  EDGEcreate(int v, int w, int wt);
void  EDGEstore (Graph g, Edge e, FILE *fout);
Graph GRAPHinit(int nV);
Graph GRAPHload(FILE *);
void  GRAPHfree(Graph g);
void  GRAPHinsertE(Graph g, Edge e);
void  GRAPHstore(Graph g, FILE *out);
int   GRAPHgetNumV(Graph g);
int   GRAPHgetNumE(Graph g);
void  GRAPHedges(Graph g, Edge *a);
int   GRAPHedgesWt(Graph g, Edge *a, int *subset, int k);
void  GRAPHdfs(Graph g, int *isAcyclic);
void  GRAPHremoveE(Graph g, Edge e);
void  DAGts(Graph g, int *ts);
void  DAGmaxPath(Graph d, int *ts);
char *GRAPHgetName(Graph g, int index);
#endif /* GRAPH_H_INCLUDED */
