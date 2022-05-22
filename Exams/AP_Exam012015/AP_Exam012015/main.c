//
//  main.c
//  AP_Exam012015
//
//  Created by Oskar Bich on 14/5/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2

struct node {
    int key;
    struct node *children[N];
} node;

typedef struct node* LINK;

typedef struct{
  char *s;
  int dim_s;
} row;

int findRow(int pos,row *val,char *sol,int dim_sol,int n_sol);

void visitLevelbyLevel (struct node* root, int l1, int l2);
void print_deep(struct node* root, int deep_nec, int deep_act);

void eraseDuplicate (char *str);
void printStr (char *str, int n);

int main(int argc, const char * argv[]) {
    char str[] = "aa;;;bbbab;";
    eraseDuplicate(str);
    return 0;
}

void eraseDuplicate (char *str) {
    int n = (int) strlen(str), cnt = 0, j, end;
    char dup[n];
    
    for (int i = 0; i < n; i++) {
        j = 0;
        end = 0;
        while (j != cnt && !end) {
            if (str[i] == dup[j])
                end = 1;
            j++;
        }
        if (!end)
            dup[cnt++] = str[i];
    }
    printStr(dup, cnt);
}

void printStr (char *str, int n) {
    for (int i = 0; i < n; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

void visitLevelbyLevel (struct node* root, int l1, int l2) {
    for (int i = l1; i <= l2; i++) print_deep(root, i, 0);
}
void print_deep(struct node* root, int deep_nec, int deep_act) {
    if (root == NULL)
        return;
    if (deep_nec == deep_act) {
        printf("%d", root->key);
        return;
    }
    for (int i = 0; i < N; i++) print_deep(root->children[i], deep_nec, deep_act+1);
}

int findRow(int pos,row *val,char *sol,int dim_sol,int n_sol){
  if(pos >= dim_sol){
      for(int i = 0; i <= pos; i++){
          printf("%c",sol[i]);
          }
      printf("\n");
      return n_sol+1;
      }
  for(int i = 0; i < val[pos].dim_s; i++){
      sol[pos] = val[pos].s[i];
      n_sol = findRow(pos+1,val,sol,dim_sol,n_sol);
      }
  return n_sol;
}
