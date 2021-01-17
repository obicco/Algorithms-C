#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "ST.h"

#define DBG 0
/* Dato che il valore 0 e' un valore ammissibile per i pesi, si utilizza il valore -1 per rappresentare l'assenza dell'arco */
#define NO_EDGE -1

struct G {
  int V, E;
  int **madj;
  ST st;
  Vertex *vett;
};

static int **MATRIXint(int r, int c, int val) {
  int i, j, **t;

  t = malloc(r * sizeof(int *));
  if (t==NULL)
    return NULL;
  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i]==NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

char *GETname(Vertex *v) {
  return (v->name);
}

Graph GRAPHinit(int nV) {
  Graph g = malloc(sizeof(*g));
  if (g == NULL)
    return NULL;

  g->V = nV;
  g->E = 0;

  g->madj = MATRIXint(nV, nV, NO_EDGE);
  if (g->madj == NULL)
    return NULL;

  g->st = STinit(nV);
  if (g->st == NULL)
    return NULL;

  g->vett = malloc((nV)*sizeof(Vertex));
  if (g->vett == NULL)
    return NULL;

  return g;
}


Graph GRAPHload(FILE *in) {
  int i, V, wt, id1, id2;
  char src[MAXL], dst[MAXL];
  Graph g;

  fscanf(in, "%d", &V);
  g = GRAPHinit(V);
  if (g == NULL)
    return NULL;

  for (i=0; i<V; i++) {
    fscanf(in, "%s", src);
    strcpy(g->vett[i].name, src);
    STinsert(g->st, src, i);
  }

  while(fscanf(in, "%s %s %d", src, dst, &wt) == 3) {
    id1 = STsearch(g->st, src);
    id2 = STsearch(g->st, dst);
    if (id1 != id2 && id1 >= 0 && id2 >= 0)
      GRAPHinsertE(g, EDGEcreate(id1, id2, wt));
  }

  return g;
}

void GRAPHfree(Graph g) {
  int v;
  for (v=0; v<g->V; v++)
    free(g->madj[v]);
  free(g->madj);
}

Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

void EDGEstore (Graph g, Edge e, FILE *fout){
  fprintf(fout, "%s  %s %d\n", GETname(&(g->vett[e.v])), GETname(&(g->vett[e.w])), e.wt);
}

void  GRAPHinsertE(Graph g, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  g->madj[v][w] = wt;
  g->E++;
}

void GRAPHstore(Graph g, FILE *fout) {
  int i;
  Edge *a;
  if (g == NULL)
    return;
  if (g->madj == NULL)
    return;

  a = malloc(g->E * sizeof(Edge));
  if (a == NULL)
    return;

  GRAPHedges(g, a);

  fprintf(fout, "%d\n", g->V);
  for (i = 0; i < g->V; i++)
    fprintf(fout, "%s\n", GETname(&(g->vett[i])));

  for (i = 0; i < g->E; i++)
    fprintf(fout, "%s  %s %d\n", GETname(&(g->vett[a[i].v])), GETname(&(g->vett[a[i].w])), a[i].wt);

}

int GRAPHgetNumV(Graph g) {
  if (g == NULL)
    return -1;
  return g->V;
}

int GRAPHgetNumE(Graph g) {
  if (g == NULL)
    return -1;
  return g->E;
}

void dfsR(Graph g, int start, int *time, int *pre, int *post, int *isAcyclic) {
  int v;
  pre[start] = (*time)++;
  for (v=0; v<g->V;v++) {
    if (g->madj[start][v] != NO_EDGE) {
      if (pre[v] == -1)
        dfsR(g, v, time, pre, post, isAcyclic);
      else
        if (post[v] == -1)
          *isAcyclic = 0;
    }
  }
  post[start] = (*time)++;
}

void GRAPHdfs(Graph g, int *isAcyclic) {
  int *pre, *post, v, time = 0;
  if (g == NULL)
    return;
  if (g->madj == NULL)
    return;
  pre = calloc(g->V, sizeof(int));
  post = calloc(g->V, sizeof(int));

  for(v=0;v<g->V;v++)
    pre[v] = post[v] = -1;

  for(v=0;v<g->V;v++)
    if (pre[v] == -1)
      dfsR(g, v, &time, pre, post, isAcyclic);

  free(pre);
  free(post);
  return;
}

void  GRAPHedges(Graph g, Edge *a) {
  int v, w, E = 0;
  if (g == NULL)
    return;
  if (g->E <= 0)
    return;
  for (v=0; v < g->V; v++)
    for (w=0; w < g->V; w++)
      if (g->madj[v][w] != NO_EDGE)
        a[E++] = EDGEcreate(v, w, g->madj[v][w]);
}

int GRAPHedgesWt(Graph g, Edge *a, int *subset, int k) {
  int i, totWt=0;
  if (g == NULL)
    return 0;
  for (i=0; i<k; i++)
    totWt +=a[subset[i]].wt;
  return totWt;
}

void GRAPHremoveE(Graph g, Edge e) {
  int v = e.v, w = e.w;
  if (g->madj[v][w] != NO_EDGE)
    g->E--;
  g->madj[v][w] = NO_EDGE;
}

void TSdfsR(Graph D, int v, int *ts, int *pre, int *time) {
  int w;
  pre[v] = 0;
  for (w  = 0; w < D->V; w++)
    if (D->madj[w][v]  != NO_EDGE)
      if (pre[w] == -1)
        TSdfsR(D, w, ts, pre, time);
  ts[(*time)++] = v;
}

void DAGts(Graph D, int *ts) {
  int v, time = 0, *pre;
  pre = malloc(D->V*sizeof(int));
  if ((pre == NULL) || (ts == NULL))
    return;

  for (v=0; v < D->V; v++) {
    pre[v] = -1;
    ts[v] = -1;
  }

  for (v=0; v <D->V; v++)
    if (pre[v]== -1)
      TSdfsR(D, v, ts, pre, &time);

  free(pre);
}

void DAGmaxPath(Graph d, int *ts) {
  int v, w, i, j, k;
  int *dist = malloc(d->V * sizeof(int));

  for (i=0; i<d->V;i++) {
    v = ts[i];
    printf("Start: %s\n", GETname(&(d->vett[v])));
    for (j=0; j<d->V; j++)
      dist[j] = -1; /* concettualmente conta come -INF a rappresentare una condizione di non raggiungibilita' */
    dist[v] = 0;
    for (j=i; j<d->V; j++) {
      w = ts[j];
      if (dist[w] == -1) /* non da non rilassare, sebbene successivo nell'ordinamento topologico, poiche' non raggiungibile */
        continue;
      for (k=0; k<d->V; k++) {
        if (d->madj[w][k] != NO_EDGE)
          if (dist[k] == -1 || dist[w]+d->madj[w][k] > dist[k])
            dist[k] = dist[w]+d->madj[w][k];
      }
    }
    for (j=0; j<d->V; j++) {
      if (j==v)
        continue;
      printf("\t -> %s [%d]\n", GETname(&(d->vett[j])), dist[j]);
    }
  }

  free(dist);
  return;
}

char *GRAPHgetName(Graph g, int index) {
  if (g == NULL) return NULL;
  if (g->vett == NULL) return NULL;
  return g->vett[index].name;
}
