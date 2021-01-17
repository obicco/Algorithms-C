//
//  Exchange.c
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//

#include "Exchange.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_ {
    struct node_ *next;
    Stock s;
} node;

typedef node* link;

struct LISTstocks_ {
    link head;
    int count;
};

LISTstocks LISTstocksInit(void) {
    LISTstocks stocks = calloc(1, sizeof(*stocks));
    return stocks;
}

int LISTstocksEmpty(LISTstocks stocks) {
    if (stocks == NULL || stocks->head == NULL || stocks->count == 0)
        return 1;
    return 0;
}

static link NEW(Stock s, link next) {
    link l = calloc(1, sizeof(*l));
    l->next = next;
    l->s = s;
    return l;
}

void LISTstocksInsert(Stock s, LISTstocks stocks) {
    link prev = NULL, curr = stocks->head;
    while (curr != NULL && compareKEY(s, curr->s) > 0) {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL) {
        stocks->head = NEW(s, curr);
        stocks->count++;
        return;
    }
    if (prev->next == NULL)
        prev->next = NEW(s, NULL);
    else
        prev->next = NEW(s, curr);
    stocks->count++;
}

Stock LISTstocksSearch(LISTstocks stocks, char *cod) {
    link prev = NULL, curr = stocks->head;
    while (curr != NULL && strcmp(cod, getKEY(curr->s)) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL)
        return NULL;
    else return curr->s;
}

void LISTstocksPrint (LISTstocks stocks, FILE *fp) {
    link prev = NULL, curr = stocks->head;
    if (LISTstocksEmpty(stocks))
        return;
    while (curr != NULL) {
        printStock(fp, curr->s);
        prev = curr;
        curr = curr->next;
    }
}
