//
//  Stock.h
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//

#ifndef Stock_h
#define Stock_h

#include <stdio.h>
#include "Index.h"

typedef struct stock_ *Stock;

Stock newStock(char *ticker);
int compareKEY(Stock s1, Stock s2);
char *getKEY(Stock s);
void printStock(FILE *fp, Stock s);
int cmpStock(char* t1, char* t2);
void insertTransactionStock(Stock s, Date d, float val, int qnt);
float minAbsoluteStock(Stock s);
float maxAbsoluteStock(Stock s);
void minmaxRangeStock(Stock s, Date d1, Date d2, float *f1, float *f2);
Quote getQuoteStock(Stock s, Date d);
void treeBalanceStock(Stock s);

#endif /* Stock_h */
