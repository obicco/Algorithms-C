//
//  LIST.h
//  AP_Exam032021
//
//  Created by Oskar Bich on 15/6/21.
//

#ifndef LIST_h
#define LIST_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_ node, *link;
typedef struct list_ *LIST; //Dimenticato puntatore durante dichiarazione, utilizzato sempre come tale nel resto del problema

link NEWnode(char *str, link next);
void addNode(LIST l, char *str);
LIST newLIST(link head);
void printLIST (LIST l);

#endif /* LIST_h */
