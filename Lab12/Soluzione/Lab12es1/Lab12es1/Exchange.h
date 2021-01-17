//
//  Exchange.h
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//

#ifndef Exchange_h
#define Exchange_h
#define LEN 256

#include <stdio.h>

#include "Stock.h"

typedef struct LISTstocks_ *LISTstocks;

LISTstocks LISTstocksInit(void);
int LISTstocksEmpty(LISTstocks stocks);
void LISTstocksInsert(Stock s, LISTstocks stocks);
Stock LISTstocksSearch(LISTstocks stocks, char *cod);
void LISTstocksPrint (LISTstocks stocks, FILE *fp);

#endif /* Exchange_h */
