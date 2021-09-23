#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 200000000
#define MAX_VERTEX 1000
#define MAX_EDGE 100000
int dist[MAX_VERTEX + 1] = { 0, };
int parent[MAX_VERTEX + 1] = { 0, };
int N, M, s, e;

typedef struct Vnode {
	int vertex;
	int weight;
	struct Vnode *next;
}vnode;

typedef struct Graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;

typedef struct Heap {
	vnode *E_heap[MAX_EDGE + 1];
	int size;
}heap;

graph *G;
heap *H;

vnode *getVnode(int u, int w) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = u;
	newnode->weight = w;
	newnode->next = NULL;
	return newnode;
}

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		G->adj_list[i] = getVnode(i, 0);
	}
}

void addEdge(int u, int v, int w) {
	vnode *p1 = G->adj_list[u];
	vnode *newnode1 = getVnode(v, w);
	newnode1->next = p1->next;
	p1->next = newnode1;
}

void Make_Graph() {
	for (int i = 0; i < M; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}
}

void Init_Heap() {
	H = (heap *)malloc(sizeof(heap));
	H->size = 0;
}

void upHeap(int i) {
	if (i > 1) {
		if (H->E_heap[i]->weight < H->E_heap[i / 2]->weight) {
			vnode *tmp = H->E_heap[i];
			H->E_heap[i] = H->E_heap[i / 2];
			H->E_heap[i / 2] = tmp;
		}
		else if (H->E_heap[i]->weight == H->E_heap[i / 2]->weight) {
			if (H->E_heap[i]->vertex < H->E_heap[i / 2]->vertex) {
				vnode *tmp = H->E_heap[i];
				H->E_heap[i] = H->E_heap[i / 2];
				H->E_heap[i / 2] = tmp;
			}
		}
		upHeap(i / 2);
	}
}

void addHeap(vnode *E) {
	H->E_heap[++H->size] = E;
	upHeap(H->size);
}

void downHeap(int i) {
	if (2 * i <= H->size) {
		int child = 2 * i;
		if (child + 1 <= H->size && H->E_heap[child]->weight > H->E_heap[child + 1]->weight) {
			child++;
		}
		else if (child + 1 <= H->size && H->E_heap[child]->weight == H->E_heap[child + 1]->weight) {
			if (H->E_heap[child]->vertex > H->E_heap[child + 1]->vertex) {
				child++;
			}
		}
		if (H->E_heap[i]->weight > H->E_heap[child]->weight) {
			vnode *tmp = H->E_heap[i];
			H->E_heap[i] = H->E_heap[child];
			H->E_heap[child] = tmp;
		}
		else if (H->E_heap[i]->weight == H->E_heap[child]->weight) {
			if (H->E_heap[i]->vertex > H->E_heap[child]->vertex) {
				vnode *tmp = H->E_heap[i];
				H->E_heap[i] = H->E_heap[child];
				H->E_heap[child] = tmp;
			}
		}
		downHeap(child);
	}
}

vnode *removeMin() {
	vnode *res = H->E_heap[1];
	H->E_heap[1] = H->E_heap[H->size--];
	downHeap(1);
	return res;
}

void DaijkstraShortestPaths_Algorithm() {
	scanf("%d %d", &s, &e);
	for (int i = 0; i <= 1000; i++) {
		dist[i] = INF;
		parent[i] = i;
	}
	Init_Heap();
	dist[s] = 0;
	int F = s;
	addHeap(G->adj_list[s]);
	while (H->size != 0) {
		vnode *from = removeMin();
		vnode *traverse = G->adj_list[from->vertex]->next;
		F = from->vertex;
		if (dist[F] < from->weight) {
			continue;
		}
		while (traverse != NULL) {
			if (dist[traverse->vertex] >= dist[F] + traverse->weight) {
				dist[traverse->vertex] = dist[F] + traverse->weight;
				parent[traverse->vertex] = F;
				addHeap(traverse);
			}
			traverse = traverse->next;

		}
	}
	printf("%d\n", dist[e]);
	int i = e;
	int res[100000 + 1] = { 0, }, cnt = 0;
	while (i != s) {
		res[cnt++] = i;
		i = parent[i];
	}
	res[cnt++] = s;
	printf("%d\n", cnt);
	for (int i = cnt - 1; i >= 0; i--) {
		printf("%d ", res[i]);
	}
}


int main(void) {
	Init_Graph();
	Make_Graph();
	DaijkstraShortestPaths_Algorithm();
	return 0;
}