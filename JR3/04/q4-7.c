/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAXQUEUE 128

/************************************************
 * 構造体宣言部
 ************************************************/
// 構造体ではないがここで宣言
typedef int elementtype;

// キュー構造体
typedef struct queue {
    int front;  // 次に要素を取り出す位置、rearと同値ならキューは空
    int rear;   // 次に要素を入れる位置
    elementtype contents[MAXQUEUE]; // 要素の配列
} queue;

/************************************************
 * グローバル変数
 ************************************************/
char buf[128];  // 標準入力保存

/************************************************
 * プロトタイプ宣言部
 ************************************************/
// キューを受け取り、それを空にする関数
void initqueue(queue *p);

// キューを受け取り、空なら0, そうでないなら１を返す
int queueempty(queue *p);

// キューを受け取り、そこから要素を取り出し、その要素を返す
elementtype getq(queue *p);

// キューを受け取り、そこにeを入れる
void putq(queue *p, elementtype e);

// キューのアドレスを受け取り、そのキューの中身を[]で囲って順に出力
// elementtypeを変更した際は要注意
void queue_printer(queue *p);

/************************************************
 * 関数部
 ************************************************/
int main(int argc, char const *argv[]) {
    queue q;    // キューの用意
    int i;
    initqueue(&q);  // キューの初期化
    // 標準入力受け取り
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        if(q.front == MAXQUEUE) {
            q.front = 0;
        }
        if(q.rear == MAXQUEUE) {
            q.rear = 0;
        }
        if(buf[0] == 'g') {
            getq(&q);
        } else {
            sscanf(buf, "%d", &i);
            putq(&q, i);
            printf("front:%d\n", q.front);
        }
        queue_printer(&q);
    }
    return 0;
}

void initqueue(queue *p) {
    p->front = 0;
    p->rear = 0;
}

int queueempty(queue *p) {
    if(p->front == p->rear) {
        return 0;
    }
    return 1;
}

elementtype getq(queue *p) {
    if(queueempty(p) == 0) {
        // 空の場合、文を表示して異常終了
        printf("Underflow.\n");
        exit(1);
    } else {
        return p->contents[p->front++];  // 要素を返した後、frontを一つ進める
    }
}

void putq(queue *p, elementtype e) {
    if(p->rear + 1 == p->front || p->rear - p->front == MAXQUEUE - 1) {
        // 要素が入れられない場合、文を表示して異常終了
        printf("Overflow.\n");
        exit(1);
    } else {
        p->contents[p->rear++] = e; // 要素を追加した後、rearを一つ進める
    }
}

void queue_printer(queue *p) {
    // 最後に入れられた要素まで順に表示
    for(int i = p->front; i != p->rear; i++) {
        if(i == MAXQUEUE) {
            i = 0;
        }
        printf("[%d]", p->contents[i]);
    }
    printf("\n");   // 表示後最後に改行
}
