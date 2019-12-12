/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>

/************************************************
 * グローバル変数
 ************************************************/
int count = 0;	//binary_searchの呼び出し回数

/************************************************
 * 構造体等宣言部
 ************************************************/
struct student { int id; char name[32]; int score; };	//学生

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
///
/// 配列stのl番目からr番目の中から、引数のidと一致するような
/// メンバidを持つ要素の添字を見つけ返す関数
///
int binary_search(struct student st[], int id, int l, int r) {
	++count;
	int ret = 0;	//戻り値
	if(r < l) {
		ret = -1;
	} else {
		int m = l + (r-l) / 2;
		if(st[m].id == id) {
			ret = m;
		} else if(st[m].id < id) {
			ret = binary_search(st, id, m+1, r);
		} else if(st[m].id > id) {
			ret = binary_search(st, id, l, m-1);
		}
	}
	return ret;
}


///
/// メイン関数
///
int main() {
	int i = 0, n, v;
	char buf[128], c;
	struct student st[1024];
	while(fgets(buf, sizeof(buf), stdin) != NULL && i < 1024) {
		sscanf(buf, "%d%c", &v ,&c);
		if(c == ',') {
			st[i].id = v;
			sscanf(buf, "%*d,%[^,],%d", st[i].name, &st[i].score);
			++i;
		}
	}
	n = i;
	/*この時点でvに探索目標の学籍番号が入っている*/
	i = binary_search(st, v, 0, n-1);
	if(i < 0) printf("Not found.\n");
	else      printf("%s,%d\n",st[i].name,st[i].score);
	printf("%d\n", count);
	return 0;
}