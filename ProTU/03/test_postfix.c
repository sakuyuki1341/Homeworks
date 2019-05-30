#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "istack.h"

//#define POSTFIX1
//#define POSTFIX2
#define POSTFIX3
//#define POSTFIX4

int operprec(int c) {
  switch(c) {
    case '+': case '-': return 1;
    case '*': case '/': case '%': return 2;
    case '^': return 3;
    case '(': case ')': return 4;
    default: return 0;
  }
}

void swap_back(char *u) {
  char save = *u;
  *u = *(u-1);
  *(u-1) = save;
} 

int pow_i(int a, int b) {
  int ret = a;
  for(int i = 0; i < b-1; i++) {
    ret *= a;
  }
  return ret;
}

void postfix1(char *t, char *u) {
  istackp s = istack_new(200);
  for(int i = 0; t[i] != '\0'; ++i) {
    char c = t[i];
    if(isdigit(c)) { *u++ = c; continue; }
    while(!istack_isempty(s) &&
          operprec(istack_top(s)) >= operprec(c)) {
      *u++ = istack_pop(s);
    }
    istack_push(s, c);
  }
  while(!istack_isempty(s)) { *u++ = istack_pop(s); }
  *u++ = '\0';
}

void postfix2(char *t, char *u) {
  istackp s = istack_new(200);
  for(int i = 0; t[i] != '\0'; ++i) {
    char c = t[i];
    if(isdigit(c)) { *u++ = c; continue; }
    while(!istack_isempty(s) &&
          operprec(istack_top(s)) > operprec(c)) {
      *u++ = istack_pop(s);
    }
    istack_push(s, c);
  }
  while(!istack_isempty(s)) { *u++ = istack_pop(s); }
  *u++ = '\0';
}

void postfix3(char *t, char *u) {
  istackp s = istack_new(200);
  for(int i = 0; t[i] != '\0'; ++i) {
    char c = t[i];
    if(isdigit(c)) { *u++ = c; continue; }
    if(c == '(') { 
      *u++ = c;
      istack_push(s, c);
      continue;
    }
    while(!istack_isempty(s) &&
          operprec(istack_top(s)) > operprec(c) && istack_top(s) != '(') {
      *u++ = istack_pop(s);
    }
    if(c == ')') {
      while(istack_top(s) != '(') {
        *u++ = istack_pop(s);
      }
      istack_pop(s);
      *u++ = c;
      continue;
    }
    istack_push(s, c);
  }
  while(!istack_isempty(s)) { *u++ = istack_pop(s); }
  *u++ = '\0';
}

void postfix4(char *t, char *u) {
  istackp s = istack_new(200);
  char buf[200];
  int a, b;
  postfix3(t, buf);
  for(int i = 0; buf[i] != '\0'; ++i) {
    char c = buf[i];
    switch(c) {
      case '+': break;
      case '-': break;
      case '*': break;
      case '/': break;
      case '%': break;
      case '^': break;
      case '(': break;
      case ')': break;
      default:
        buf[i] -= '0';
        break;
    }
  }
  for(int i = 0; buf[i] != '\0'; ++i) {
    char c = buf[i];
    switch(c) {
      case '+':
        a = istack_pop(s); b = istack_pop(s);
        istack_push(s, b+a);
        break;
      case '-':
        a = istack_pop(s); b = istack_pop(s);
        istack_push(s, b-a);
        break;
      case '*':
        a = istack_pop(s); b = istack_pop(s);
        istack_push(s, b*a);
        break;
      case '/':
        a = istack_pop(s); b = istack_pop(s);
        istack_push(s, b/a);
        break;
      case '%':
        a = istack_pop(s); b = istack_pop(s);
        istack_push(s, b%a);
        break;
      case '^':
        a = istack_pop(s); b = istack_pop(s);
        istack_push(s, pow_i(b,a));
        break;
      case '(':
        break;
      case ')':
        break;
      default:
        istack_push(s, c);
        break;
    }
    printf("stack_top = %d\n", istack_top(s));
  }
  int result = istack_pop(s);
  snprintf(u, 200, "%d", result);
}

void expect_str(char *s1, char *s2, char *msg) {
  printf("%s '%s':'%s' %s\n", strcmp(s1, s2)?"NG":"OK", s1, s2, msg);
}

int main(void) {
  char buf[200];
#ifdef POSTFIX1
  postfix1("1+2*3", buf); expect_str(buf, "123*+", "1+2*3 => 123*+");
  postfix1("2*3+1", buf); expect_str(buf, "23*1+", "2*3+1 => 23*1+");
  postfix1("2^3^4", buf); expect_str(buf, "23^4^", "2^3^4 => 23^4^");
#endif
#ifdef POSTFIX2
  postfix2("1+2*3", buf); expect_str(buf, "123*+", "1+2*3 => 123*+");
  postfix2("2^3^4", buf); expect_str(buf, "234^^", "2^3^4 => 234^^");
#endif
#ifdef POSTFIX3
  postfix3("1+2*3+4", buf); expect_str(buf, "123*4++", "1+2*3+4 => 123*4++");
  postfix3("1+2*(3+4)", buf); expect_str(buf, "12(34+)*+", "1+2*(3+4) => 12(34+)*+");
#endif
#ifdef POSTFIX4
  postfix4("2^3^2", buf); expect_str(buf, "512", "2^3^2 => 512");
  postfix4("1+2*(3+4)", buf); expect_str(buf, "15", "1+2*(3+4) => 15");
#endif
  return 0;
}
