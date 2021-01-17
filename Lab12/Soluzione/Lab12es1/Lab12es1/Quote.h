//
//  Quote.h
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//

#ifndef Quote_h
#define Quote_h

#include <stdio.h>
#include "Date.h"

typedef struct {
    Date date;
    float val;
    int qnt;
} Quote;

Quote QUOTEnew(Date d);
Date QUOTEgetDate(Quote q);
float QUOTEgetValue(Quote q);
void QUOTEprint(FILE *fp, Quote q);
int QUOTEcheckNull(Quote q);
Quote QUOTEsetNull(void);

#endif /* Quote_h */
