/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAXQUEUE 128
#define N 10

/************************************************
 * 構造体宣言部
 ************************************************/
// 座標構造体
 typedef struct zahyo {
     int x;
     int y;
 } zahyo;

// 構造体ではないがここで宣言
typedef zahyo elementtype;

// キュー構造体
typedef struct queue {
    int front;  // 次に要素を取り出す位置、rearと同値ならキューは空
    int rear;   // 次に要素を入れる位置
    elementtype contents[MAXQUEUE]; // 要素の配列
} queue;

/************************************************
 * グローバル変数
 ************************************************/
char buf[N + 2];  // 標準入力保存
char heya[N][N];

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

// キューのアドレスを受け取り、そのキューのfrontとrearがMAXQUEUEのとき、0に戻す
void queue_back(queue *p);

/************************************************
 * 関数部
 ************************************************/
int main(int argc, char const *argv[]) {
    queue q;    // キューの用意
    int i, j;
    int kyori[N][N]; // startからの距離を記録する用
    zahyo start, goal;  // スタート, ゴールの用意

    // kyoriの初期化
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            kyori[i][j] = -1;
        }
    }
    initqueue(&q);  // キューの初期化

    i = 0;
    /// 標準入力受け取り
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        for(j = 0; j < N; j++) {
            if(buf[j] == 'S') { // startの記録
                start.x = i;
                start.y = j;
            } else if(buf[j] == 'G') {  // goalの記録
                goal.x = i;
                goal.y = j;
            }
            heya[i][j] = buf[j];
        }
        i++;
    }

    /// 最短距離計算
    putq(&q, start);    // キューにstartを入れる
    kyori[start.x][start.y] = 0;    // スタート位置に0
    // 空になるまでループ
    while (queueempty(&q) == 1) {
        zahyo tmp = getq(&q);   // 先頭座標を取得
        // 次の座標を関数に引き渡し
        zahyo surroundigs[4] = {
            {tmp.x, tmp.y + 1}, // up
            {tmp.x, tmp.y - 1}, // down
            {tmp.x - 1, tmp.y}, // left
            {tmp.x + 1, tmp.y}  // right
        };
        for(i = 0; i < 4; i++) {
            // 内部の壁を含む壁と壁の範囲外の場合とばす
            if(surroundigs[i].x <= 0 || 9 <= surroundigs[i].x || surroundigs[i].y <= 0 || 9 <= surroundigs[i].y || heya[surroundigs[i].x][surroundigs[i].y] == '*') {
                continue;
            }
            // 訪問済みの場合とばす
            if(kyori[surroundigs[i].x][surroundigs[i].y] != -1) {
                continue;
            }
            putq(&q, surroundigs[i]);   // キューに座標を入れる
            kyori[surroundigs[i].x][surroundigs[i].y] = kyori[tmp.x][tmp.y] + 1; // 距離更新
        }
    }

    // 最短距離の表示
    printf("%d\n", kyori[goal.x][goal.y]);

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
    queue_back(p);
    if(p->rear + 1 == p->front || p->rear - p->front == MAXQUEUE - 1) {
        // 要素が入れられない場合、文を表示して異常終了
        printf("Overflow.\n");
        exit(1);
    } else {
        p->contents[p->rear++] = e; // 要素を追加した後、rearを一つ進める
    }
}

void queue_printer(queue *p) {
    queue_back(p);
    // 最後に入れられた要素まで順に表示
    for(int i = p->front; i != p->rear; i++) {
        if(i == MAXQUEUE) {
            i = 0;
        }
        printf("[%d]", p->contents[i]);
    }
    printf("\n");   // 表示後最後に改行
}

void queue_back(queue *p) {
    if(p->front == MAXQUEUE) {
        p->front = 0;
    }
    if(p->rear == MAXQUEUE) {
        p->rear = 0;
    }
}
