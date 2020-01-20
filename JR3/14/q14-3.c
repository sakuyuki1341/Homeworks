/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************************
 * グローバル変数
 ************************************************/
char buf[256];	//get_avlで用いる

/************************************************
 * 構造体等宣言部
 ************************************************/
struct node { int eki, rosen; float kyori; struct node *next; };

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
	int ekisu;
	scanf("%d ", &ekisu);
	int adjmat[ekisu][ekisu];	//隣接行列を表す二次元配列

	int eki1, eki2, rosen;
	float kyori;
	for(int i = 0; i < ekisu; ++i) {
		for(int j = 0; j < ekisu; ++j) {
			adjmat[i][j] = 0;
		}
	}
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		//隣り合う駅の情報を読み取り
		sscanf(buf, "%d:%d:%d:%f ", &eki1, &eki2, &rosen, &kyori);
		adjmat[eki1][eki2] = 1;
		adjmat[eki2][eki1] = 1;
	}
	for(int i = 0; i < ekisu; ++i) {
		for(int j = 0; j < ekisu; ++j) {
			printf("%d", adjmat[i][j]);
		}
		printf("\n");
	}

	return 0;
}