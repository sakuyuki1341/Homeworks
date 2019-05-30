#include <stdlib.h>
#include "ideq.h"
#include <string.h>

struct ideq { int ip, op, size, count; int *arr; };

ideqp ideq_new(int size) {
  ideqp p = (ideqp)malloc(sizeof(struct ideq));
  p->ip = p->op = p->count = 0; p->size = size;
  p->arr = (int*)malloc(size * sizeof(int)); return p;
}

bool ideq_isempty(ideqp p) { return p->count == 0; }

bool ideq_isfull(ideqp p) { return p->count == p->size; }

void ideq_push(ideqp p, int v) {
  if(ideq_isfull(p)) {
    int *arr_new = (int*)malloc((p->size + 1) * sizeof(int));
    for(int i = 0; i < p->size; i++) {
      arr_new[i] = p->arr[p->op++];
      if(p->op >= p->size) { p->op = 0; }
    }
    p->arr = arr_new;
    p->size += 1;
    p->op = 0;
    p->ip = p->size - 1;
  }
  p->arr[p->ip++] = v;
  if(p->ip >= p->size) { p->ip = 0; }
  p->count += 1;
}

int ideq_shift(ideqp p) {
  if(ideq_isempty(p)) { return 0; }
  int v = p->arr[p->op++];
  if(p->op >= p->size) { p->op = 0; }
  p->count -= 1;
  return v;
}

void ideq_unshift(ideqp p, int v){
  if(ideq_isfull(p)) {
    int *arr_new = (int*)malloc((p->size + 1) * sizeof(int));
    for(int i = 0; i < p->size; i++) {
      arr_new[i] = p->arr[p->op++];
      if(p->op >= p->size) { p->op = 0; }
    }
    p->arr = arr_new;
    p->size += 1;
    p->op = 0;
    p->ip = p->size - 1;
  }
  if(p->op - 1 < 0) {
    p->op = p->size; 
  }
  p->op -= 1; p->arr[p->op] = v;
  p->count += 1;

}

int ideq_pop(ideqp p){
  if(ideq_isempty(p)) { return 0; }
  if(p->ip - 1 < 0) {
    p->ip = p->size;
  }
  p->ip -= 1; int v = p->arr[p->ip];
  p->count -= 1;
  return v;
}

int ideq_count(ideqp p) {
  return p->count;
}

int ideq_op(ideqp p) {
  if(ideq_isempty(p)) {
    return 0;
  }
  return p->arr[p->op];
}

