//BaekJoon-4013 - solved by c. (위상정렬)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 500000
#define MAX_EDGE 500000

int N, M,S,P;
int cost[MAX_VERTEX + 1] = { 0, };
int num[MAX_VERTEX + 1] = { 0, };

typedef struct Vnode {
	int vertex;
	int indegree;
	struct Vnode *next;
}vnode;

typedef struct Graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;

vnode *heap[MAX_VERTEX + 1];
graph *G;
int size=0;

vnode *getVnode(int v) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = v;
	newnode->indegree = 0;
	newnode->next = NULL;
	return newnode;
}

void upHeap(int i) {
	while (i > 1) {
		if (cost[heap[i]->vertex] > cost[heap[i / 2]->vertex]) {
			vnode *tmp = heap[i];
			heap[i] = heap[i / 2];
			heap[i / 2] = tmp;
			i /= 2;
		}
		else {
			return;
		}
	}
}

void downHeap(int i) {
	while (2 * i <= size) {
		int child = 2 * i;
		if (child + 1 <= size && cost[heap[child]->vertex] < cost[heap[child + 1]->vertex]) {
			child++;
		}
		if (cost[heap[child]->vertex] > cost[heap[i]->vertex]) {
			vnode *tmp = heap[i];
			heap[i] = heap[i / 2];
			heap[i / 2] = tmp;
			i =child;
		}
		else {
			return;
		}
	}
}

void addHeap(vnode *V) {
	heap[++size] = V;
	upHeap(size);
}

vnode *removeMax() {
	vnode *res = heap[1];
	heap[1] = heap[size--];
	downHeap(1);
	return res;
}

void addEdge(int u, int v) {
	vnode *newnode = getVnode(v);
	newnode->next = G->adj_list[u]->next;
	G->adj_list[u]->next = newnode;
	G->adj_list[v]->indegree++;
}


void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		G->adj_list[i] = getVnode(i);
	}
}

void Make_Graph() {
	for (int i = 0; i < M; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}
	for (int i = 1; i <= N; i++) {
		scanf("%d", &cost[i]);
	}
	scanf("%d %d", &S, &P);
	for (int i = 0; i < P; i++) {
		scanf("%d", &num[i]);
	}
}

void topologicalsort() {
	int res = 0;
	vnode *tmp = G->adj_list[S]->next;
	while (tmp != NULL) {
		addHeap(G->adj_list[tmp->vertex]);
		tmp = tmp->next;
	}//시작지점 주위 진입차수 0인 지점 넣기
	while (size!=0) {
		vnode *T = removeMax();
		res += cost[T->vertex];
		vnode *traverse = T->next;
		while (traverse != NULL) {
			G->adj_list[traverse->vertex]->indegree--;
			if (G->adj_list[traverse->vertex]->indegree == 0) {
				addHeap(G->adj_list[traverse->vertex]);
			}
			traverse = traverse->next;
		}
	}
	printf("%d", res);
}

int main(void) {
	Init_Graph();
	Make_Graph();
	topologicalsort();
	return 0;
}