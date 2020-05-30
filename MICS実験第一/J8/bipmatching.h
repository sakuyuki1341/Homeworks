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

// start����end�ւȂ��鑝�����𔽓]������
// matching�ւ�start��end�ւȂ���ӂ��������ӂ�ǉ�����
void augment(graph *g, dfs_info *d_i, graph *matching, int start, int end) {
	// �ȉ��̓e�L�X�gp27 2.(a)~(c)�ɉ����č쐬
	// (a),(b)�̏���
	int v = end;
	int p = d_i->predecessor[v];

	// ���]��(c)�̏���
	while (v != start) {
		reorient_edge(g, p, v);
		// matching��u,v�����ԕӂ����݂��Ȃ���΁A(u, v)��}��
		// �܂��Amatching��source, sink�͑��݂��Ȃ����߁Av, p��start, end�̏ꍇ��matching�֒ǉ����Ȃ�
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

// �ő�}�b�`���O���Z�o����
int find_maximum_matching(graph *g, graph *matching)
{
	int size = 0;			/* the size of a current matching */
	int source, sink;
	dfs_info *d_i;
	
	source = g->nvertices -2;
	sink   = g->nvertices -1;
	d_i = (dfs_info*)malloc(sizeof(dfs_info));

	while (true) {
		// �[���D��T��
		initialize_search(g, d_i);
		dfs(g, d_i, source);
		// ���B�ł��Ȃ��ꍇ�I��
		if (d_i->visited[sink] == 0) {
			break;
		}
		// ���B�ł����ꍇ�A�������̔��]
		augment(g, d_i, matching, source, sink);
		// ��������������Ȃ��������߈���₷
		size++;
	}
	// �m�F�̈�matching�̏o��
	print_graph(matching);
	return size;
}

#endif
