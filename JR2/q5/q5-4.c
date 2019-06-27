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
    l = (list)malloc(sizeof(struct node));
    l->next = NULL;

    return l;
}

position first(list l) {
    // add your code here
    return l->next;
}

position next(list l, position p) {
    // add your code here
    return p->next;
}

position end(list l) {
    // add your code here
    for(; l->next != NULL; l = l->next){
        // do nothing
    }
    return l;
}

elementtype retrieve(list l, position p) {
    // add your code here
    return p->element;
}

position find(list l, elementtype e) {
    // add your code here
    position p = l;
    for(; p->next != NULL; ) {
        char* pn_ele =p->next->element;
        for(int i = 0; e[i]!='\n'; i++) {
            if(pn_ele[i] < e[i] || pn_ele[i] == '\n') {
                break;
            } else if(pn_ele[i] == e[i]) {
                continue;
            }
            return p;
        }
        p = next(l,p);
    }
    return p;
}

void insert(list l, position p, elementtype e) {
    // add your code here
    list n = initlist();
    n->element = e;
    n->next = p->next;
    p->next = n;
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
