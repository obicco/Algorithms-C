//
//  LIST.c
//  AP_Exam032021
//
//  Created by Oskar Bich on 15/6/21.
//

#include "LIST.h"

struct node_ {
    char *str;
    link next;
};

struct list_ {
    link head;
    int n;
};

void addNode(LIST l, char *str) { //ESAME
    link prev = NULL, curr = l->head;
    while (curr->next != NULL) {
        prev = curr;
        curr = prev->next;
    }
    curr->next = NEWnode(str ,NULL);
    l->n++;
}

link NEWnode (char *str, link next) { //ESAME
    link x = malloc(sizeof(node));
    x->str = strdup(str);
    x->next = next;
    return x;
}

LIST newLIST(link head) { //aggiunto per main
    LIST x = malloc(1*sizeof(LIST*));
    x->n = 0;
    x->head = head;
    return x;
}

void printLIST (LIST l) { //aggiunto per main
    link prev = NULL, curr = l->head->next;
    while (curr != NULL) {
        printf("%s\n", curr->str);
        prev = curr;
        curr = prev->next;
    }
}
