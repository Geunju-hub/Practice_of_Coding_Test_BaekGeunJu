//BaekJoon - 1753 solved by c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 200000000
#define MAX_VERTEX 20000
#define MAX_EDGE 300000
int dist[MAX_VERTEX + 1] = { 0, };
int N, M, s;

typedef struct Vnode {
	int vertex;
	int weight;
	struct Vnode *next;
}vnode;// 인접 리스트에 들어갈 정점 노드 : 가중치와 정점 번호 그리고 다음 링크를 멤버로 가짐.

typedef struct Graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;//인접리스트 구현 : c++에서는 vector로 표현 가능

typedef struct Heap {
	vnode *E_heap[MAX_EDGE + 1];
	int size;
}heap;//최소 힙 구현 위해 힙 구조체 선언 및 원소로 정점 노드를 가지게 함.

graph *G;
heap *H;//코드를 간편하게 하기 위해 전역변수로 설정

vnode *getVnode(int u, int w) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = u;
	newnode->weight = w;
	newnode->next = NULL;
	return newnode;
}// 새로운 정점 노드 생성 함수. 정점u와 가중치 w를 받으면 새 노드에 넣어서 새 노드를 반환함.

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d %d", &N, &M, &s);
	for (int i = 1; i <= N; i++) {
		dist[i] = INF;
		G->adj_list[i] = getVnode(i, 0);
	}
}//초기 그래프 생성 dist 배열 : 시작 정점으로부터 해당 점점 사이의 거리를 나타내는 배열
//초기에는 아무것도 정해진 것이 없기에 INF로 정의함.

void addEdge(int u, int v, int w) {
	vnode *p1 = G->adj_list[u];
	vnode *newnode1 = getVnode(v, w);
	newnode1->next = p1->next;
	p1->next = newnode1;
}//간선 연결 : stack에서 새 노드를 top과 연결해주는 것처럼 두 노드를 연결해줌.
//방향성이 있는 그래프이기 때문에 반대쪽은 따로 생성해 줄 필요 없음.

void Make_Graph() {
	for (int i = 0; i < M; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}
}//초기 그래프 구현 함수

void Init_Heap() {
	H = (heap *)malloc(sizeof(heap));
	H->size = 0;
}//힙 초기화 함수

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
			else {
				return;
			}
		}
		else {
			return;
		}
		upHeap(i / 2);
	}
	else {
		return;
	}
}//최소힙 구현 중 upHeap 함수 : 부모노드로 올라가면서 
//1) 가중치가 작을수록 2) 가중치가 같다면 정점 번호가 작은 순으로 최상단에 놓이게 설정함.

void addHeap(vnode *E) {
	H->E_heap[++H->size] = E;
	upHeap(H->size);
}//힙에 추가하는 함수 

void downHeap(int i) {
	if (2 * i <= H->size) {
		int child = 2 * i;
		if (child + 1 <= H->size) {
			if (H->E_heap[child]->weight > H->E_heap[child + 1]->weight) {
				child++;
			}
			else if (H->E_heap[child]->weight == H->E_heap[child + 1]->weight) {
				if (H->E_heap[child]->vertex > H->E_heap[child + 1]->vertex) {
					child++;
				}
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
			else {
				return;
			}
		}
		else {
			return;
		}
		downHeap(child);
	}
	else {
		return;
	}
}//downHeap 함수
// 왼쪽 오른쪽 자식 중 더 작은 자식을 골라 부모노드와 비교 후 특정 조건 만족시 교환

vnode *removeMin() {
	vnode *res = H->E_heap[1];
	H->E_heap[1] = H->E_heap[H->size--];
	downHeap(1);
	return res;
}//루트 노드 반환 후 크기 1 줄이고 루트에 마지막 값을 넣은 후 downHeap 진행 : Heap의 특성 유지

void DaijkstraShortestPaths_Algorithm() {
	Init_Heap();//힙 이용 위해 초기힙 생성
	dist[s] = 0;
	int F = s;// 시작 지점 설정
	addHeap(G->adj_list[s]);
	while (H->size != 0) {
		vnode *from = removeMin();//제일 작은 값 반환
		vnode *traverse = G->adj_list[from->vertex]->next;
		F = from->vertex;
		if (dist[F] < from->weight) {
			continue;
		}//시간 초과를 막기 위해 이미 작다면 다음 단계로 진행
		while (traverse != NULL) {
			int comp = dist[F] + traverse->weight;
			if (dist[traverse->vertex] > comp) {
				dist[traverse->vertex] = comp;
				traverse->weight = comp;
				addHeap(traverse);
			}
			traverse = traverse->next;
		}//값을 바꿔줄 필요성이 있다면 탐색하며 값 바꿔주고 힙에 추가
	}
	for (int i = 1; i <= N; i++) {
		if (dist[i] == INF) {
			printf("INF\n");
		}
		else {
			printf("%d\n", dist[i]);
		}
	}//정점 순서대로 출력.
}


int main(void) {
	Init_Graph(); // 그래프 초기 생성 및 정점 생성
	Make_Graph(); // 간선 연결
	DaijkstraShortestPaths_Algorithm(); // 다익스트라 최단거리 함수
	return 0;
}