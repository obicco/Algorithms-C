//
//  Quote.c
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Quote.h"

Date QUOTEgetDate(Quote q) {
    return q.date;
}

float average(Quote q) {
    if (q.qnt != 0)
        return q.val /(float) q.qnt;
    return 0;
}

float QUOTEgetValue(Quote q) {
    return average(q);
}

void QUOTEprint(FILE *fp, Quote q) {
    DATEprint(q.date, fp);
    printf("%.2f\n", QUOTEgetValue(q));
}

int QUOTEcheckNull(Quote q) {
    return (q.qnt == 0);
}

Quote QUOTEsetNull(void) {
    Quote q = {0};
    return q;
}

