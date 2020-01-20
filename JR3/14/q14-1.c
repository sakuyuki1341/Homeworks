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
/// adjlistに、eki1からeki2への辺を追加する関数
///
void add_edge(struct node *adjlist[], int eki1, int eki2, int rosen, float kyori) {
	struct node *go = (struct node*)malloc(sizeof(struct node)),
				*back = (struct node*)malloc(sizeof(struct node));
	go->eki = eki2;
	go->kyori = kyori;
	go->next = adjlist[eki1];
	go->rosen = rosen;

	back->eki = eki1;
	back->kyori = kyori;
	back->next = adjlist[eki2];
	back->rosen = rosen;

	adjlist[eki1] = go;
	adjlist[eki2] = back;
}

///
/// 頂点数nの隣接リスト表現を表示する関数
///
void print_adjlist(struct node *adjlist[], int n) {
	int i;
	struct node *p;
	for(i = 0; i < n; ++i) {
		printf("%d:", i);
		p = adjlist[i];
		while(p != NULL) {
			printf(" (%d,%d,%.3f)", p->eki, p->rosen, p->kyori);
			p = p->next;
		}
		printf("\n");
	}
	return;
}

///
/// メイン関数
///
int main() {
	int eki1, eki2, rosen, ekisu, i;
	float kyori;
	//頂点数をekisuに格納
	scanf("%d ", &ekisu);
	struct node *adjlist[ekisu];
	//隣接リスト表現を初期化,すべての頂点に対する隣接リストを空にする
	for(i = 0; i < ekisu; ++i)	adjlist[i] = NULL;
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		//隣り合う駅の情報を読み取り
		sscanf(buf, "%d:%d:%d:%f ", &eki1, &eki2, &rosen, &kyori);
		//そのデータを隣接リスト表現のグラフに追加
		add_edge(adjlist, eki1, eki2, rosen, kyori);
	}
	print_adjlist(adjlist, ekisu);
	return 0;
}