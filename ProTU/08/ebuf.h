#include <stdbool.h>

#define MAXSTR 100

struct ebuf;
typedef struct ebuf *ebufp;

ebufp ebuf_new();            // create ebuf
bool ebuf_iseof(ebufp e);    // see if current line is EOF
bool ebuf_forward(ebufp e);  // forward 1 line
bool ebuf_backward(ebufp e); // backward 1 line
void ebuf_top(ebufp e);      // go to top
char *ebuf_str(ebufp e);    // obtain current line string 
void ebuf_insert(ebufp e, char *s); // insert a line
