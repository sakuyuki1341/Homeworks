#include <stdbool.h>
struct istack;
typedef struct istack *istackp;
istackp istack_new(int size); // allocate new stack
bool istack_isempty(istackp p); // test if the stack is empty
void istack_push(istackp p, int v); // push a value
int istack_pop(istackp p);      // pop a value and return it
int istack_top(istackp p);      // peek the topmost value
