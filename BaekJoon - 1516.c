#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 500
int N;
int weight[MAX_VERTEX + 1] = { 0, };
long long res[MAX_VERTEX + 1] = { 0, };

long long Max(long long a, long long b) {
	return a > b ? a : b;
}

typedef struct Vnode {
	int vertex;
	int indegree;
	struct Vnode *next;
}vnode;

typedef struct Qnode {
	vnode *element;
	int cnt;
	struct Qnode *next;
}qnode;

typedef struct Graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;

typedef struct Queue {
	qnode *front;
	qnode *rear;
}queue;

graph *G;
queue *Q;

qnode *getQnode(vnode *V, int cnt) {
	qnode *newnode = (qnode *)malloc(sizeof(qnode));
	newnode->element = V;
	newnode->cnt = cnt;
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
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		G->adj_list[i] = getVnode(i, 0);
	}
}

void addEdge(int u, int v) {
	//v->u의 방향성
	vnode *newnode = getVnode(u, 0);
	newnode->next = G->adj_list[v]->next;
	G->adj_list[v]->next = newnode;
	G->adj_list[u]->indegree++;
}

void Make_Graph() {
	for (int i = 1; i <= N; i++) {
		scanf("%d", &weight[i]);
		int connected;
		while (1) {
			scanf("%d", &connected);
			if (connected == -1) {
				break;
			}
			else {
				addEdge(i, connected);
			}
		}
	}
}

void topologicalsort() {
	Init_Queue();
	for (int i = 1; i <= N; i++) {
		if (G->adj_list[i]->indegree == 0) { 
			enqueue(G->adj_list[i], 0);
		}
	}
	while (Q->front != NULL && Q->rear != NULL) {
		qnode *tmp = dequeue();
		int p = res[tmp->element->vertex];
		vnode *traverse = tmp->element->next;
		while (traverse != NULL) {
			G->adj_list[traverse->vertex]->indegree--;
			res[traverse->vertex] = Max(res[traverse->vertex], p + weight[tmp->element->vertex]);
			if (G->adj_list[traverse->vertex]->indegree == 0) {
				enqueue(G->adj_list[traverse->vertex], tmp->cnt + 1);
			}
			traverse = traverse->next;
		}
	}
	for (int i = 1; i <= N; i++) {
		printf("%lld\n", res[i]+weight[i]);
	}
}

int main(void) {
	Init_Graph();
	Make_Graph();
	topologicalsort();
	return 0;
}