//
//  BT.h
//  AP_Exam012022
//
//  Created by Oskar Bich on 28/1/22.
//

#ifndef BT_h
#define BT_h

#include <stdio.h>
#include <stdlib.h>

typedef struct BT_t *BT; //Dimenticato punatore - utilizzato come tale in BT.c

BT BTinit(void);
void loadEx2(BT t);
int checkBT(BT t);

#endif /* BT_h */
