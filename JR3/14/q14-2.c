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
/// 隣接リストadjlistにおいて、駅番号ekiの駅から1駅離れた駅のうち、
/// 最も遠い駅までの距離を出力する関数
///
float one_hop_kyori(struct node *adjlist[], int eki, int nogo_eki) {
	float max = adjlist[eki]->kyori;
	if(adjlist[eki]->eki == nogo_eki) {
		max = adjlist[eki]->next->kyori;
	}
	struct node *move = adjlist[eki]->next;
	while(move != NULL) {
		if(max < move->kyori && move->eki != nogo_eki) {
			max = move->kyori;
		}
		move = move->next;
	}
	return max;
}

///
/// 隣接リストadjlistにおいて、駅番号ekiの駅から2駅離れた駅のうち、
/// 最も遠い駅までの距離を出力する関数
///
float two_hop_kyori(struct node *adjlist[], int eki) {
	float max = adjlist[eki]->kyori + one_hop_kyori(adjlist, adjlist[eki]->eki, eki);
	struct node *move = adjlist[eki]->next;
	while(move != NULL) {
		float now = move->kyori + one_hop_kyori(adjlist, move->eki, eki);
		if(max < now) {
			max = now;
		}
		move = move->next;
	}
	return max;
}

///
/// メイン関数
///
int main() {
	int eki1, eki2, rosen, ekisu, i;
	float kyori;
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
	for(i = 0; i < ekisu; ++i)
		printf("%d: %.3f\n", i, two_hop_kyori(adjlist, i));
	return 0;
}