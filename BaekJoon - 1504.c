#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 800
#define MAX_EDGE 200000
#define INF 200000000

int Min(int a, int b) {
	return a > b ? b : a;
}//최솟값 구하는 함수 설정

int N, E;

typedef struct Vnode {
	int vertex;
	int weight;
	struct Vnode *next;
}vnode;//정점노드 구조체 선언

typedef struct Graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;//그래프 구조체 선언

typedef struct Heap {
	vnode *H_list[MAX_EDGE + 1];
	int size;
}heap;//힙 구조체 선언

graph *G;
heap *H;

void Init_Heap() {
	H = (heap *)malloc(sizeof(heap));
	H->size = 0;
}//힙 초기화 함수

void upHeap(int i) {
	while (i > 1) {
		if (H->H_list[i]->weight < H->H_list[i / 2]->weight) {
			vnode *tmp = H->H_list[i];
			H->H_list[i] = H->H_list[i / 2];
			H->H_list[i / 2] = tmp;
		}
		i /= 2;
	}
}//upHeap 함수

void addHeap(vnode *V) {
	H->H_list[++H->size] = V;
	upHeap(H->size);
}//힙에 넣고 최솟값 맨 위로 올리기

void downHeap(int i) {
	while (2 * i <= H->size) {
		int child = 2 * i;
		if (child + 1 <= H->size && H->H_list[child] > H->H_list[child + 1]) {
			child++;
		}
		if (H->H_list[child] < H->H_list[i]) {
			vnode *tmp = H->H_list[child];
			H->H_list[child] = H->H_list[i];
			H->H_list[i] = tmp;
			i = child;
		}
		else {
			return;
		}
	}
}//downHeap 구현

vnode *removeMin() {
	vnode *res = H->H_list[1];
	H->H_list[1] = H->H_list[H->size--];
	downHeap(1);
	return res;
}//다익스트라에서 쓰일 최소힙의 맨 윗부분 뽑기

vnode *getVnode(int V,int W) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = V;
	newnode->weight = W;
	newnode->next = NULL;
	return newnode;
}//Edge에 들어갈 정점 노드 생성 함수

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d", &N, &E);
	for (int i = 1; i <= N; i++) {
		G->adj_list[i] = getVnode(i, 0);
	}//헤드포인터 생성
}

void addEdge(int u, int v, int w) {
	//u->v의 edge생성
	vnode *newnode = getVnode(v, w);
	newnode->next = G->adj_list[u]->next;
	G->adj_list[u]->next = newnode;
	//v->u의 edge 생성
	vnode *newnode2 = getVnode(u, w);
	newnode2->next = G->adj_list[v]->next;
	G->adj_list[v]->next = newnode2;
}//양방향 간선 추가

void Make_Graph() {
	int u, v, w;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}
}//가중치 있는 양방향 그래프 그리기

void Daijkstra(int start, int end,int *dist) {
	Init_Heap();
	for (int i = 1; i <= N; i++) {
		dist[i] = INF;
	}
	dist[start] = 0;
	addHeap(G->adj_list[start]);
	while (H->size != 0) {
		vnode *tmp = removeMin();
		if (dist[tmp->vertex] < tmp->weight) {
			continue;
		}
		else {
			vnode *traverse = tmp->next;
			while (traverse != NULL) {
				if (dist[traverse->vertex] > dist[tmp->vertex] + traverse->weight) {
					dist[traverse->vertex] = dist[tmp->vertex] + traverse->weight;
					addHeap(G->adj_list[traverse->vertex]);
				}
				traverse = traverse->next;
			}
		}
	}
}

int main(void) {
	Init_Graph();//그래프 초기화
	Make_Graph();//그래프 생성
	int v1, v2;
	scanf("%d %d", &v1, &v2);
	int dist1[800 + 1],dist2[800+1],dist3[800+1];
	Daijkstra(1, N, dist1);//1->N까지 비용 계산
	Daijkstra(v1, N, dist2);//v1->N까지 비용 계산
	Daijkstra(v2, N, dist3);//v2->N까지 비용 계산
	int ans = Min(dist1[v1] + dist2[v2] + dist3[N], dist1[v2] + dist3[v1] + dist2[N]);
	//1->v1->v2->N 과 1->v2->v1->N의 최소비용 중 작은 것
	if (ans >= INF || ans < 0) {
		printf("-1");
	}//두 경로를 지나지 않는 경우 -1출력
	else {
		printf("%d", ans);
	}//지나면 최소비용 출력
	return 0;
}