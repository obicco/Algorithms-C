//
//  main.c
//  AP_Exam032022_18pt
//
//  Created by Oskar Bich on 7/4/22.
//

#include <stdio.h>
#include "GRAPH.h"

int main(int argc, const char * argv[]) {
    FILE *in;
    int dim;
    Graph G;
    in = fopen(argv[1], "r");
    fscanf(in, "%d", &dim);
    G = GRAPHinit(dim);
    GRAPHloadST(in, G);
    fclose(in);
    in = fopen(argv[2], "r");
    GRAPHstore(G, in);
    fclose(in);
    in = fopen(argv[3], "r");
    GRAPHloadM(in, G);
    output(G);
    if (GRAPHcheck1(G, *argv[4], *argv[5]))
        printf("\nTutte le coppie di punti di interesse sono minori di %d ed il cammino e' minore di %d\n\n", *argv[4], *argv[5]);
    else printf("\nLe prime due condizioni non sono rispettate per la soluzione caricata\n");
    return 0;
}


/* Esempio file "terzo.txt"
 3
 PiazzaCastello PortaPalatina
 PortaPalatina GiardiniReali
 GiardiniReali MoleAntonelliana
*/

