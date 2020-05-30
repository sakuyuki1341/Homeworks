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

// ���_x���n�_�Ay���I�_�Ƃ���ӂ��폜
// �Ԃ�l=> �폜����: 0, �폜�Ώۂ����݂��Ȃ�: 1
int remove_edge_sub(graph *g, int x, int y) {
	// x���n�_�̕ӂ����ɎQ��
	for(int i = 0; i < g->degree[x]; i++) {
		if(g->edges[x][i] == y) {
			//�אڃ��X�g�̍Ō���ŏ㏑����, �����ƕӐ������炷?
			g->edges[x][i] = g->edges[x][g->degree[x]-1];
			g->degree[x] --;
			g->nedges --;
			return 0;
		}
	}
	return 1;
}

// ���_x���n�_�Ay���I�_�Ƃ���ӂ��폜
void remove_edge(graph *g, int x, int y) {
	if(remove_edge_sub(g, x, y) == 1) {
	//�폜�Ώۂ̕ӂ����݂��Ȃ��ꍇ�ȉ������s�����
		printf("���݂��Ȃ�\n");
	}
	return;
}

// ���_x���n�_�Ay���I�_�Ƃ���ӂ��폜
// ���̌�Ay���n�_�Ax���I�_�Ƃ���ӂ�ǉ�
void reorient_edge(graph *g, int x, int y) {
	if(remove_edge_sub(g, x, y) == 0) {
		//�ȉ���y���n�_�Ax���I�_�Ƃ���ӂ�ǉ�����
		insert_edge(g, y, x);
	}
	//�폜�Ώۂ����݂��Ȃ��ꍇ�A�������Ȃ�
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
