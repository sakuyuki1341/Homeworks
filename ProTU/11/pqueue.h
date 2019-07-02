// pqueue.h --- int type queue interface
#include <stdbool.h>
struct pqueue;
typedef struct pqueue *pqueuep;
pqueuep pqueue_new(int size);
bool pqueue_isempty(pqueuep p);
bool pqueue_isfull(pqueuep p);
void pqueue_enq(pqueuep p, void *v);
void *pqueue_deq(pqueuep p);
