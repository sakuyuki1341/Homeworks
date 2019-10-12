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
int number = 0;

/************************************************
 * プロトタイプ宣言部
 ************************************************/
// 引数の構造体に格納されている値を2倍にした構造体を返す
golden double_golden(golden x);

// 引数の構造体に格納されている値の、和の値を格納した構造体を返す
golden add_golden(golden x, golden y);

// 引数の構造体に格納されている値の、積の値を格納した構造体を返す
golden mult_golden(golden x, golden y);

// 引数の構造体に格納されている値の、累乗の値を格納した構造体を返す
golden power_golden(golden x, int n);

/************************************************
 * 関数部
 ************************************************/
int main(int argc, char const *argv[]) {
    golden x;
    int n;
    // 入力
    scanf("%lld %lld", &x.a, &x.b);
    scanf("%d", &n);
    x = power_golden(x, n);   // 計算実行
    // 表示
    printf("%lld %lld\n", x.a, x.b);
    printf("%d\n", number);
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
    number += 1;
    golden z;
    // (a1 + b1φ) * (a2 + b2φ) = (a1a2 + b1b2) + (a1b2 + a2b1 + b1b2)φ
    z.a = x.a*y.a + x.b*y.b;
    z.b = x.a*y.b + x.b*y.b + x.b*y.a;
    return z;
}

golden power_golden(golden x, int n) {
    golden z;
    if(n == 0) {
        z.a = 1; z.b = 0;
    } else {
        z = mult_golden(x, power_golden(x, n-1));
    }
    return z;
}
