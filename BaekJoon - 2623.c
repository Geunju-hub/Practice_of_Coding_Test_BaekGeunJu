#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 1000
int N, M;

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
	struct Qnode *next;
}qnode;

typedef struct Queue {
	qnode *front;
	qnode *rear;
}queue;

vnode *getVnode(int vertex, int indegree) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = vertex;
	newnode->indegree = indegree;
	newnode->next = NULL;
	return newnode;
}

qnode *getQnode(vnode *element) {
	qnode *newnode = (qnode *)malloc(sizeof(qnode));
	newnode->element = element;
	newnode->next = NULL;
	return newnode;
}

graph *G;
queue *Q;

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		G->adj_list[i] = getVnode(i, 0);
	}
}

void addEdge(int u, int v) {
	vnode *newnode = getVnode(v, 0);
	newnode->next = G->adj_list[u]->next;
	G->adj_list[u]->next = newnode;
	G->adj_list[v]->indegree++;
}

void Make_Graph() {
	for (int i = 0; i < M; i++) {
		int n;
		scanf("%d", &n);
		int tmp1,tmp2;
		scanf("%d", &tmp1);
		for (int j = 1; j < n; j++) {
			scanf("%d", &tmp2);
			addEdge(tmp1, tmp2);
			tmp1 = tmp2;
		}
	}
}

void Init_Queue() {
	Q = (queue *)malloc(sizeof(queue));
	Q->front = NULL;
	Q->rear = NULL;
}

void enqueue(vnode *V) {
	qnode *newnode = getQnode(V);
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

void topologicalsort() {
	int res[1000 + 1] = { 0, }, cnt = 0;
	Init_Queue();
	for (int i = 1; i <= N; i++) {
		if (G->adj_list[i]->indegree == 0) {
			enqueue(G->adj_list[i]);
		}
	}
	while (Q->front != NULL && Q->rear != NULL) {
		qnode *tmp = dequeue();
		int v = tmp->element->vertex;
		res[cnt++] = v;
		vnode *traverse = tmp->element->next;
		while (traverse != NULL) {
			G->adj_list[traverse->vertex]->indegree--;
			if (G->adj_list[traverse->vertex]->indegree == 0) {
				enqueue(G->adj_list[traverse->vertex]);
			}
			traverse = traverse->next;
		}
	}
	if (cnt != N) {
		printf("0");
	}
	else {
		for (int i = 0; i < cnt; i++) {
			printf("%d\n", res[i]);
		}
	}
}

int main(void) {
	Init_Graph();
	Make_Graph();
	topologicalsort();
	return 0;
}