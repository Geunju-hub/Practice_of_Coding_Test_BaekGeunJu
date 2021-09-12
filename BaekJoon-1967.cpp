//BaekJoon-1967(트리의 지름) solved by c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10000

int N,res=0,node=0;
int visited[MAX_VERTEX + 1] = { 0, };

typedef struct Vnode {
	int vertex;
	int weight;
	struct Vnode *next;
}vnode;

typedef struct Graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;

graph *G;

vnode *getVnode(int v, int w) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = v;
	newnode->weight = w;
	newnode->next = NULL;
	return newnode;
}

void addEdge(int u, int v, int w) {
	vnode *newnode = getVnode(v, w);
	newnode->next = G->adj_list[u]->next;
	G->adj_list[u]->next = newnode;
	if (u != v) {
		vnode *newnode2 = getVnode(u, w);
		newnode2->next = G->adj_list[v]->next;
		G->adj_list[v]->next = newnode2;
	}
}

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		G->adj_list[i] = getVnode(i, 0);
	}
}

void Make_Graph() {
	for (int i = 1; i < N; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}
}

void DFS(int s,int cost) {
	visited[s] = 1;
	vnode *tmp = G->adj_list[s];
	while (tmp != NULL) {
		if (visited[tmp->vertex] == 0) {
			DFS(tmp->vertex,cost+tmp->weight);
			if (cost + tmp->weight > res) {
				res = cost + tmp->weight;
				node = tmp->vertex;
			}
		}
		tmp = tmp->next;
	}
}

int main(void) {
	Init_Graph();
	Make_Graph();
	//그래프 구현 후
	DFS(1,0);//시작점으로부터 가장 먼 정점 찾고
	res = 0;
	for (int i = 1; i <= N; i++) {
		visited[i] = 0;
	}//초기화 과정 필수
	DFS(node, 0);// 그 정점 기준 dfs다시 반복
	printf("%d", res);
	return 0;
}