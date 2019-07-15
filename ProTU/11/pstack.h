// pstack.h --- pointer type stack interface
#include <stdbool.h>
struct pstack;
typedef struct pstack *pstackp;
pstackp pstack_new(int size);
bool pstack_isempty(pstackp p);
bool pstack_isfull(pstackp p);
void pstack_push(pstackp p, void *v);
void *pstack_pop(pstackp p);
void *pstack_top(pstackp p);
