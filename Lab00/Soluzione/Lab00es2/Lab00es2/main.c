//
//  main.c
//  Lab00es2
//
//  Created by Oskar Bich on 22/10/2020.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 21

int conta(char S[N], int n);
int vocale(char c);

int main(int argc, const char * argv[]) {
    int dim, l;
    char fname[N], row[N];
    FILE *fp;
    printf("Inserire nome file e dimensione sottovettore:\n");
    scanf("%s %d", fname, &l);
    
    fp = fopen(fname, "r");
    fscanf(fp, "%d", &dim);
    for (int i = 0; i < dim; i++) {
        fscanf(fp, "%s", row);
        printf("%s --> %d\n", row, conta(row, l));
    }
    
    fclose(fp);
    //printf("\nNome file: %s", fname);
    return 0;
}

int conta(char S[N], int n) {
    int cnt, len = strlen(S), tcnt = 0;
    for( int i = 0; i <= len-n; i++) {
      cnt = 0;
      for(int j = i; j < i+n; j++) {
        if (vocale(S[j]))
          cnt++;
      }
      if (cnt == 2) {
        tcnt++;
      }
    }
    return tcnt;
}

int vocale(char c) {
  c = tolower(c);
  return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u');
}
