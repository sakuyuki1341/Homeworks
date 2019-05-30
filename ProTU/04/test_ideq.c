#include <stdbool.h>
#include <stdio.h>
#include "ideq.h"

char *bool2str(bool b) { return b ? "true" : "false"; }

void expect_bool(bool b1, bool b2, char *msg) {
  printf("%s %s:%s %s\n", (b1==b2)?"OK":"NG",
         bool2str(b1), bool2str(b2), msg);
}

void expect_int(int i1, int i2, char *msg) {
  printf("%s %d:%d %s\n", (i1==i2)?"OK":"NG", i1, i2, msg);
}

int main(void) {
  // デックの宣言
  ideqp q = ideq_new(4);
  // スタックの確かめ
  ideq_push(q, 1); ideq_push(q, 2); ideq_push(q, 3);
  expect_bool(ideq_isfull(q), false, "deq not full");
  expect_int(ideq_count(q), 3, "count=3");
  ideq_push(q, 4);
  expect_bool(ideq_isfull(q), true, "deq full");
  ideq_push(q, 5);
  expect_int(ideq_pop(q), 5, "last in => 5");
  expect_int(ideq_pop(q), 4, "last in => 4");
  expect_int(ideq_pop(q), 3, "last in => 3");
  expect_int(ideq_pop(q), 2, "last in => 2");
  expect_int(ideq_pop(q), 1, "last in => 1");
  expect_bool(ideq_isempty(q), true, "dec emptied");
  //ここからキューの確かめ
  ideq_push(q, 1); ideq_push(q, 2); ideq_push(q, 3);
  expect_bool(ideq_isfull(q), false, "deq not full");
  expect_int(ideq_count(q), 3, "count=3");
  ideq_push(q, 4); ideq_push(q, 5);
  expect_int(ideq_shift(q), 1, "1st => 1");
  expect_int(ideq_shift(q), 2, "2nd => 2");
  expect_int(ideq_shift(q), 3, "3rd => 3");
  expect_int(ideq_shift(q), 4, "4th => 4");
  expect_int(ideq_shift(q), 5, "5th => 5");
  expect_bool(ideq_isempty(q), true, "dec emptied");
  return 0;
}
