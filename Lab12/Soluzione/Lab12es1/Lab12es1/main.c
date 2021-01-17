//
//  main.c
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//  F1.txt F2.txt F3.txt

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Index.h"
#include "Exchange.h"
#include "Date.h"

#define N_OPT 8

void readFILE (char *fn, LISTstocks stocks);
void printMenu (char *options[], int *sel);

int main(int argc, const char * argv[]) {
    char *options[] = {
          "Uscita",
          "Leggi file",
          "Stampa titoli",
          "Stampa titolo",
          "Stampa quotazione",
          "Stampa quotazione MIN/MAX assoluti",
          "Stampa quotazione MIN/MAX intervallo",
          "Bilanciamento"
      };
    
    LISTstocks stocks = LISTstocksInit();
    Stock s;
    Quote q;
    float f1, f2;
    char strTmp[100], strTmp1[100];
    int sel = 0;
    int endProg = 0;
    
    readFILE("F1.txt", stocks);
    readFILE("F2.txt", stocks);
    readFILE("F3.txt", stocks);
    
    do {
          printMenu(options, &sel);
          switch(sel){

              case 0:
                  endProg = 1;
                  break;

              case 1:
                  printf("Inserire nome file: ");
                  scanf("%s", strTmp);
                  readFILE(strTmp, stocks);
                  break;

              case 2:
                  LISTstocksPrint(stocks, stdout);
                  break;

              case 3:
                  printf("Inserire codice titolo: ");
                  scanf("%s", strTmp);
                  s = LISTstocksSearch(stocks, strTmp);
                  if (s != NULL)
                    printStock(stdout, s);
                  break;

              case 4:
                  printf("Inserire codice titolo: ");
                  scanf("%s", strTmp);
                  s = LISTstocksSearch(stocks, strTmp);
                  if (s != NULL) {
                    printf("Inserire data: ");
                    scanf("%s", strTmp);
                      printf("Inserire ora: ");
                      scanf("%s", strTmp1);
                    q = getQuoteStock(s, DATEload(strTmp, strTmp1));
                    QUOTEprint(stdout, q);
                  }
                  break;

              case 5:
                  printf("Inserire codice titolo: ");
                  scanf("%s", strTmp);
                  s = LISTstocksSearch(stocks, strTmp);
                  if (s != NULL)
                    printf("MIN = %f || MAX = %f\n", minAbsoluteStock(s), maxAbsoluteStock(s));
                  break;

        case 6:
                  printf("Inserire codice titolo: ");
                  scanf("%s", strTmp);
                  s = LISTstocksSearch(stocks, strTmp);
                  if (s != NULL) {
                    printf("Inserire data 1: ");
                    scanf("%s", strTmp);
                    printf("Inserire data 2: ");
                    scanf("%s", strTmp1);
                    minmaxRangeStock(s, DATEload(strTmp, "00:00"), DATEload(strTmp1, "00:00"), &f1, &f2);
                    printf("MIN = %f || MAX = %f\n", f1, f2);
                  }
                  break;

        case 7:
                  printf("Inserire codice titolo: ");
                  scanf("%s", strTmp);
                  s = LISTstocksSearch(stocks, strTmp);
                  if (s != NULL)
                    treeBalanceStock(s);
                  break;

              default:{
                  printf("Scelta non valida\n");
              } break;
          }
      } while(!endProg);
    
    return 0;
}

void readFILE (char *fn, LISTstocks stocks) {
    char ticker[LEN], date[DATELEN], time[TIMELEN];
    int quote = 0, qnt;
    float val;
    Stock s;
    FILE *fp = fopen(fn, "r");
    if (fp == NULL)
        return;
    
    while(fscanf(fp, "%s %d\n", ticker, &quote) == 2) {
        s = LISTstocksSearch(stocks, ticker);
        if (s == NULL) {
            s = newStock(ticker);
            LISTstocksInsert(s, stocks);
        }
        
        for (int i = 0; i < quote; i++) {
            fscanf(fp, "%s %s %f %d\n", date, time, &val, &qnt);
            insertTransactionStock(s, DATEload(date, time), val, qnt);
        }
    }
    
    fclose(fp);
    return;
}

void printMenu (char *options[], int *sel) {
    printf("\nMENU\n");
    for (int i = 0; i < N_OPT; i++)
        printf("%2d > %s\n", i, options[i]);
    scanf(" %d", sel);
}
