#include <stdbool.h>

struct ideq;
typedef struct ideq *ideqp;
ideqp ideq_new(int size);
bool ideq_isempty(ideqp p);
bool ideq_isfull(ideqp p);
void ideq_unshift(ideqp p, int v);
int ideq_shift(ideqp p);
void ideq_push(ideqp p, int v);
int ideq_pop(ideqp p);
int ideq_count(ideqp p);
int ideq_op(ideqp p);
