#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 1000
#define MAX_EDGE 100000
#define INF 100000+1
int N, K,W;
int weight[MAX_VERTEX + 1] = { 0, };

int Max(int a, int b) {
	return a > b ? a : b;
}

typedef struct Vnode {
	int vertex;
	int indegree;
	struct Vnode *next;
}vnode;

typedef struct Graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;

typedef struct Qnode {
	vnode *element;
	int cnt;
	struct Qnode *next;
}qnode;

typedef struct Queue {
	qnode *front;
	qnode *rear;
}queue;

qnode *getQnode(vnode *V,int cnt) {
	qnode *newnode = (qnode *)malloc(sizeof(qnode));
	newnode->cnt = cnt;
	newnode->element = V;
	newnode->next = NULL;
	return newnode;
}

vnode *getVnode(int vertex, int degree) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = vertex;
	newnode->indegree = degree;
	newnode->next = NULL;
	return newnode;
}

graph *G;
queue *Q;

void Init_Queue() {
	Q = (queue *)malloc(sizeof(queue));
	Q->front = NULL;
	Q->rear = NULL;
}

void enqueue(vnode *V, int cnt) {
	qnode *newnode = getQnode(V, cnt);
	if (Q->front == NULL) {
		Q->front = newnode;
		Q->rear = newnode;
	}
	else {
		Q->rear->next = newnode;
		Q->rear = newnode;
	}
}

qnode *dequeue() {
	qnode *res = Q->front;
	if (Q->front == NULL) {
		Q->rear = NULL;
	}
	else {
		Q->front = Q->front->next;
	}
	return res;
}

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		weight[i] = 0;
		G->adj_list[i] = getVnode(i, 0);
	}
	for (int i = 1; i <= N; i++) {
		scanf("%d", &weight[i]);
	}
}

void addEdge(int x, int y) {
	vnode *newnode = getVnode(y, 0);
	newnode->next = G->adj_list[x]->next;
	G->adj_list[x]->next = newnode;
	G->adj_list[y]->indegree++;
}

void Make_Graph() {
	for (int i = 0; i < K; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		addEdge(x, y);
	}
	scanf("%d", &W);
}

void topologicalsort() {
	int res[100000] = { 0, };
	int ans = 0;
	Init_Queue();
	for (int i = 1; i <= N; i++) {
		if (G->adj_list[i]->indegree == 0) {
			enqueue(G->adj_list[i], 0);
			res[i] = weight[i];
		}
	}
	while (Q->front != NULL && Q->rear != NULL) {
		qnode *tmp = dequeue();
		vnode *traverse = tmp->element->next;
		while (traverse != NULL) {
			G->adj_list[traverse->vertex]->indegree--;
			res[traverse->vertex] = Max(res[traverse->vertex], weight[traverse->vertex] + res[tmp->element->vertex]);
			if (G->adj_list[traverse->vertex]->indegree == 0) {
				enqueue(G->adj_list[traverse->vertex],tmp->cnt+1);
			}
			traverse = traverse->next;
		}
	}
	printf("%d\n", res[W]);
}

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		Init_Graph();
		Make_Graph();
		topologicalsort();
	}
	return 0;
}