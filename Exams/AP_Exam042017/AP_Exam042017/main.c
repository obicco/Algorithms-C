//
//  main.c
//  AP_Exam042017
//
//  Created by Oskar Bich on 4/8/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW 4
#define COL 5
#define L 4
#define W 21

typedef struct node1 node1_t, *link1;
typedef struct node2 node2_t, *link2;

struct node1 {
    char *farmer;
    link2 product;
    link1 next;
};

struct node2 {
    char *product;
    link2 next;
};

int mat_search (char **mat, int r, int c, char *s);
int check (char **mat, int r, int c, int i, int j, char *s, int l);
node1_t *list_init_example(void);
node1_t *list_of_list_invert(node1_t *head1);
node1_t *newFarmer(char* farmer, link1 next, link2 product);
node2_t *newProduct(char* product, link2 next);
void agricoltoriVisit(node1_t* agricoltori);

int main(int argc, const char * argv[]) {
    node1_t *agricoltori = list_init_example(), *inv_agr = list_of_list_invert(agricoltori);
    char S[L] = "foo";
    char M[ROW][COL] = {
        {'x', 'f', 'o', 'o', 'x'},
        {'y', 'o', 'x', 'z', 'f'},
        {'x', 'o', '2', 'f', 'o'},
        {'g', '4', 'x', 'a', 'o'},
    };
    
    char **m = malloc(ROW*sizeof(char*));
    for(int i = 0; i < ROW; i++) {
        m[i] = malloc(COL*sizeof(char));
        for (int j = 0; j < COL; j++) {
            m[i][j] = M[i][j];
        }
    }
    
    agricoltoriVisit(agricoltori);
    printf("\n\n");
    agricoltoriVisit(inv_agr);
    
    char *s = malloc(L*sizeof(char));
    for (int i = 0; i < L; i++) s[i] = S[i];
    
    printf("Trovate %d ricorrenze\n", mat_search(m, ROW, COL, s));
    return 0;
}

int mat_search (char **mat, int r, int c, char *s) {
    int cnt = 0, l = (int) strlen(s);
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
                cnt += check(mat, r, c, i, j, s, l);
        }
    }
    return cnt;
}

int check (char **mat, int r, int c, int i, int j, char *s, int l) {
    int cnt = 0, k;
    if (l > r+i && l > c+j)
        return cnt;
    if (l <= r+i) {
        for (k = 0; k < l; k++) {
            if (mat[i+k][j] == s[k])
                continue;
            else break;
        }
        if (k == l)
            cnt++;
    }
    if (l <= c+j) {
        for (k = 0; k < l; k++) {
            if (mat[i][j+k] == s[k])
                continue;
            else break;
        }
        if (k == l)
            cnt++;
    }
    return cnt;
}

node1_t *list_init_example(void) {
    //farmer1-product5-product4-product2
    //farmer2-product2-product4-product3
    //farmer3-product5-product2
    node1_t* agricoltori = NULL;
    node2_t* product = NULL;
    
    // farmer3
    
    product = newProduct("product2", product);
    product = newProduct("product5", product);
    agricoltori = newFarmer("farmer3", NULL, product);
    
    product = NULL;
    
    // farmer2
    
    product = newProduct("product3", product);
    product = newProduct("product4", product);
    product = newProduct("product2", product);
    agricoltori = newFarmer("farmer2", agricoltori, product);
    
    product = NULL;
    
    // farmer1
    
    product = newProduct("product2", product);
    product = newProduct("product4", product);
    product = newProduct("product5", product);
    agricoltori = newFarmer("farmer1", agricoltori, product);
    
    return agricoltori;
}

node1_t *newFarmer(char* farmer, link1 next, link2 product) {
    node1_t *n = malloc(sizeof(*n));
    n->farmer = strdup(farmer);
    n->next = next;
    n->product = product;
    return n;
}

node2_t *newProduct(char* product, link2 next) {
    node2_t *n = malloc(sizeof(*n));
    n->product = strdup(product);
    n->next = next;
    return n;
}

void agricoltoriVisit(node1_t* agricoltori) {
    if (agricoltori == NULL) return;
    node2_t* product;
    printf("%s : ", agricoltori->farmer);
    for(product = agricoltori->product; product != NULL; product = product->next)
        printf("%s, ", product->product);
    printf("\n");
    agricoltoriVisit(agricoltori->next);
}

node1_t* productGet(node1_t* head, char* productName){
    if (head == NULL)
        return NULL;
    if (strcmp(head->farmer, productName) == 0)
        return head;
    return productGet(head->next, productName);
}

node1_t* farmerGet(node1_t* head, char* farmerName){
    if (head == NULL)
        return NULL;
    if (strcmp(head->farmer, farmerName) == 0)
        return head;
    return farmerGet(head->next, farmerName);
}

node1_t *list_of_list_invert(node1_t *head1) {
    node1_t *n = NULL, *tmp;
    
    for (node1_t *x = head1; x != NULL; x = x->next) {
        for (node2_t *y = x->product; y != NULL; y = y->next) {
            tmp = productGet(n, y->product);
            if (tmp == NULL)
                n = newFarmer(y->product, n, newProduct(x->farmer, NULL));
            else tmp->product = newProduct(x->farmer, n->product);
        }
    }
    return n;
}

