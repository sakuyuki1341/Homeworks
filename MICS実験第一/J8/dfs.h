#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED

#include <stdio.h>
#include "graph.h"

/* ****************** */
/* Depth-first search */
/* ****************** */

typedef struct {
	int visited[MAXV];
	int predecessor[MAXV];
} dfs_info;

void initialize_search(graph *g, dfs_info *d_i)
{
  int i;
  for (i = 0; i < g->nvertices; i++) {
    d_i->visited[i]     =  0;
    d_i->predecessor[i] = -1;
  }
  return;
}

// 深さ優先探索の実行
void dfs(graph *g, dfs_info *d_i, int start) {
	// 頂点startに訪問済の印を付ける
	d_i->visited[start] = 1;
	
	// startを始点とする辺の終点で訪問済みでないものを見つけ、dfsを実行する
	for (int i = 0; i < g->degree[start]; i++) {
		if (d_i->visited[g->edges[start][i]] == 0) {
			// 先行頂点の記録
			d_i->predecessor[g->edges[start][i]] = start;
			dfs(g, d_i, g->edges[start][i]);
		}
	}
	
	// 見つからなかった場合、関数は終了
	return;
}

void print_predecessors(graph *g, dfs_info *d_i)
{
	int i;
  for(i = 0; i < g->nvertices; i++) {
    printf("%d: predecessor[%d] = %d\n", i, i, d_i->predecessor[i]);
  }
	return;
}

void print_visited_vertices(graph *g, dfs_info *d_i)
{
	int i;
  for(i = 0; i < g->nvertices; i++) {
    printf("%d: visited[%d] = %d\n", i, i, d_i->visited[i]);
  }
	return;
}

#endif
