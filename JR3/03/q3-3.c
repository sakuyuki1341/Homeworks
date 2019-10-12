/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/************************************************
 * 構造体宣言部
 ************************************************/
// golden型の構造体を宣言
typedef struct {
    long long int a;
    long long int b;
} golden;

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * プロトタイプ宣言部
 ************************************************/
// 引数の構造体に格納されている値を2倍にした構造体を返す
golden double_golden(golden x);

// 引数の構造体に格納されている値の、和の値を格納した構造体を返す
golden add_golden(golden x, golden y);

// 引数の構造体に格納されている値の、積の値を格納した構造体を返す
golden mult_golden(golden x, golden y);

/************************************************
 * 関数部
 ************************************************/
int main(int argc, char const *argv[]) {
    golden x, y;
    // 入力
    scanf("%lld %lld", &x.a, &x.b);
    scanf("%lld %lld", &y.a, &y.b);
    x = mult_golden(x, y);   // 計算実行
    // 表示
    printf("%lld %lld\n", x.a, x.b);
    return 0;
}



// 引数の構造体に格納されている値を2倍にした構造体を返す
golden double_golden(golden x) {
    golden y;   // 戻値用構造体
    y.a = x.a * 2;
    y.b = x.b * 2;
    return y;
}

// 引数の構造体に格納されている値の、和の値を格納した構造体を返す
golden add_golden(golden x, golden y) {
    golden z;   // 戻値用構造体
    z.a = x.a + y.a;
    z.b = x.b + y.b;
    return z;
}

// 引数の構造体に格納されている値の、積の値を格納した構造体を返す
golden mult_golden(golden x, golden y) {
    golden z;
    z.a = x.a*y.a + x.b*y.b;
    z.b = x.a*y.b + x.b*y.b + x.b*y.a;
    return z;
}
