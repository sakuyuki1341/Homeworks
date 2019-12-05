/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * 構造体等宣言部
 ************************************************/
struct point { int x, y; };	//座標

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
///
/// 配列aの先頭n番目の要素について、
/// rビットを1桁として下位dmax桁に対して行う基数ソートアルゴリズムにより、
/// 規準xで昇順に整列する関数
///
void radix_sort(struct point a[], int n, int r, int dmax) {
	int c_max = 1;
	for(int i = 0; i < r; i++) {
		c_max = c_max * 2;
	}
	int c[c_max];
	struct point p, b[n];

	for(int d = 0; d < dmax; d++) {
		for(int i = 0; i < c_max; i++) {
			c[i] = 0;
		}
		for(int i = 0; i < n; i++) {
			int num_x = (a[i].x >> (d * r)) & ((1 << r) -1);
			c[num_x] += 1;
			b[i] = a[i];
		}
		for(int i = 1; i < c_max; i++) {
			c[i] += c[i-1];
		}
		for(int i = n-1; i >= 0; i--) {
			p = b[i];
			c[(p.x >> (d * r)) & ((1 << r) -1)] -= 1;
			a[c[(p.x >> (d * r)) & ((1 << r) -1)]] = p;
		}
		for(int i=0; i<n; ++i) {
			printf("%d %d\n", a[i].x, a[i].y);
		}
		printf("--\n");
	}
	/*
	int c[100] = {};
	struct point p, b[n];
	for(int i = 0; i < n; i++) {
		int num_x = a[i].x;
		c[num_x] += 1;
		b[i] = a[i];
	}
	for(int i = 1; i < 100; i++) {
		c[i] += c[i-1];
	}
	for(int i = n-1; i >= 0; i--) {
		p = b[i];
		c[p.x] -= 1;
		a[c[p.x]] = p;
	}
	*/
}

///
/// メイン関数
///
int main() {
	char buf[128];
	struct point p, arr[128];
	int i = 0, n, r, dmax;
	scanf("%d %d ",&r,&dmax);

	while(fgets(buf,sizeof(buf),stdin) != NULL && i<128) {
		sscanf(buf, "%d %d", &p.x, &p.y);
		arr[i] = p;
		++i;
	}
	n = i;
	radix_sort(arr, n, r, dmax);
	return 0;
}