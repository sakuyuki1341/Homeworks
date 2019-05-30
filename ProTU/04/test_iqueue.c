#include <stdbool.h>
#include <stdio.h>
#include "iqueue.h"

#define ENSHU_1

char *bool2str(bool b) { return b ? "true" : "false"; }

void expect_bool(bool b1, bool b2, char *msg) {
  printf("%s %s:%s %s\n", (b1==b2)?"OK":"NG",
         bool2str(b1), bool2str(b2), msg);
}

void expect_int(int i1, int i2, char *msg) {
  printf("%s %d:%d %s\n", (i1==i2)?"OK":"NG", i1, i2, msg);
}

int main(void) {
#ifdef ENSHU_1
  iqueuep q = iqueue_new(4);
  iqueue_enq(q, 1); iqueue_enq(q, 2); iqueue_enq(q, 3);
  expect_bool(iqueue_isfull(q), true, "size=4 queue full");
  iqueue_enq(q, 4);
  expect_int(iqueue_deq(q), 1, "1st => 1");
  iqueue_enq(q, 5);
  expect_int(iqueue_deq(q), 2, "2nd => 2");
  expect_int(iqueue_deq(q), 3, "3rd => 3");
  expect_bool(iqueue_isempty(q), false, "queue not empty");
  expect_int(iqueue_deq(q), 5, "4th => 5");
  expect_bool(iqueue_isempty(q), true, "queue emptied");
  expect_int(iqueue_deq(q), 0, "0 returned for empty");
  return 0;
#endif

}
