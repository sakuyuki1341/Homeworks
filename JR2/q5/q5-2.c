#include <stdio.h>
#include <stdlib.h>

struct node{
    char element;
    struct node *next;
};

typedef struct node *nodep;

struct node *initlist() {
    struct node *n;

    // add your code here
    n = (nodep)malloc(sizeof(struct node));
    n->next = NULL;

    return n;
}

void insert(struct node *p, char x) {

    // add your code here
    nodep n = (nodep)malloc(sizeof(struct node));
    n->element = x;
    n->next = NULL;

    nodep q = p;
    for(; q->next != NULL;) {
        q = q->next;
    }
    q->next = n;

}

void printlist(struct node *p) {
    p = p->next;
    while (p) {
        putchar(p->element);
        p = p->next;
    }
    putchar('\n');
}

void halfchange(struct node *p) {

    // add your code here
    nodep q = p;
    nodep r = p;
    int num;
    for(num = 1; q->next != NULL; num++) {
        q = q->next;
    }
    if(num % 2 != 0) {
        num = num/2;
    } else {
        num = (num/2) -1;
    }
    for(; num > 0; num--) {
        r = r->next;
    }
    q->next = p->next;
    p->next = r->next;
    r->next = NULL;

}

int main(int argc, char *argv[]) {
    struct node *list, *head;
    char *p;

    if (argc<2)
        exit(-1);

    list = initlist();
    p = argv[1];
    for (; *p; p++) {
        insert(list, *p);
    }

    halfchange(list);
    printlist(list);

    for (; list; ) {
        head = list;
        list = list->next;
        free(head);
    }
    return 0;
}


