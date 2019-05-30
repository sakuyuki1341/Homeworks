#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "istack.h"

///ここで使用する関数とテストを選択する
///定義した変数の小文字の関数が実行される
//#define BALANCE1
//#define BALANCE2
//#define BALANCE3
#define BALANCE4
//#define BALANCE5

char *bool2str(bool b) { return b ? "true" : "false"; }

void expect_bool(bool b1, bool b2, char *msg) {
  printf("%s %s:%s %s\n", (b1==b2)?"OK":"NG", bool2str(b1), bool2str(b2), msg);
}

/*-------------------------------------------------------------*
 * 受け取った文字列の丸括弧がきちんと対応してるかを判定する関数.
 * 引数として文字配列の先頭アドレスを受け取る.
 * 戻り値はbool型で、対応していればtrueを、していなければfalse
 * を返す.
 *-------------------------------------------------------------*/
bool balance1(char *t) {
  istackp s = istack_new(200);
  for(int i = 0; t[i] != '\0'; ++i) {
    char c = t[i];
    if(c == '(') {
      istack_push(s, c);
    } else if(c == ')') {
      if(istack_isempty(s)) { return false; }
      istack_pop(s);
    }
  }
  return istack_isempty(s);
}

/*-------------------------------------------------------------*
 * 受け取った文字列の括弧が種類を気にせず対応しているかを
 * 判定する関数.
 * 引数として文字配列の先頭アドレスを受け取る、またこのアドレス
 * はcharポインタ型の変数tに代入する.
 * 戻り値はbool型で、対応していればtrueを、していなければfalse
 * を返す.
 *-------------------------------------------------------------*/
bool balance2(char *t) {
  istackp s = istack_new(200);
  for(int i = 0; t[i] != '\0'; ++i) {
    char c = t[i];
    if((c == '(') || (c == '[') || (c == '{')) {
      istack_push(s, c);
    } else if((c == ')') || (c == ']') || (c == '}')) {
      if(istack_isempty(s)) { return false; }
      istack_pop(s);
    }
  }
  return istack_isempty(s);
}

/*-------------------------------------------------------------*
 * 受け取った文字列の括弧が同じ種類の括弧で対応しているかを
 * 判定する関数.
 * 引数として文字配列の先頭アドレスを受け取る、またこのアドレス
 * はcharポインタ型の変数tに代入する.
 * 戻り値はbool型で、対応していればtrueを、していなければfalse
 * を返す.
 *-------------------------------------------------------------*/
bool balance3(char *t) {
  istackp s = istack_new(200);
  for(int i = 0; t[i] != '\0'; ++i) {
    char c = t[i];
    char top = istack_top(s);
    if((c == '(') || (c == '[') || (c == '{')) {
      istack_push(s, c);
    } else if(c == ')') {
      if(istack_isempty(s) || top != '(') { return false; }
      istack_pop(s);
    } else if(c == ']') {
      if(istack_isempty(s) || top != '[') { return false; }
      istack_pop(s);
    } else if(c == '}') {
      if(istack_isempty(s) || top != '{') { return false; }
      istack_pop(s);
    } 
  }
  return istack_isempty(s);
}

/*-------------------------------------------------------------*
 * 受け取った文字列の括弧が上記とことなり対応しているか否かを
 * 独立に対応をチェックする関数.
 * 引数として文字配列の先頭アドレスを受け取る、またこのアドレス
 * はcharポインタ型の変数tに代入する.
 * 戻り値はbool型で、対応していればtrueを、していなければfalse
 * を返す.
 *-------------------------------------------------------------*/
