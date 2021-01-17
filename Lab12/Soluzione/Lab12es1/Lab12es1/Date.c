//
//  Date.c
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//

#include "Date.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Date DATEload (char *s1, char *s2) {
    Date d;
    sscanf(s1, "%d/%d/%d", &d.year, &d.month, &d.day);
    sscanf(s2, "%d:%d", &d.hour, &d.minute);
    return d;
}

void DATEprint (Date d, FILE *fp) {
    fprintf(fp, "%d/%d/%d %d:%d\n", d.year, d.month, d.day, d.hour, d.minute);
}

int DATEcmp (Date d1, Date d2) {
    if (d1.year != d2.year)
        return (d1.year - d2.year);
    if (d1.month != d2.month)
        return (d1.month - d2.month);
    if (d1.day != d2.day)
        return (d1.day - d2.day);
    return 0;
}
