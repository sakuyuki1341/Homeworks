#include <stdbool.h>
struct iqueue;
typedef struct iqueue *iqueuep;
iqueuep iqueue_new(int size);
bool iqueue_isempty(iqueuep p);
bool iqueue_isfull(iqueuep p);
void iqueue_enq(iqueuep p, int v);
int iqueue_deq(iqueuep p);
