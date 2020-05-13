#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "graph_param.h"


/* *************** */
/* graph structure */
/* *************** */

typedef struct {
	int edges[MAXV][MAXDEGREE];	/* adjacency info */
	int degree[MAXV];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
} graph;
	
/* ****************************** */
/* functions for graph operations */
/* ****************************** */

void initialize_graph(graph *g)
{
  int i;
  g->nvertices = 0;
  g->nedges = 0;
  for(i = 0; i < MAXV; i++) {
    g->degree[i] = 0;
  }
  return;
}

void insert_vertex(graph *g)
{
  g->nvertices ++;
  if(g->nvertices > MAXV)
    fprintf(stderr, "Warning: insertion exceeds max number of vertices\n");
  return;
}

int is_edge(graph *g, int x, int y)
{
  int i;
  for(i = 0; i < g->degree[x]; i++) {
    if(g->edges[x][i] == y) {
			return 1;
		}
  }
  return 0;
}

void insert_edge(graph *g, int x, int y)
{
  if(is_edge(g, x, y)) {
    fprintf(stderr, "Warning: (%d, %d) already exists, no insertion is performed\n", x, y);
  } else {
    if(g->degree[x] >= MAXDEGREE) {
      fprintf(stderr, "Warning: insertion(%d, %d) exceeds max degree\n", x, y);
    }
    g->edges[x][g->degree[x]] = y;
    g->degree[x] ++;
    g->nedges ++;
  }
  return;
}

void read_graph(FILE *fp, graph *g)
{
	int i;
	int m;
	int x, y;

	initialize_graph(g);

	fscanf(fp, "%d %d\n", &(g->nvertices), &m);
  
	for(i = 0; i < m; i++) {
		fscanf(fp, "%d %d\n", &x, &y);
		insert_edge(g, x, y);
	}
	
	return;
}

// 頂点xを始点、yを終点とする辺を削除
// 返り値=> 削除完了: 0, 削除対象が存在しない: 1
int remove_edge_sub(graph *g, int x, int y) {
	// xが始点の辺を順に参照
	for(int i = 0; i < g->degree[x]; i++) {
		if(g->edges[x][i] == y) {
			//隣接リストの最後尾で上書きし, 次数と辺数を減らす
			g->edges[x][i] = g->edges[x][g->degree[x]-1];
			g->degree[x] --;
			g->nedges --;
			return 0;
		}
	}
	return 1;
}

// 頂点xを始点、yを終点とする辺を削除
void remove_edge(graph *g, int x, int y)
{
	if(remove_edge_sub(g, x, y) == 1) {
	//削除対象の辺が存在しない場合以下が実行される
		printf("存在しない\n");
	}
	return;
}

// 頂点xを始点、yを終点とする辺を削除
// その後、yを始点、xを終点とする辺を追加
void reorient_edge(graph *g, int x, int y)
{
	if(remove_edge_sub(g, x, y) == 0) {
	//以下でyを始点、xを終点とする辺を追加する
		g->edges[y][g->degree[y]] = x;
		g->degree[y] ++;
		g->nedges ++;
	}
	//削除対象が存在しない場合何もしない
	return;
}

void print_graph(graph *g)
{
  int i, j;

  for (i = 0; i < g->nvertices; i++) {
    printf("%d:", i);
      for (j = 0; j < g->degree[i]; j++) {
        printf(" %d", g->edges[i][j]);
      }
    printf("\n");
  }
  return;
}

#endif
