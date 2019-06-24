#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 80

typedef char *elementtype;

struct node {
    elementtype element;
    struct node *next;
};

typedef struct node *link;
typedef link list;
typedef link position;


list initlist(void) {
    list l;

    // add your code here
    n = (list)malloc(sizeof(struct node));
    n->next = NULL;

    return l;
}

position first(list l) {
    return l;
}

position next(list l, position p) {
    return p->next;
}

position end(list l) {
    list p = 
}

elementtype retrieve(list l, position p) {
    // add your code here
}

position find(list l, elementtype e) {
    // add your code here
}

void insert(list l, position p, elementtype e) {
    // add your code here
}

void printlist(list l) {
    position p;
    p = next(l,l);
    while (p) {
        printf("%s", (retrieve(l,p)));
        p = next(l,p);
    }
}

int main(void) {
    list university;
    position p, tmp;

    university = initlist();
    while(1) {
        char buf[MAXLENGTH+2];
        fgets(buf, sizeof(buf), stdin);
        if(buf[0] == '.') {
            break;
        }
        p = find(university, buf);
        insert(university, p, buf);
    }
    printlist(university);

    for (p=first(university); p; p=next(university,p)) {
        tmp = p;
        free(tmp);
    }
    return 0;
}


