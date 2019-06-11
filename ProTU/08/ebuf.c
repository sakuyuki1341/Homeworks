#include <stdlib.h>
#include <string.h>
#include "ebuf.h"


struct line {
  struct line *prev, *next; char str[MAXSTR];
};

struct ebuf { struct line *head, *cur; };


ebufp ebuf_new() {
  ebufp r = (ebufp)malloc(sizeof(struct ebuf));
  r->head = (struct line*)malloc(sizeof(struct line));
  r->cur = r->head->next = r->head->prev = r->head;
  strcpy(r->head->str, "EOF"); return r;
}

bool ebuf_iseof(ebufp e) { return e->cur == e->head; }

bool ebuf_forward(ebufp e) {
  if(e->cur == e->head) { return false; }
  e->cur = e->cur->next; return true;
}

bool ebuf_backward(ebufp e) {
  if(e->cur->prev == e->head) { return false; }
  e->cur = e->cur->prev; return true;
}

void ebuf_top(ebufp e) { e->cur = e->head->next; }

char *ebuf_str(ebufp e) { return e->cur->str; }

void ebuf_insert(ebufp e, char *s) {
  struct line *p = (struct line*)malloc(sizeof(struct line));
  strncpy(p->str, s, MAXSTR); p->str[MAXSTR-1] = '\0';
  p->prev = e->cur->prev; p->next = e->cur;
  e->cur->prev->next = p; e->cur->prev = p;
}
