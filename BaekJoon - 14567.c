#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 1000
#define MAX_EDGE 500000

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
	int cnt;
	struct Qnode *next;
}Qnode;

typedef struct Queue {
	Qnode *front;
	Qnode *rear;
}queue;

graph *G;
queue *Q;

void Init_Queue() {
	Q = (queue *)malloc(sizeof(queue));
	Q->front = NULL;
	Q->rear = NULL;
	return;
}

Qnode *getQnode(vnode *I,int Cnt) {
	Qnode *newnode = (Qnode *)malloc(sizeof(Qnode));
	newnode->element = I;
	newnode->cnt = Cnt;
	newnode->next = NULL;
	return newnode;
}

void enqueue(vnode *I,int Cnt) {
	Qnode *newnode = getQnode(I, Cnt);
	if (Q->rear == NULL) {
		Q->rear = newnode;
		Q->front = newnode;
	}
	else {
		Q->rear->next = newnode;
		Q->rear = newnode;
	}
}

Qnode *dequeue() {
	if (Q->front == Q->rear) {
		Qnode *res = Q->front;
		Q->front = NULL;
		Q->rear = NULL;
		return res;
	}
	else {
		Qnode *res = Q->front;
		Qnode *F = Q->front;
		Q->front = Q->front->next;
		return res;
	}
}

vnode *getVnode(int v, int id) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = v;
	newnode->indegree = id;
	newnode->next = NULL;
	return newnode;
}

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		G->adj_list[i] = getVnode(i,0);
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
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}
}

void topological() {
	int res[MAX_VERTEX + 1] = { 0, };
	Init_Queue();
	for (int i = 1; i <= N; i++) {
		if (G->adj_list[i]->indegree == 0) {
			enqueue(G->adj_list[i], 1);
		}
	}
	while (Q->front != NULL && Q->rear!=NULL) {
		Qnode *tmp = dequeue();
		res[tmp->element->vertex] = tmp->cnt;
		vnode *traverse = tmp->element->next;
		while (traverse != NULL) {
			G->adj_list[traverse->vertex]->indegree--;
			if (G->adj_list[traverse->vertex]->indegree == 0) {
				enqueue(G->adj_list[traverse->vertex], tmp->cnt + 1);
			}
			traverse = traverse->next;
		}
	}
	for (int i = 1; i <= N; i++) {
		printf("%d ", res[i]);
	}
}

int main(void) {
	Init_Graph();
	Make_Graph();
	topological();
	return 0;
}