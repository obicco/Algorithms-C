//
//  main.c
//  Lab07es2
//
//  Created by Oskar Bich on 05/12/20.
// anag1.txt anag2.txt -- vedere video liste

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
}TInfo;

typedef struct {
    TInfo info;
    struct SNode *link;
}TNode;

typedef TNode *TList;

TList Crea_Lista(void);
TInfo Leggi_Info(void);
TList Inserisci_Elemento(TList list, TInfo info);
void Stampa_Lista(TList lista);

int main(int argc, const char * argv[]) {
    TList lista = Crea_Lista();
    TInfo info;
    int dim;
    
    printf("Quani elementi vuoi inserire?\n");
    scanf("%d", &dim);
    for (int i = 0; i < dim; i++) {
        info = Leggi_Info();
        lista = Inserisci_Elemento(lista, info);
    }
    
    
    return 0;
}

TList Crea_Lista() {
    return NULL;
}

TInfo Leggi_Info(void) {
    TInfo info;
    printf("Inserisci numero\n");
    scanf("%d", &info.value);
    return info;
}

TList Inserisci_Elemento(TList list, TInfo info) {
    TList prec = NULL, curr = list, newnode;
    
    while(curr != NULL && info.value > curr->info.value) { //Ricerca poszizione inseirmento (scorre lita)
        prec = curr;
        curr = curr->link;
    }
    newnode = (TNode *) malloc(sizeof(TNode));
    newnode->info = info;
    if(prec == NULL) {
        newnode->link = list;
        list = newnode;
        return list;
    }else {
        prec->link = newnode;
        newnode->link = curr;
        return list;
    }
    return newnode;
}

void Stampa_Lista(TList lista) {
    TList curr;
    curr = lista; //Curr è il primo nodo della lista
    while(curr != NULL) {
        printf("%d", curr->info.value);
        curr = curr->link;
    }
}
