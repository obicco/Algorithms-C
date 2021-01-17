#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

#include "ST.h"
#include "Graph.h"

#define MAXL 31
#define MAXN 10

#define DBG 0

void generaSetE(Graph g);

int main(int argc, char **argv) {
  int i, V, a=1;
  Graph g = NULL;
  FILE *in;
  int *ts;

  if (argc != 2) {
    printf("Use: %s <file_in>\n", argv[0]);
    exit(-1);
  }

  in = fopen(argv[1], "r");
  if (in == NULL)
    exit(-1);

  g = GRAPHload(in);
  if (g == NULL)
    exit(-1);
#if DBG
  printf("Grafo originale\n");
  GRAPHstore(g, stdout);
#endif
  GRAPHdfs(g, &a);
  if (!a) {
    printf("Il grafo originale e' ciclico\n\n");
    generaSetE(g);
    printf("Il DAG risultante e'\n\n");
    GRAPHstore(g, stdout);
    printf("\n");
  }
  else
    printf("Il grafo originale e' gia' un DAG\n\n");

  V = GRAPHgetNumV(g);
  ts = malloc(V*sizeof(int));

  DAGts(g, ts);

  printf("Ordinamento topologico\n");
  for (i=0; i<V; i++)
    printf("%s ", GRAPHgetName(g, ts[i]));
  printf("\n\n");

  printf("Distanze massime da tutti i vertici (-1 => irraggiungibile)\n");

  DAGmaxPath(g, ts);


  GRAPHfree(g);
  free(ts);

  return 0;
}

void comb_sempl(int pos, int *sol, Graph g, Edge *vE, int n, int k, int start, int *stop, int *bestSol, int *bestWt) {
  int i, a=1, solWt;
  if (pos >= k) {

    /* Rimozione del set di archi scelti */
    for (i=0; i<k; i++)
      GRAPHremoveE(g, vE[sol[i]]);
    solWt = GRAPHedgesWt(g, vE, sol, k);

    /* Verifica di aciclicit‡ */
    GRAPHdfs(g, &a);

    /* Se aciclico, imposta condizione di stop per set a cardinalit‡ maggiore di questa e aggiorna best se migliorante */
    if (a) {
      *stop = 1;
      if (solWt > *bestWt) {
        *bestWt = solWt;
        for(i=0;i<k;i++)
          bestSol[i] = sol[i];
      }
    }

    /* Ripristino del set di archi scelti */
    for (i=0; i<k; i++)
      GRAPHinsertE(g, vE[sol[i]]);

    return;
  }
  for (i=start; i<n; i++) {
    sol[pos] = i;
    comb_sempl(pos+1, sol, g, vE, n, k, i+1, stop, bestSol, bestWt);
  }
}

void generaSetE(Graph g) {
  int i, j, E = GRAPHgetNumE(g), V = GRAPHgetNumV(g), stop = 0, bestWt = 0;
  Edge *vE = malloc(E*sizeof(Edge));
  int *sol;
  int *bestSol = calloc(E, sizeof(int));
  int upper_bound = E - (V - 1);
  if (upper_bound <= 0)
    return;
  printf("\nV=%d, E=%d, numero massimo di archi da rimuovere %d\n", V, E, upper_bound);
  GRAPHedges(g, vE);

  /*  esclude il set vuoto e itera fino al massimo a cardinalita'  |E|-(|V|-1) */
  for(i=1; i<=upper_bound && !stop; i++) {
    sol = malloc(i * sizeof(int));
    printf("Generazione set di cardinalita' %d\n", i);
    comb_sempl(0, sol, g, vE, E, i, 0, &stop, bestSol, &bestWt);
  }
  /* elenco archi rimossi nella soluzione ottima */
  printf("elenco archi rimossi nella soluzione ottima\n");
  for (j=0; j<i-1; j++)
    EDGEstore(g, vE[bestSol[j]], stdout);
  printf("\n");

  /* costruzione del DAG finale ottimo */
  if (stop)
    for (j=0; j<i-1; j++)
      GRAPHremoveE(g, vE[bestSol[j]]);
}

