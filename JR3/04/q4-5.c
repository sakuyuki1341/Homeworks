/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAXSTACK 128
#define N 11

/************************************************
 * 構造体宣言部
 ************************************************/
typedef struct zahyo {
    int x;
    int y;
} zahyo;

// 構造体では無いがここで記述
typedef zahyo elementtype;

typedef struct stack {
    int top;    // 最後に入れた要素の位置, 空なら-1
    elementtype contents[MAXSTACK]; // 要素を入れる配列
} stack;

/************************************************
 * グローバル変数
 ************************************************/
char buf[N+2];  // 標準入力保存
char canvas[N][N];  // 最終入力保存先

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

// もし与えられた座標が空白なら、スタックに座標をプッシュして、
// その座標に'.'を入れる
void next_coordinate(stack *p, zahyo e);

/************************************************
 * 関数部
 ************************************************/
int main(int argc, char const *argv[]) {
    int i, j;
    i = 0;
    // 入力を1行ずつ読み込んでcanvasへ格納
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        for(j = 0; j < N; j++) {
            canvas[i][j] = buf[j];
        }
        i++;
    }

    stack s;    // スタック用意
    initstack(&s);  // スタックの初期化
    // 中央をプッシュ
    zahyo center = {N/2, N/2};
    push(&s, center);

    // 周囲の' 'がなくなるまで'.'で埋め尽くす
    while(stackempty(&s) != 1) {
        // 座標取り出し
        zahyo tmp = pop(&s);
        // 次の座標を関数に引き渡し
        zahyo surroundigs[4] = {
            {tmp.x, tmp.y + 1}, // up
            {tmp.x, tmp.y - 1}, // down
            {tmp.x - 1, tmp.y}, // left
            {tmp.x + 1, tmp.y}  // right
        };
        for(i = 0; i < 4; i++) {
            // canvasで宣言された範囲外の場合とばす
            if(surroundigs[i].x < 0 || 10 < surroundigs[i].x || surroundigs[i].y < 0 || 10 < surroundigs[i].y) {
                continue;
            }
            next_coordinate(&s, surroundigs[i]);
        }
    }

    // スタート地点を埋める
    canvas[N/2][N/2] = '.';

    // canvasを表示
    for(i = 0; i < 11; i++) {
        for(j = 0; j < 11; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }

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
        printf("Underflow\n");
        exit(1);
    } else {
        return p->contents[p->top--];  // 先頭要素を返した後、先頭を下げる
    }
}

void push(stack *p, elementtype e) {
    if(p->top == MAXSTACK) {
        // 要素が入れられない場合、文を表示して異常終了
        printf("Overflow\n");
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

void next_coordinate(stack *p, zahyo e) {
    if(canvas[e.x][e.y] == ' ') {
        push(p, e);
        canvas[e.x][e.y] = '.';
    }
}
