//BaekJoon 1766. solved by c - topological sort(C언어로 푼 위상정렬)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 32000
#define MAX_EDGE 100000

int N, M;
int res[MAX_VERTEX + 1] = { 0, };//결과를 옮겨줄 res 배열 선언

typedef struct vnode {
	int vertex;
	int indegree;
	struct vnode *next;
}vnode;//정점 구조체 선언

typedef struct Heap {
	vnode *H_list[MAX_EDGE + 1];
	int size;
}heap;//필요한 힙 구조체 선언

typedef struct graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;//인접리스트 선언

heap *H;
graph *G;//문제 풀이에 용이하게 하기 위해 전역 변수로 설정

vnode *getvnode(int i) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = i;
	newnode->indegree = 0;
	newnode->next = NULL;
	return newnode;
}//정점노드 생성 함수

void Init_Heap() {
	H = (heap *)malloc(sizeof(heap));
	H->size = 0;
}//힙 구조체 초기화 함수

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		G->adj_list[i] = getvnode(i);
	}
}//그래프 초기화 함수

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
}//최소 힙을 만들어 주기 위해 upHeap 구현

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
}//빼주고 난 이후 원래 Heap 성질 유지하기 위한 downHeap함수 설정

void addHeap(vnode *V) {
	H->H_list[++H->size] = V;
	upHeap(H->size);
}//힙에 새로운 노드 추가

vnode *removeMin() {
	vnode *res = H->H_list[1];
	H->H_list[1] = H->H_list[H->size--];
	downHeap(1);
	return res;
}//힙에서 가장 작은 노드 제거 후 힙 특성 유지

void addEdge(int u, int v) {
	vnode *newnode = getvnode(v);
	newnode->next = G->adj_list[u]->next;
	G->adj_list[u]->next = newnode;
	G->adj_list[v]->indegree++;
}//새로운 노드 연결 및 진입차수 증가

void Make_Graph() {
	for (int i = 0; i < M; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}
}//그래프 생성함수

void topologicalsort() {
	Init_Heap();
	for (int i = 1; i <= N; i++) {
		if (G->adj_list[i]->indegree == 0) {
			addHeap(G->adj_list[i]);
		}
	}//초기에 진입차수가 0인 점들 모두 힙에 넣기
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
	}//하나하나 천천히 제거하면서 진입차수가 0이되면 넣어줌.
	for (int i = 1; i <= k; i++) {
		printf("%d ", res[i]);
	}//결과값들 출력
}

int main(void) {
	Init_Graph();
	Make_Graph();
	topologicalsort();
	return 0;
}