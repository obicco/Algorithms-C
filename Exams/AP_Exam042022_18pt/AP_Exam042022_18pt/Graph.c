//
//  Graph.c
//  AP_Exam042022_18pt
//
//  Created by Oskar Bich on 27/6/22.
//

#include <stdlib.h>
#include "Graph.h"

struct grafo {
    int V, E;
    int **madj;
};

int DScheck (int c, int *v, Graph G);
static Edge EdgeCreate(int v, int w);
static void insertE(Graph G, Edge e);

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
void GRAPHinsertE(Graph G, int id1, int id2);

Graph GRAPHinit(int V) {
    Graph g;
    g = malloc(sizeof(*g));
    g->V = V;
    g->E = 0;
    g->madj = malloc(V*sizeof(int*));
    for (int i = 0; i < V; i++) {
        g->madj[i] = calloc(V, sizeof(int));
        g->madj[i][i] = 1;
    }
    return g;
}

void GRAPHfree(Graph G) {
    for (int i = 0; i < G->V; i++) free(G->madj[i]);
    free(G->madj);
    free(G);
}

static Edge EdgeCreate(int v, int w) {
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
    insertE(G, EdgeCreate(id1, id2));
}

static void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    if(G->madj[v][w] == 0)
        G->E++;
    G->madj[v][w] = 1;
}


void GRAPHprintmatrix(Graph G) {
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) printf("%d ", G->madj[i][j]);
        printf("\n");
    }
}

Graph GRAPHload(FILE *fin) {
    int dim, v, w;
    Graph g;
    fscanf(fin, "%d", &dim);
    g = GRAPHinit(dim);
    while (fscanf(fin, "%d %d", &v, &w) == 2) {
        GRAPHinsertE(g, v, w);
    }
    return g;
}

//RAPPRESENTAZIONE FILE: prima riga indica il numero di partizioni, dalla secon da riga la prima colonna indica il numero di nodi presenti nella partizione, a seguire i nodi stessi seguiti da spazi (esempio come da consegna -- riga 1: 3, riga 2: 2 0 5 etc..)
int verify(FILE *fin, Graph G) {
    int n;
    int **m, *v; //Vettore v per le dimensioni delle partizioni lette da file, matrice m per i l salvataggio delle partizioni
    int *cnt = calloc(G->V, sizeof(int)); //Inizializzo vettore conteggio ricorrenze per par tizionamenti
    
    //LETTURA FILE
    fscanf(fin, "%d", &n); //Numero di partizioni definite sulla prima riga del file
    m = malloc(n*sizeof(int*));  //ERR sintassi - Messo asterisco prima di int e non dopo
    v = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d ", &v[i]);
        m[i] = malloc (v[i]*sizeof(int));
        for (int j = 0; j < v[i]; j++) {
            fscanf(fin, "%d ", &m[i][j]);
        }
    }
    
    //VERIFICA PARTIZONAMENTO CORRETTO
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < v[i]; j++) {
            cnt[m[i][j]] += 1;
            if (cnt[m[i][j]] > 1) //Se ripetuto, no partizionamento, ritorno 0
                return 0;
        }
    }
    for (int i = 0; i < G->V; i++) {
        if (cnt[i] == 0)
            return 0; // Partizione non comprende tutti i vertici, ritorno 0
    }
    //VERIFICA DOMINATING SET
    for (int i = 0; i < n; i++) {
        if(!DScheck(v[i], m[i], G))
            return 0; //Almeno uno dei sottoinsiemi non e' dominating set
    }
    return 1;
}
    
int DScheck (int c, int *v, Graph G) {
    int *visited = calloc(G->V, sizeof(int));
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < G->V; j++) {
            if (G->madj[v[i]][j])
                visited[j] = 1;
        }
    }
    for (int i = 0; i < G->V; i++) {
        if (!visited[i])
            return 0; //Se almeno un vertice non e' stato visitato, ritorno 0
    }
    return 1;
}

 
