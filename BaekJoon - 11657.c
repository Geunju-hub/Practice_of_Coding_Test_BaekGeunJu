#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 210000000

int N, M;
long long dist[500 + 1] = { 0, };

typedef struct Vnode {
	int start_vertex;
	int end_vertex;
	int weight;
	struct Vnode *next;
}vnode;

typedef struct Graph {
	vnode *edge_list[6000+1];
}graph;

graph *G;

vnode *getVnode(int i, int j,int w) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->start_vertex = i;
	newnode->end_vertex = j;
	newnode->weight = w;
	return newnode;
}

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d", &N, &M);
}

void Make_Graph() {
	for (int i = 0; i < M; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		vnode *newnode = getVnode(u, v, w);
		G->edge_list[i] = newnode;
	}
}

void BellmanFord() {
	for (int i = 2; i <= N; i++) {
		dist[i] = INF;
	}
	for (int i = 0; i <= N-1; i++) {
		for (int j = 0; j < M; j++) {
			int from = G->edge_list[j]->start_vertex;
			int to = G->edge_list[j]->end_vertex;
			int cost = G->edge_list[j]->weight;
			if (dist[from] == INF) {
				continue;
			}
			if (dist[to] > dist[from] + cost) {
				if (i == N - 1) {
					printf("-1\n");
					return;
				}//음수 사이클
				dist[to] = dist[from] + cost;
			}
		}
	}
	for (int i = 0; i < M; i++) {
		int from = G->edge_list[i]->start_vertex;
		int to = G->edge_list[i]->end_vertex;
		int cost = G->edge_list[i]->weight;
		if (dist[from] == INF) {
			continue;
		}
		if (dist[to] > dist[from] + cost) {
			dist[to]=INF;
		}
	}
	
	for (int i = 2; i <= N; i++) {
		if (dist[i] == INF) {
			printf("-1\n");
		}
		else {
			printf("%d\n", dist[i]);
		}
	}
}

int main(void) {
	Init_Graph();
	Make_Graph();
	BellmanFord();
	return 0;
}