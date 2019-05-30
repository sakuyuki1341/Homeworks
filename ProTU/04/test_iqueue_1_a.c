#include <stdbool.h>
#include <stdio.h>
#include "iqueue_1_a.h"

//#define ENSHU_A
//#define ENSHU_B
//#define ENSHU_C
#define ENSHU_D

char *bool2str(bool b) { return b ? "true" : "false"; }

void expect_bool(bool b1, bool b2, char *msg) {
  printf("%s %s:%s %s\n", (b1==b2)?"OK":"NG",
         bool2str(b1), bool2str(b2), msg);
}

void expect_int(int i1, int i2, char *msg) {
  printf("%s %d:%d %s\n", (i1==i2)?"OK":"NG", i1, i2, msg);
}

int main(void) {
#ifdef ENSHU_A
  iqueuep q = iqueue_new(4);
  iqueue_enq(q, 1); iqueue_enq(q, 2); iqueue_enq(q, 3);
  expect_bool(iqueue_isfull(q), false, "queue not full");
  expect_int(iqueue_count(q), 3, "count=3");
  iqueue_enq(q, 4);
  expect_bool(iqueue_isfull(q), true, "queue full");
  expect_int(iqueue_count(q), 4, "count=4");
  expect_int(iqueue_deq(q), 1, "1st => 1");
  expect_int(iqueue_deq(q), 2, "2nd => 2");
  expect_int(iqueue_deq(q), 3, "3rd => 3");
  expect_int(iqueue_deq(q), 4, "4th => 4");
  expect_bool(iqueue_isempty(q), true, "queue emptied");
#endif
#ifdef ENSHU_B
  iqueuep q = iqueue_new(4);
  iqueue_enq(q, 1); iqueue_enq(q, 2); iqueue_enq(q, 3);
  expect_int(iqueue_op(q), 1, "op => 1");
  expect_bool(iqueue_isfull(q), false, "queue not full");
  expect_int(iqueue_count(q), 3, "count=3");
  iqueue_enq(q, 4);
  expect_bool(iqueue_isfull(q), true, "queue full");
  expect_int(iqueue_count(q), 4, "count=4");
  expect_int(iqueue_deq(q), 1, "1st => 1");
  expect_int(iqueue_deq(q), 2, "2nd => 2");
  expect_int(iqueue_deq(q), 3, "3rd => 3");
  expect_int(iqueue_deq(q), 4, "4th => 4");
  expect_bool(iqueue_isempty(q), true, "queue emptied");
  expect_int(iqueue_op(q), 0, "op => NULL(0)");
#endif
#ifdef ENSHU_C 
  iqueuep q = iqueue_new(4);
  iqueue_enq(q, 1); iqueue_enq(q, 2); iqueue_enq(q, 3);
  expect_int(iqueue_op(q), 1, "op => 1");
  expect_bool(iqueue_isfull(q), false, "queue not full");
  expect_int(iqueue_count(q), 3, "count=3");
  iqueue_enq(q, 4);
  expect_bool(iqueue_isfull(q), true, "queue full");
  iqueue_enq(q, 5); iqueue_enq(q, 6);
  expect_int(iqueue_count(q), 4, "count=4");
  expect_int(iqueue_deq(q), 3, "1st => 3");
  expect_int(iqueue_deq(q), 4, "2nd => 4");
  expect_int(iqueue_deq(q), 5, "3rd => 5");
  expect_int(iqueue_deq(q), 6, "4th => 6");
  expect_bool(iqueue_isempty(q), true, "queue emptied");
  expect_int(iqueue_op(q), 0, "op => NULL(0)");
#endif
#ifdef ENSHU_D
  iqueuep q = iqueue_new(4);
  iqueue_enq(q, 1); iqueue_enq(q, 2); iqueue_enq(q, 3);
  expect_int(iqueue_op(q), 1, "op => 1");
  expect_bool(iqueue_isfull(q), false, "queue not full");
  expect_int(iqueue_count(q), 3, "count=3");
  iqueue_enq(q, 4);
  expect_bool(iqueue_isfull(q), true, "queue full");
  iqueue_enq(q, 5); iqueue_enq(q, 6);
  expect_int(iqueue_count(q), 6, "count=6");
  expect_int(iqueue_deq(q), 1, "1st => 1");
  expect_int(iqueue_deq(q), 2, "2nd => 2");
  expect_int(iqueue_deq(q), 3, "3rd => 3");
  expect_int(iqueue_deq(q), 4, "4th => 4");
  expect_int(iqueue_deq(q), 5, "5th => 5");
  expect_int(iqueue_deq(q), 6, "6hh => 6");
  expect_bool(iqueue_isempty(q), true, "queue emptied");
  expect_int(iqueue_op(q), 0, "op => NULL(0)");
#endif
  return 0;
}
