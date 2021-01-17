//
//  Stock.c
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//

#include "Stock.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stock_ {
    char *ticker;
    float min, max;
    BSTindex index;
};

Stock newStock(char *ticker) {
    Stock s = calloc(1, sizeof(*s));
    s->ticker = strdup(ticker);
    s->min = s->max = -1.0;
    s->index = BSTindexInit();
    return s;
}

int compareKEY(Stock s1, Stock s2) {
    return strcmp(s1->ticker, s2->ticker);
}

char *getKEY(Stock s) {
    return s->ticker;
}

void printStock(FILE *fp, Stock s) {
    fprintf(fp, "%s [MIN = %.2f - MAX = %.2f]\n", s->ticker, s->min, s->max);
    BSTindexPrint(s->index, fp);
}

int cmpStock(char* t1, char* t2) {
  return strcmp(t1, t2);
}

void updateMinmax(Stock s) {
  float min = -1.0, max = -1.0;
    BSTgetMinMax(s->index, &min, &max);
  s->min = min;
  s->max = max;
}

void insertTransactionStock(Stock s, Date d, float val, int qnt) {
  BSTindexInsert(s->index, d, val, qnt);
  updateMinmax(s);
  return;
}

float minAbsoluteStock(Stock s) {
  if (s == NULL)
    return -1;
  return s->min;
}

float maxAbsoluteStock(Stock s) {
  if (s == NULL)
    return -1;
  return s->max;
}

void valRange(Stock s, Date d1, Date d2, float *f1, float *f2) {
  BSTindexMinmaxRange(s->index, d1, d2, f1, f2);
}

void minmaxRangeStock(Stock s, Date d1, Date d2, float *f1, float *f2) {
  int cmp = DATEcmp(d1, d2);
  if (cmp < 0)
    valRange(s, d1, d2, f1, f2);
  else if (cmp > 0)
    valRange(s, d2, d1, f1, f2);
  else
    *f1 = *f2 = QUOTEgetValue(BSTindexSearch(s->index, d1));
}

Quote getQuoteStock(Stock s, Date d) {
  if (s == NULL)
    return QUOTEsetNull();
  if (s->index == NULL)
    return QUOTEsetNull();
  return BSTindexSearch(s->index, d);
}

void treeBalanceStock(Stock s) {
  if (s == NULL || s->index == NULL)
    return;
  BSTindexBalance(s->index);
}
