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
/// 頂点数nのグラフを表す隣接行列adjmatに対して、そのグラフの
/// 推移的閉包の隣接行列resultを作成する関数
///
void warshall(int n, int adjmat[n][n], int result[n][n]) {
	int reach[n+1][n][n];
	for(int k = 0; k <= n; ++k) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				reach[k][i][j] = 0;
				if(k == 0 && i == j) {
					reach[k][i][j] = 1;
					reach[k][j][i] = 1;
				} else if(k == 0 && adjmat[i][j]) {
					reach[k][i][j] = 1;
					reach[k][j][i] = 1;
				} else if(k > 0) {
					if(reach[k-1][i][j] == 1) {
						reach[k][i][j] = 1;
						reach[k][j][i] = 1;
					} else if(reach[k-1][i][k-1] && reach[k-1][k-1][j]) {
						reach[k][i][j] = 1;
						reach[k][j][i] = 1;
					}
				}
			}
		}
	}


	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			result[i][j] = reach[n][i][j];
		}
	}
}

///
/// メイン関数
///
int main() {
	int ekisu;
	scanf("%d ", &ekisu);
	int adjmat[ekisu][ekisu], result[ekisu][ekisu];

//問題3で作成した部分
	int eki1, eki2, rosen;
	float kyori;
	for(int i = 0; i < ekisu; ++i) {
		for(int j = 0; j < ekisu; ++j) {
			adjmat[i][j] = 0;
		}
	}
	//入力
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		//隣り合う駅の情報を読み取り
		sscanf(buf, "%d:%d:%d:%f ", &eki1, &eki2, &rosen, &kyori);
		adjmat[eki1][eki2] = 1;
		adjmat[eki2][eki1] = 1;
	}

	warshall(ekisu, adjmat, result);
	for(int i = 0; i < ekisu; ++i) {
		for(int j = 0; j < ekisu; ++j) {
			printf("%d", result[i][j]);
		}
		printf("\n");
	}

	return 0;
}