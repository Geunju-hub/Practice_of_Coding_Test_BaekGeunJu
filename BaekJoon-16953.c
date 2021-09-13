#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	long long element;
	int cnt;
	struct node *next;
}node;

typedef struct Qnode {
	node *E;
	struct Qnode *next;
}Qnode;

typedef struct queue {
	Qnode *front;
	Qnode *rear;
}queue;

queue *Q;

node *getnode(long long i, int c) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = i;
	newnode->cnt = c;
	newnode->next = NULL;
	return newnode;
}

Qnode *getQnode(node *e) {
	Qnode *newnode = (Qnode *)malloc(sizeof(Qnode));
	newnode->E = e;
	newnode->next = NULL;
	return newnode;
}

void Init_Queue() {
	Q = (queue *)malloc(sizeof(queue));
	Q->front = NULL;
	Q->rear = NULL;
}

void enqueue(long long A, int count) {
	node *I = getnode(A, count);
	Qnode *newnode = getQnode(I);
	if (Q->front == NULL) {
		Q->front = newnode;
		Q->rear=newnode;
	}
	else {
		Q->rear->next = newnode;
		Q->rear = newnode;
	}
}

node *dequeue() {
	if (Q->front == Q->rear) {
		node *res = Q->front->E;
		Q->front = NULL;
		Q->rear = NULL;
		return res;
	}
	else {
		node *res = Q->front->E;
		Q->front = Q->front->next;
		return res;
	}
}

void BFS(long long A,long long B) {
	Init_Queue();
	enqueue(A,1);
	while (Q->front!=NULL) {
		node *tmp = dequeue();
		if (tmp->element == B) {
			printf("%d", tmp->cnt);
			return;
		}
		else {
			long long C = tmp->element,newcnt=tmp->cnt;
			if (C * 2 <= B) {
				enqueue(C * 2, newcnt + 1);
			}
			if (C * 10 + 1 <= B) {
				enqueue(C * 10 + 1, newcnt + 1);
			}
		}
	}
	printf("-1");
	return;
}

int main(void) {
	long long A, B;
	scanf("%lld %lld", &A, &B);
	BFS(A,B);
	return 0;
}