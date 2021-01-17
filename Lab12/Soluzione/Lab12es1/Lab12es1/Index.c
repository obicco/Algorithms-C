//
//  Index.c
//  Lab12es1
//
//  Created by Oskar Bich on 16/01/21.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Index.h"

typedef struct node_ {
    struct node_ *l, *r;
    Quote q;
    int cnt;
} node;

typedef node* link;

struct BSTindex_ {
    link root;
    int count;
};

BSTindex BSTindexInit(void) {
    BSTindex i = calloc(1, sizeof(*i));
    return i;
}

int BSTindexEmpty(BSTindex index) {
    if (index == NULL || index->count == 0)
        return 1;
    return 0;
}

Quote searchR (link h, Date d) {
    if (h == NULL)
        return QUOTEsetNull();
    int cmp = DATEcmp(d, QUOTEgetDate(h->q));
    if (cmp == 0)
        return h->q;
    else if(cmp < 0)
        return searchR(h->l, d);
    else
        return searchR(h->r, d);
}

Quote BSTindexSearch(BSTindex index, Date d) {
    return searchR(index->root, d);
}

static link NEW (Date d, float val, int qnt, link left, link right) {
    link l = calloc(1, sizeof(*l));
    l->q.date = d;
    l->q.val = val * qnt;
    l->q.qnt = qnt;
    l->l = left;
    l->r = right;
    l->cnt = 1;
    return l;
}

void minmax (link h, float *min, float *max) {
    float q = QUOTEgetValue(h->q);
    if (h == NULL)
        return;;
    if (*min < 0 || *min > q)
        *min = q;
    if (*max < 0 || *max < q)
        *max = q;
    if (h->r)
        minmax(h->r, min, max);
    if (h->l)
        minmax(h->l, min, max);
}

void BSTgetMinMax(BSTindex index, float *min, float *max) {
    if (BSTindexEmpty(index))
        return;
    minmax(index->root, min, max);
}

link insertR (link h, Date d, float val, int qnt, int *add) {
    link n;
    if (h == NULL) {
        *add = 1;
        n = NEW(d, val, qnt, NULL, NULL);
        return n;
    }
    int cmp = DATEcmp(d, QUOTEgetDate(h->q));
    if (cmp < 0) {
        h->l = insertR(h->l, d, val, qnt, add);
    } else if (cmp > 0) {
        h->r = insertR(h->r, d, val, qnt, add);
    }
    else {
        h->q.val += (h->q.val + qnt * val);
        h->q.qnt += qnt;
    }
    if (*add) h->cnt++;
    return h;
}

void BSTindexInsert(BSTindex index, Date d, float val, int qnt) {
    int add = 0;
    index->root = insertR(index->root, d, val, qnt, &add);
    if (add) index->count++;
    return;
}

void treePrint(link h, FILE *fp) {
    if (h == NULL)
        return;
    
    treePrint(h->l, fp);
    QUOTEprint(fp, h->q);
    treePrint(h->r, fp);
}

void  treeMinmaxRange(link r, Date d1, Date d2, float *f1, float *f2) {
  int cmp1 = DATEcmp(d1, QUOTEgetDate(r->q));
  int cmp2 = DATEcmp(d2, QUOTEgetDate(r->q));
  float qv;
  if (r == NULL)
    return;
  if (cmp1 < 0)
    treeMinmaxRange(r->l, d1, d2, f1, f2);
  if (cmp2 > 0)
    treeMinmaxRange(r->r, d1, d2, f1, f2);
  if (cmp1 <= 0 && cmp2 >= 0) {
    qv = QUOTEgetValue(r->q);
    if (*f1 < 0 || *f1 > qv)
      *f1 = qv;
    if (*f2 < 0 || *f2 < qv)
      *f2 = qv;
  }
}

void BSTindexMinmaxRange(BSTindex index, Date d1, Date d2, float *f1, float *f2) {
    if (index == NULL || index->root == NULL || index->count == 0)
        return;
    treeMinmaxRange(index->root, d1, d2, f1, f2);
}

void BSTindexPrint(BSTindex index, FILE *fp) {
    if (BSTindexEmpty(index))
        return;
    treePrint(index->root, fp);
}

int treeMinmaxHeight(link h, int *max, int depth) {
  int min_l, min_r;
  if (h == NULL)
    return 0;
  if (h->l == NULL && h->r == NULL) {
    if (depth > *max)
      *max = depth;
    return 1;
  }
  min_l = treeMinmaxHeight(h->l, max, depth+1);
  min_r = treeMinmaxHeight(h->r, max, depth+1);
  if (h->l == NULL)
    return min_r+1;
  if (h->r == NULL)
    return min_l+1;
  return (min_l < min_r) ? min_l+1 : min_r+1;
}

link rotR(link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  x->cnt = h->cnt;
  h->cnt = 1;
  h->cnt += (h->l) ? h->l->cnt : 0;
  h->cnt += (h->r) ? h->r->cnt : 0;
  return x;
}

link rotL(link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  x->cnt = h->cnt;
  h->cnt = 1;
  h->cnt += (h->l) ? h->l->cnt : 0;
  h->cnt += (h->r) ? h->r->cnt : 0;
  return x;
}

static link treePartition(link h, int k) {
  int t = (h->l) ? h->l->cnt : 0;
  if (h == NULL)
    return NULL;
  if (t > k) {
    h->l = treePartition(h->l, k);
    h = rotR(h);
  }
  if (t < k) {
    h->r = treePartition(h->r, k-t-1);
    h = rotL(h);
  }
  return h;
}

static void treeBalance(BSTindex index) {
  int k = (index->count+1)/2-1;
  index->root = treePartition(index->root, k);
}

void BSTindexBalance(BSTindex index) {
    int min = -1, max = -1;
    if (BSTindexEmpty(index))
        return;
    min = treeMinmaxHeight(index->root, &max, 1);
    if (index->root && (index->root->l == NULL || index->root->r == NULL))
        min = 0;
    if (min == 0 || (max / (float) min) > S) {
        printf("Pre-bilanciamento min_path = %d max_path = %d\n", min, max);
        treeBalance(index);
        min = max = -1;
        min = treeMinmaxHeight(index->root, &max, 1);
        printf("Post-bilanciamento min_path = %d max_path = %d\n", min, max);
    }
}

