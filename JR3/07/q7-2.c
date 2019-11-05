/************************************************
 * マクロ部
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/************************************************
 * 構造体等宣言部
/************************************************/
typedef struct point {  //座標構造体
    int x;
    int y;
} point;

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * プロトタイプ宣言部
/************************************************/
int compare_by(point p1, point p2, char c);
int max_index_by(point a[], int n, char c);

/************************************************
 * 関数部
/************************************************/
///
/// メイン関数
///
int main(int argc, char const *argv[])
{
    char c, buf[128];   //入力保存用
    point p, arr[128];  //入力保存用
    int i = 0;
    //基準取得
    scanf("%c", &c);
    //座標取得
    while(fgets(buf, sizeof(buf), stdin) != NULL && i < 128) {
        sscanf(buf, "%d %d", &p.x, &p.y);
        arr[i] = p;
        i++;
    }
    //最大の座標の表示
    printf("%d\n", max_index_by(arr, i, c));
    return 0;
}

///
/// 座標p1, p2に対し、文字cで指定された基準で比較した結果を「1, 0, -1」として返す
/// p1がp2より大きい場合: 1 / p1とp2が等しい場合: 0 / p1がp2より小さい場合: -1
///
int compare_by(point p1, point p2, char c) {
    if(c == 'X') {

    } else if(c == 'Y') {

    } else if(c == 'D') {

    }
    return 0;
}

///
/// 配列aに対し、先頭からn個のうち、文字cで指定された基準で最大の要素の添字を返す
///
int max_index_by(point a[], int n, char c) {
    point max = a[0];    //一時最大値
    int max_place = 0; //一時最大値の位置
    //n個まで繰り返し
    for (int i = 0; i < n; i++)
    {
        if (compare_by(max, a[i], c) >= 0) //一時最大値の更新
        {
            max = a[i];
            max_place = i;
        }
    }
    return max_place; //最大値の位置を返す
}