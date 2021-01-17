//
//  Date.h
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//

#ifndef Date_h
#define Date_h
#define DATELEN 13 /* aaaa/mm/gg */
#define TIMELEN 6  /* hh:mm */

#include <stdio.h>

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
}Date;

Date DATEload (char *s1, char *s2);
void DATEprint (Date d, FILE *fp);
int DATEcmp (Date d1, Date d2);

#endif /* Date_h */
