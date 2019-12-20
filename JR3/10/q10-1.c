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
struct student { int id; char name[32]; int score; };	//学生

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
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
	st[n].score = v;	//番兵を記録
	i = 0;
	//目的の学生を上から探索
	while(st[i].score != st[n].score) {
		i++;
	}
	//最初に見つかったものを表示
	if(i == n) {
		printf("Not found.\n");
	} else if(i < n) {
		printf("%d,%s\n", st[i].id, st[i].name);
	}
	return 0;
}