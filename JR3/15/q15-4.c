/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ROSENZU "rosenzu-s.txt"	//路線図データファイル
#define SETMAX 10600	// 集合の要素数の最大値(駅の数)

/************************************************
 * グローバル変数
 ************************************************/
char buf[256];	//入力された文字列を格納するグローバル変数
//指定された駅から各駅までの最短距離を格納するグローバル変数
int dist[SETMAX];

/************************************************
 * 構造体等宣言部
 ************************************************/
struct node { int eki, rosen, kyori; struct node *next; };
struct set { int elements[SETMAX]; int size; };

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
///
/// eを除く0からn-1までの整数を要素とする集合を、
/// アドレスpの指す構造体に格納する関数
///
void init_set(struct set *p, int n, int e) {
	int i, count = 0;
	for(i = 0; i < n; i++) {
		if(i != e) {
			p->elements[count++] = i;
		}
	}
	p->size = n-1;
}

///
/// アドレスpの指す構造体setが表す集合の要素のうち、
/// dist[m]の値が最も小さくなる要素mを削除し、その要素を返す関数
///
int delete_min(struct set *p) {
	int ret = -1;
	if(p->size == 0) {
		//nop
	} else {
		int min = dist[p->elements[0]];
		int min_num = 0;
		for(int i = 0; i < p->size; i++) {
			if(min > dist[p->elements[i]]) {
				min = dist[p->elements[i]];
				min_num = i;
			}
		}
		ret =p->elements[min_num];
		p->elements[min_num] = p->elements[p->size - 1];
		p->size -= 1;
	}
	return ret;
}

///
/// adjlistに、eki1からeki2への辺を追加する関数
///
void add_edge(struct node *adjlist[], int eki1, int eki2, int rosen, int kyori) {
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
/// 頂点数ekisuのグラフを表す隣接リスト表現adjlistに対して、
/// 駅eki1から駅eki2までの最短距離を返す関数
///
int dijkstra(struct node *adjlist[], int eki1, int eki2, int ekisu) {
	//配列distのeki1番目を0, それ以外をINT_MAXに設定
	for(int i = 0; i < SETMAX; i++) {
		if(i == eki1) {
			dist[i] = 0;
		} else {
			dist[i] = INT_MAX;
		}
	}

	//直前に最短距離を確定した駅を格納する変数curにeki1を入れる
	int cur = eki1;
	//まだ最短距離を確定していない駅の集合unknownとして「0からekisu-1までのうち
	//eki1を除く全ての整数が入った集合」を用意
	struct set unknown;
	init_set(&unknown, ekisu, eki1);

	while(unknown.size != 0 && cur != eki2) {
		//printf("cur = %d\n", cur);
		//printf("size = %d\n", unknown.size);
		/*for(int i = 0; i < 6; i++) {
			printf("%d \n", dist[i]);
		}
		printf("----------------\n");*/
		struct node *move = adjlist[cur];
		while(move != NULL) {
			if(dist[move->eki] > dist[cur] + move->kyori) {
				dist[move->eki] = dist[cur] + move->kyori;
			}
			move = move->next;
		}
		cur = delete_min(&unknown);
	}

	return dist[eki2];
}

///
/// メイン関数
///
int main() {
	int eki1, eki2, rosen, ekisu, i, kyori;
	FILE *fp = fopen(ROSENZU, "r");	//路線図ファイルを読む準備
	fscanf(fp, "%d ", &ekisu);	//1行目の駅数を読み取り
	struct node *adjlist[ekisu];
	//隣接リスト表現を初期化、すべての頂点に対する隣接リストを空にする
	for(i = 0; i < ekisu; ++i) adjlist[i] = NULL;
	while(fgets(buf, sizeof(buf), fp) != NULL) {
		//隣り合う駅の情報を読み取り
		sscanf(buf, "%d:%d:%d:%d ", &eki1, &eki2, &rosen, &kyori);
		//そのデータを隣接リスト表現のグラフに追加
		add_edge(adjlist, eki1, eki2, rosen, kyori);
	}
	fclose(fp);
	scanf("%d %d ", &eki1, &eki2);
	printf("%d\n", dijkstra(adjlist, eki1, eki2, ekisu));
	/*for(i = 0; i < ekisu; ++i)
		if(dist[i] < INT_MAX)
			printf("%d: %d\n", i, dist[i]);	*/
	return 0;
}