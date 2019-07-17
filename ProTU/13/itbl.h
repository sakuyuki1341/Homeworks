// itbl.h --- int table api.
struct itbl;
typedef struct itbl *itblp;
itblp itbl_new();                     // allocate new tbl
void itbl_put(itblp t, int k, int v); // store value
int itbl_get(itblp t, int k);         // obtain value
//void itbl_delete(itblp t, int k);     // delete key/value
void itbl_pr(itblp t);                // print contents
