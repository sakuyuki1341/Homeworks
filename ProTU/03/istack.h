#include <stdbool.h>

struct istack;
typedef struct istack *istackp;
istackp istack_new(int size);
bool istack_isempty(istackp p);
void istack_push(istackp p, int v);
int istack_pop(istackp p);
int istack_top(istackp p);
