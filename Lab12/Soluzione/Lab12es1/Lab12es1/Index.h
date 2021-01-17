//
//  Index.h
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//

#ifndef Index_h
#define Index_h
#define S 2.0

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Date.h"
#include "Quote.h"

typedef struct BSTindex_ *BSTindex;

int BSTindexEmpty(BSTindex index);
Quote BSTindexSearch(BSTindex index, Date d);
void BSTindexInsert(BSTindex index, Date d, float val, int qnt);
void BSTindexMinmaxRange(BSTindex index, Date d1, Date d2, float *f1, float *f2);
BSTindex BSTindexInit(void);
void BSTindexPrint(BSTindex index, FILE *fp);
void BSTindexBalance(BSTindex index);
void BSTgetMinMax(BSTindex index, float *min, float *max);


#endif /* Index_h */
