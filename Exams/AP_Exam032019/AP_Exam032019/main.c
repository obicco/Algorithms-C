//
//  main.c
//  AP_Exam032019
//
//  Created by Oskar Bich on 1/6/21.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node {
    char c;
    link next;
};

int **generateM(int n);
void printM(int **m, int n);
link purgeList(link head1);
link stringToList(char *s);
link newnode(void);
void printList(link head);

int main(int argc, const char * argv[]) {
    int n = 5, **m = generateM(n);
    printM(m, n);
    
    char s[18] = "ab(acg)be()a(xx)f";
    
    link head1 = stringToList(s);
    
    printf("\nLISTA INPUT\n");
    printList(head1);
    printf("\n\n");
    
    link head2 = purgeList(head1);
    
    printf("LISTA OUTPUT\n");
    printList(head2);
    printf("\n\n");

    return 0;
}

int **generateM(int n) {
    int **m = malloc(n*sizeof(*m));
    
    for (int i = 0; i < n; i++) {
        m[i] = malloc(n*sizeof(*m));
        for (int j = 0; j < n; j++) {
            m[i][j] = abs(j-i);
        }
    }
    return m;
}

void printM(int **m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j =0; j < n; j++) printf("%d ", m[i][j]);
        printf("\n");
    }
}

link newnode(void) {
    link x = malloc(sizeof(*x));
    x->c = ' ';
    x->next = NULL;
    return x;
}

link stringToList (char *s) {
    int i = 0;
    link head = newnode(), x = head;
    while(s[i] != '\0') {
        x->c = s[i];
        x->next = newnode();
        x = x->next;
        i++;
    }
    return head;
}

void printList(link head) {
    link curr = head;
    while (curr != NULL) {
        printf("%c", curr->c);
        curr = curr->next;
    }
}

link purgeList (link head1) {
    link head2 = newnode(), x = head2, curr = head1;
    int copy = 1;
    while (curr != NULL) {
        if (curr->c == ')')
            copy = 1;
        if (copy) {
            x->c = curr->c;
            x->next = newnode();
            x = x->next;
        }
        if (curr->c == '(') {
            copy = 0;
            x->c = '*';
            x->next = newnode();
            x = x->next;
        }
        curr = curr->next;
    }
    return head2;
}
