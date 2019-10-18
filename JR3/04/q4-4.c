/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAXSTACK 128

// マクロでは無いがここで記述
typedef char elementtype;

/************************************************
 * 構造体宣言部
 ************************************************/
typedef struct stack {
    int top;    // 最後に入れた要素の位置, 空なら-1
    elementtype contents[MAXSTACK]; // 要素を入れる配列
} stack;

/************************************************
 * グローバル変数
 ************************************************/
char buf[1024];  // 標準入力保存

/************************************************
 * プロトタイプ宣言部
 ************************************************/
// スタックのアドレスを受け取り、そのスタックを空にする
void initstack(stack *p);

// スタックのアドレスを受け取り、それが空なら1、空でないなら0を返す
int stackempty(stack *p);

// スタックのアドレスを受け取り、そのスタックにポップをし、その要素を返す
elementtype pop(stack *p);

// スタックのアドレスと要素を受け取り、スタックに要素をプッシュする
void push(stack *p, elementtype e);

// スタックのアドレスを受け取り、そのスタックの中身を[]で囲って順に出力
// elementtypeを変更した際は要注意
void stack_printer(stack *p);

/************************************************
 * 関数部
 ************************************************/
int main(int argc, char const *argv[]) {
    stack s;    // スタック用意
    initstack(&s);  // スタックの初期化
    // 標準入力受け取り
    fgets(buf, sizeof(buf), stdin);

    // 全ての文字を参照していく
    for(int i = 0; i < (int)strlen(buf); i++) {
        // bufの変更を回避のため
        const char tmp = buf[i];

        // 左括弧か右括弧で分岐
        if(tmp == '(' || tmp == '[' || tmp == '{' || tmp == '<') {
            push(&s, tmp);  // スタックに左括弧を格納
        } else if(tmp == ')' || tmp == ']' || tmp == '}' || tmp == '>') {
            char cmp = pop(&s); // スタックから左括弧を取り出し
            printf("%c\n", cmp);
            // 括弧が対応するか判定
            // 失敗なら異常終了
            switch (cmp) {
                case '(':
                    if(tmp != ')') {
                        printf("Bad.\n");
                        exit(1);
                    }
                    break;
                case '[':
                    if(tmp != ']') {
                        printf("Bad.\n");
                        exit(1);
                    }
                    break;
                case '{':
                    if(tmp != '}') {
                        printf("Bad.\n");
                        exit(1);
                    }
                    break;
                case '<':
                    if(tmp != '>') {
                        printf("Bad.\n");
                        exit(1);
                    }
            }
        }
    }

    // 閉じきっていない括弧があるかどうか
    if(stackempty(&s)) {
        printf("-1");
        printf("Bad.\n");
        exit(1);
    }

    // 全て確認して問題なければGoodを表示して終了
    printf("Good.\n");

    return 0;
}

void initstack(stack *p) {
    p->top = -1;    // 初期化時スタックは空
}

int stackempty(stack *p) {
    if(p->top == -1) {
        return 1;
    } else {
        return 0;
    }
}

elementtype pop(stack *p) {
    if(stackempty(p)) {
        // 空の場合、文を表示して異常終了
        printf("Bad.\n");
        exit(1);
    } else {
        return p->contents[p->top--];  // 先頭要素を返した後、先頭を下げる
    }
}

void push(stack *p, elementtype e) {
    if(p->top == MAXSTACK) {
        // 要素が入れられない場合、文を表示して異常終了
        printf("Bad.\n");
        exit(1);
    } else {
        p->contents[++p->top] = e; // 要素の追加
    }
}

void stack_printer(stack *p) {
    // 最後に入れられた要素まで順に表示
    for(int i = 0; i <= p->top; i++) {
        printf("[%d]", p->contents[i]);
    }
    printf("\n");   // 表示後最後に改行
}
