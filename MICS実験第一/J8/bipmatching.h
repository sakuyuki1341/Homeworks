#ifndef BIPMATCHING_H_INCLUDED
#define BIPMATCHING_H_INCLUDED

#include "dfs.h"
#include "stdbool.h"

/* ************************** */
/* maximum-matching algorithm */
/* ************************** */

void construct_digraph_for_matching(graph *g)
{
	int i, source, sink;
	source = g->nvertices; insert_vertex(g);
	sink   = g->nvertices; insert_vertex(g);
	for(i = 0; i < g->nvertices -2; i++) {
		if(g->degree[i]==0) insert_edge(g, i, sink);
		else                insert_edge(g, source, i);
	}
	return;
}

// startからendへつながる増加道を反転させる
// matchingへはstartとendへつながる辺を除いた辺を追加する
void augment(graph *g, dfs_info *d_i, graph *matching, int start, int end) {
	// 以下はテキストp27 2.(a)~(c)に沿って作成
	// (a),(b)の処理
	int v = end;
	int p = d_i->predecessor[v];

	// 反転と(c)の処理
	while (v != start) {
		reorient_edge(g, p, v);
		// matchingのu,vを結ぶ辺が存在しなければ、(u, v)を挿入
		// また、matchingにsource, sinkは存在しないため、v, pがstart, endの場合はmatchingへ追加しない
		if (is_edge(matching, p, v) == 0 && is_edge(matching, v, p) == 0 && v != end && p != start) {
			insert_edge(matching, p, v);
		} else {
			remove_edge_sub(matching, v, p);
		}
		v = p;
		p = d_i->predecessor[v];
	}
	return;
}

// 最大マッチングを算出する
int find_maximum_matching(graph *g, graph *matching)
{
	int size = 0;			/* the size of a current matching */
	int source, sink;
	dfs_info *d_i;
	
	source = g->nvertices -2;
	sink   = g->nvertices -1;
	d_i = (dfs_info*)malloc(sizeof(dfs_info));

	while (true) {
		// 深さ優先探索
		initialize_search(g, d_i);
		dfs(g, d_i, source);
		// 到達できない場合終了
		if (d_i->visited[sink] == 0) {
			break;
		}
		// 到達できた場合、増加道の反転
		augment(g, d_i, matching, source, sink);
		// 増加道が見つからなかったため一つ増やす
		size++;
	}
	// 確認の為matchingの出力
	print_graph(matching);
	return size;
}

#endif
