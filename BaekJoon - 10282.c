#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n, d, c;
#define INF 200000000
#define MAX_VERTEX 10000
#define MAX_EDGE 100000

typedef struct Vnode {
	int vertex;
	int weight;
	struct Vnode *next;
}vnode;

typedef struct Heap {
	vnode *H_list[MAX_EDGE + 1];
	int size;
}heap;

typedef struct Graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;

heap *H;
graph *G;

void Init_Heap() {
	H = (heap *)malloc(sizeof(heap));
	H->size = 0;
}

void upHeap(int i) {
	while (i > 1) {
		if (H->H_list[i]->weight < H->H_list[i / 2]->weight) {
			vnode *tmp = H->H_list[i];
			H->H_list[i] = H->H_list[i/2];
			H->H_list[i / 2] = tmp;
			i /= 2;
		}
		else {
			break;
		}
	}
}

void downHeap(int i) {
	while (2 * i <= H->size) {
		int child = 2 * i;
		if (child + 1 <= H->size && H->H_list[child]->weight > H->H_list[child + 1]->weight) {
			child++;
		}
		if (H->H_list[i]->weight > H->H_list[child]->weight) {
			vnode *tmp = H->H_list[i];
			H->H_list[i] = H->H_list[child];
			H->H_list[child] = tmp;
			i = child;
		}
		else {
			break;
		}
	}
}

vnode *removeMin() {
	vnode *res = H->H_list[1];
	H->H_list[1] = H->H_list[(H->size)--];
	downHeap(1);
	return res;
}

void addHeap(vnode *V) {
	H->H_list[++(H->size)] = V;
	upHeap(H->size);
}

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
}

vnode *getVnode(int v, int w) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = v;
	newnode->weight = w;
	newnode->next = NULL;
	return newnode;
}

void addEdge(int u, int v, int s) {
	vnode *newnode = getVnode(v, s);
	newnode->next = G->adj_list[u]->next;
	G->adj_list[u]->next = newnode;
}

void Make_Graph() {
	int a, b, s;
	scanf("%d %d %d", &n, &d, &c);
	for (int i = 1; i <= n; i++) {
		G->adj_list[i] = getVnode(i, 0);
	}//헤더노드 생성
	for (int i = 0; i < d; i++) {
		scanf("%d %d %d", &a, &b, &s);
		addEdge(b, a, s);
	}
}

void Daijkstra() {
	Init_Heap();
	int res = 0,max=0;
	int dist[10000 + 1] = { 0, };
	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
	}
	dist[c] = 0;
	addHeap(G->adj_list[c]);
	while (H->size != 0) {
		vnode *tmp = removeMin();
		int F = tmp->vertex;
		vnode *traverse = G->adj_list[F]->next;
		if (dist[F] < tmp->weight) {
			continue;
		}
		while (traverse != NULL) {
			if (dist[traverse->vertex] > dist[F] + traverse->weight) {
				dist[traverse->vertex] = dist[F] + traverse->weight;
				traverse->weight = dist[traverse->vertex];
				addHeap(traverse);
			}
			traverse = traverse->next;
		}
	}

	for (int i = 1; i <= n; i++) {
		if (dist[i] != INF) {
			res++;
			if (max < dist[i]) {
				max = dist[i];
			}
		}
	}
	printf("%d %d\n", res, max);
}


int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		Init_Graph();
		Make_Graph();
		Daijkstra();
	}
	return 0;
}