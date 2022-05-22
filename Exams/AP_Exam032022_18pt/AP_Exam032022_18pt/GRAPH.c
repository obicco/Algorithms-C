//
//  GRAPH.c
//  AP_Exam032022_18pt
//
//  Created by Oskar Bich on 7/4/22.
//

#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"
#include "ST.h"
#define MAXC 51

struct graph{
    int V, E;
    int **Madj;
    ST table;
    int **M, **Mmin;
    int dimM; //Inserita dimM in quanto andremo a considerare anche cammini non semplici, serve per la visita
};

static Edge EdgeCreate(int v, int w, int wt);
static void insertE(Graph G, Edge e);
static int GRAPHvisitMR(Graph G, int pos, int max, int max_all, int all_wt);

int GRAPHgetE(Graph G) {
    return G->E;
}

int GRAPHgetV(Graph G) {
    return G->V;
}

Graph GRAPHinit(int V) {
    Graph g;
    g = malloc(sizeof(*g));
    g->V = V;
    g->E = 0;
    g->Madj = malloc(V*sizeof(int*));
    for (int i = 0; i < V; i++) g->Madj[i] = calloc(V, sizeof(int));
    return g;
}

static Edge EdgeCreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EdgeCreate(id1, id2, wt));
}

void insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  if (G->Madj[v][w] == 0)
    G->E++;
  G->Madj[v][w] = wt;
}

void GRAPHstore(Graph G, FILE *fin) {
    int wt;
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) {
            fscanf(fin, "%d", &wt);
            insertE(G, EdgeCreate(i, j, wt));
        }
    }
}

void GRAPHloadST(FILE *fin, Graph G) {
    char val[MAXC];
    G->table = STinit(G->V);
    while (fscanf(fin, "%s", val) == 1) {
        STinsert(G->table, val);
    }
}

void GRAPHloadM(FILE *fin, Graph G) { //INSERITO G->m al posto di G->M in tutta la funzione durante l'esame
    int dim, i = 0;
    char id1[MAXC], id2[MAXC];
    
    fscanf(fin, "%d", &dim);
    G->M = malloc (dim*sizeof(int*));
    G->dimM = dim;
    while (fscanf(fin, "%s %s", id1, id2) == 2) {
        G->M[i] = malloc(2*sizeof(int));
        G->M[i][0] = STgetindex(G->table, id1);  //G->M al posto di M da sola
        G->M[i][1] = STgetindex(G->table, id2);  //G->M al posto di M da sola
        i++;
    }
}

int GRAPHcheck1(Graph G, int max, int max_all) {
    return GRAPHvisitMR(G, 0, max, max_all, 0);
}

int GRAPHvisitMR(Graph G, int pos, int max, int max_all, int all_wt) {
    if (pos >= G->dimM) {
        if (all_wt > max_all)
            return 0;
        return 1;
    }
    all_wt += G->Madj[G->M[pos][0]][G->M[pos][1]];
    if (G->Madj[G->M[pos][0]][G->M[pos][1]] > max || all_wt > max_all)
        return 0;
    return GRAPHvisitMR(G, pos+1, max, max_all, all_wt);
}

//Output
void output(Graph G) {
    printf("Hashtable:\n");
    STprint(G->table);
    printf("\nMatrice Madj:\n");
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++)
            printf("%d ", G->Madj[i][j]);
        printf("\n");
    }
    printf("\nMatrice M:\n");
    for (int i = 0; i < G->dimM; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d ", G->M[i][j]);
        printf("\n");
    }
    
}
