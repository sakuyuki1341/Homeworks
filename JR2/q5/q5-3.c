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

void remove_1st(struct node *p) {

    // add your code here
    char del = p->next->element;
    nodep q = p;
    for(; q->next != NULL;) {
        if(q->next->element == del) {
            q->next = q->next->next;
        } else {
            q = q->next;
        }
    }
}

int main(int argc, char *argv[]) {
    struct node *list, *head;
    char *p;

    if (argc<2)
        exit(-1);

    list = initlist();
    p = argv[1];
    for (; *p; p++)
        insert(list, *p);

    remove_1st(list);
    printlist(list);

    for (; list; ) {
        head = list;
        list = list->next;
        free(head);
    }
    return 0;
}

