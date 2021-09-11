//BaekJoon 1766. solved by c - topological sort(C���� Ǭ ��������)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 32000
#define MAX_EDGE 100000

int N, M;
int res[MAX_VERTEX + 1] = { 0, };//����� �Ű��� res �迭 ����

typedef struct vnode {
	int vertex;
	int indegree;
	struct vnode *next;
}vnode;//���� ����ü ����

typedef struct Heap {
	vnode *H_list[MAX_EDGE + 1];
	int size;
}heap;//�ʿ��� �� ����ü ����

typedef struct graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;//��������Ʈ ����

heap *H;
graph *G;//���� Ǯ�̿� �����ϰ� �ϱ� ���� ���� ������ ����

vnode *getvnode(int i) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = i;
	newnode->indegree = 0;
	newnode->next = NULL;
	return newnode;
}//������� ���� �Լ�

void Init_Heap() {
	H = (heap *)malloc(sizeof(heap));
	H->size = 0;
}//�� ����ü �ʱ�ȭ �Լ�

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		G->adj_list[i] = getvnode(i);
	}
}//�׷��� �ʱ�ȭ �Լ�

void upHeap(int i) {
	while (i > 1) {
		if (H->H_list[i]->vertex < H->H_list[i / 2]->vertex) {
			vnode *tmp = H->H_list[i];
			H->H_list[i] = H->H_list[i / 2];
			H->H_list[i / 2] = tmp;
			i /= 2;
		}
		else {
			return;
		}
	}
}//�ּ� ���� ����� �ֱ� ���� upHeap ����

void downHeap(int i) {
	while (2 * i <= H->size) {
		int child = 2 * i;
		if (child + 1 <= H->size && H->H_list[child]->vertex > H->H_list[child + 1]->vertex) {
			child++;
		}
		if (H->H_list[child]->vertex < H->H_list[i]->vertex) {
			vnode *tmp = H->H_list[child];
			H->H_list[child] = H->H_list[i];
			H->H_list[i] = tmp;
			i = child;
		}
		else {
			return;
		}
	}
}//���ְ� �� ���� ���� Heap ���� �����ϱ� ���� downHeap�Լ� ����

void addHeap(vnode *V) {
	H->H_list[++H->size] = V;
	upHeap(H->size);
}//���� ���ο� ��� �߰�

vnode *removeMin() {
	vnode *res = H->H_list[1];
	H->H_list[1] = H->H_list[H->size--];
	downHeap(1);
	return res;
}//������ ���� ���� ��� ���� �� �� Ư�� ����

void addEdge(int u, int v) {
	vnode *newnode = getvnode(v);
	newnode->next = G->adj_list[u]->next;
	G->adj_list[u]->next = newnode;
	G->adj_list[v]->indegree++;
}//���ο� ��� ���� �� �������� ����

void Make_Graph() {
	for (int i = 0; i < M; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}
}//�׷��� �����Լ�

void topologicalsort() {
	Init_Heap();
	for (int i = 1; i <= N; i++) {
		if (G->adj_list[i]->indegree == 0) {
			addHeap(G->adj_list[i]);
		}
	}//�ʱ⿡ ���������� 0�� ���� ��� ���� �ֱ�
	int cnt = 0, k = 0;
	while (H->size!=0) {
		vnode *tmp = removeMin();
		res[++k] = tmp->vertex;
		vnode *traverse = tmp->next;
		while (traverse != NULL) {
			int v = traverse->vertex;
			G->adj_list[v]->indegree--;
			if (G->adj_list[v]->indegree == 0) {
				addHeap(G->adj_list[v]);
			}
			traverse = traverse->next;
		}
		cnt++;
	}//�ϳ��ϳ� õõ�� �����ϸ鼭 ���������� 0�̵Ǹ� �־���.
	for (int i = 1; i <= k; i++) {
		printf("%d ", res[i]);
	}//������� ���
}

int main(void) {
	Init_Graph();
	Make_Graph();
	topologicalsort();
	return 0;
}