bool balance4(char *t) {
  istackp s = istack_new(200);
  istackp u = istack_new(200);
  istackp v = istack_new(200);
  for(int i = 0; t[i] != '\0'; ++i) {
    char c = t[i];
    if(c == '(') {
      istack_push(s, c);
    } else if(c == '[') {
      istack_push(u, c);
    } else if(c == '{') {
      istack_push(v, c);
    } else if(c == ')') {
      if(istack_isempty(s)) { return false; }
      istack_pop(s);
    } else if(c == ']') {
      if(istack_isempty(u)) { return false; }
      istack_pop(u);
    } else if(c == '}') {
      if(istack_isempty(v)) { return false; }
      istack_pop(v);
    }
  }
  return (istack_isempty(s) || istack_isempty(u) || istack_isempty(v));
}

/*-------------------------------------------------------------*
 * 受け取った文字列が種類を気にせず対応しているかを
 * 判定し、間違えがあった場合その位置が分かるようになる
 * 引数として文字配列の先頭アドレスを受け取る、またこのアドレス
 * はcharポインタ型の変数tに代入する.
 * 戻り値はbool型で、対応していればtrueを、していなければfalse
 * を返す.
 *-------------------------------------------------------------*/
bool balance5(char *t) {
  istackp s = istack_new(200);
  for(int i = 0; t[i] != '\0'; ++i) {
    char c = t[i];
    if((c == '(') || (c == '[') || (c == '{')) {
      istack_push(s, c);
    } else if((c == ')') || (c == ']') || (c == '}')) {
      if(istack_isempty(s)) {
        printf("%s\n", t);
        for(int j = 0; j < i; j++) {
          printf(" ");
        }
        printf("↑\n");
        return false;
      }
      istack_pop(s);
    }
  }
  if(istack_isempty(s)) {
    return true;
  } else {
    int len = strlen(t);
    printf("%s\n", t);
    for(int i = 0; i < len - 1; i++) {
      printf(" ");
    }
    printf("↑\n");
    return false;
  }
}

int main(void) {
#ifdef BALANCE1  
  expect_bool(balance1("((a)())"), true, "((a)())");
  expect_bool(balance1(")(a)()("), false, ")(a)()(");
  expect_bool(balance1("((a)()"), false, "((a)()");
  expect_bool(balance1("(a)())"), false, "(a)())");
  expect_bool(balance1("(((())))"), true, "(((())))");
#endif
#ifdef BALANCE2
  expect_bool(balance2("((a)}"), true, "((a)}");
  expect_bool(balance2("((a)]"), true, "((a)]");
  expect_bool(balance2("{(a))"), true, "{(a))");
  expect_bool(balance2("[(a))"), true, "[(a))");
  expect_bool(balance2("([a)}"), true, "([a)}");
  expect_bool(balance2("({(a)}"), false, "({(a)}");
  expect_bool(balance2("((a)}()}]"), false, "((a)}()}]");
#endif
#ifdef BALANCE3
  expect_bool(balance3("{[]}"), true, "{[]}");
  expect_bool(balance3("{{}}[]"), true, "{{}}[]");
  expect_bool(balance3("[(a)]"), true, "[(a)]");
  expect_bool(balance3("([a)}"), false, "([a)}");
  expect_bool(balance3("({(a)}"), false, "({(a)}");
  expect_bool(balance3("((a)}()}]"), false, "((a)}()}]");
#endif
#ifdef BALANCE4
  expect_bool(balance4("[(])"), true, "[(])");
  expect_bool(balance4("[{)]"), false, "[{)]");
  expect_bool(balance4("{[a}]"), true, "{[a}]");
  expect_bool(balance4("([{a)}(}]"), false, "([{a)}(}]");
  expect_bool(balance4("([{)]}"), true, "([{)]}");
#endif
#ifdef BALANCE5
  expect_bool(balance5("((a)}"), true, "((a)}");
  expect_bool(balance5("({[a()"), false, "({[a()");
  expect_bool(balance5("([a)}"), true, "([a)}");
  expect_bool(balance5("({(a)}"), false, "({(a)}");
  expect_bool(balance5("((a)}()}]"), false, "((a)}()}]");
#endif 
  return 0;
}
