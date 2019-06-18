// iset.h
#include <stdbool.h>

struct iset;
typedef struct iset *isetp;

isetp iset_new();                 // create empty set
void iset_free(isetp s);          // free memory
bool iset_isempty(isetp s);       // test emptiness
bool iset_isin(isetp s, int e);   // e included in s?
int iset_max(isetp s);            // return max value
void iset_addelt(isetp s, int e); // add e to s
void iset_subelt(isetp s, int e); // remove e from s
isetp iset_union(isetp s, isetp q); // set union
