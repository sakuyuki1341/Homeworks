
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char elementtype;

typedef struct _node {
    elementtype element;
    struct _node * next;
}  node;

node* initList(){
    node * n;
    n = (node*) malloc(sizeof(node));
    n->next = NULL;
    return n;
}

node* newNode(elementtype e){
    node* n = (node*)malloc(sizeof(node));
    n->element = e;
    n->next = NULL;
    return n;
}

node* buildList(char *p) {
    node * h = initList();
    node * n = h;
    while (*p) {
        n->next = newNode(*p++);
        n = n->next;
    }
    return h;
}

void freeList(node* list) {
    node *head;
    for (; list; ) {
        head = list;
        list = list->next;
        free(head);
    }
}

bool

int findMaxRemoval(node *head){

    // add your code here
    elementtype now;
    node* here = head;
    int count = 0;
    // 中央部削除
    for(int i = 0; here->next != NULL; i++) {
        now =
    }
    return count;
}

int main(int argc, char *argv[]){
    if (argc<2)
        exit(-1);

    node *head = buildList(argv[1]);
    int m = findMaxRemoval(head);
    printf("%d\n",m);
    freeList(head);
    return 0;
}
