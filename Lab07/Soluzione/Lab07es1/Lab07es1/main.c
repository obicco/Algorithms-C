//
//  main.c
//  Lab07es1
//
//  Created by Oskar Bich on 29/11/20.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
} arco;

typedef struct {
    arco *archi;
    int n, a;
} grafo;

grafo *leggiFile(void);
void stampa(grafo *g);
int powerset_comb_sempl(int start, int pos, int *sol, int k, arco *a, int N, int E, int count);
int check(int *sol, int k, arco *a, int E);

int main(int argc, const char * argv[]) {
    int *sol, k, cnt, tot = 0;
    grafo *g = leggiFile();
    stampa(g);
    
    sol = calloc(g->n, sizeof(int));
    
    printf("Vertex cover\n");
    for(k = 1; k <= g->n; k++) {
      printf("di dimensione %d\n", k);
      cnt = powerset_comb_sempl(0, 0, sol, k, g->archi, g->n, g->a, 0);
      if (cnt == 0)
        printf("nessuna soluzione \n");
      tot += cnt;
    }
    printf ("numero di soluzioni: %d \n", tot);

    free(sol);
    free(g->archi);
    free(g);

    return 0;
}

grafo *leggiFile() {
    grafo *g;
    FILE *fIN = fopen("grafo.txt", "r");
    g = (grafo *) calloc(1, sizeof(grafo));
    fscanf(fIN, "%d %d", &g->n, &g->a);
    g->archi = (arco *) calloc(g->a, sizeof(arco));
    
    for (int i = 0; i < g->a; i++, g->archi++) {
        fscanf(fIN, "%d %d", &g->archi->u, &g->archi->v);
    }
    g->archi -= g->a;
    return g;
}

void stampa(grafo *g) {
    printf("Archi letti da file:\n");
    for(int i = 0; i < g->a; i++, g->archi++) {
        printf("(%d, %d)\n", g->archi->u, g->archi->v);
    }
    g->archi -= g->a;
}

int check(int *sol, int k, arco *a, int E) {
  int arcocnt = 0;
  int *arcocheck = calloc(E, sizeof(int));

  for (int i = 0; i < k; i++) {
    for (int j = 0; j < E; j++) {
      if (a[j].u == sol[i] || a[j].v == sol[i]) {
        if (arcocheck[j] == 0)
          arcocnt++;
        arcocheck[j] = 1;
      }
    }
  }
  free(arcocheck);
  return (arcocnt == E);
}

int powerset_comb_sempl(int start, int pos, int *sol, int k, arco *a, int N, int E, int count) {
  if (pos >= k) {
    if (check(sol, k, a, E)) {
      for(int i = 0; i < k; i++)
        printf("%d ", sol[i]);
      printf("\n");
      return count+1;
    }
    return count;
  }
  for (int i = start; i < N; i++) {
    sol[pos] = i;
    count = powerset_comb_sempl(i+1, pos+1, sol, k, a, N, E, count);
  }
  return count;
}

