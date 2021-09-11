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
}vnode;// ���� ����Ʈ�� �� ���� ��� : ����ġ�� ���� ��ȣ �׸��� ���� ��ũ�� ����� ����.

typedef struct Graph {
	vnode *adj_list[MAX_VERTEX + 1];
}graph;//��������Ʈ ���� : c++������ vector�� ǥ�� ����

typedef struct Heap {
	vnode *E_heap[MAX_EDGE + 1];
	int size;
}heap;//�ּ� �� ���� ���� �� ����ü ���� �� ���ҷ� ���� ��带 ������ ��.

graph *G;
heap *H;//�ڵ带 �����ϰ� �ϱ� ���� ���������� ����

vnode *getVnode(int u, int w) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->vertex = u;
	newnode->weight = w;
	newnode->next = NULL;
	return newnode;
}// ���ο� ���� ��� ���� �Լ�. ����u�� ����ġ w�� ������ �� ��忡 �־ �� ��带 ��ȯ��.

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d %d %d", &N, &M, &s);
	for (int i = 1; i <= N; i++) {
		dist[i] = INF;
		G->adj_list[i] = getVnode(i, 0);
	}
}//�ʱ� �׷��� ���� dist �迭 : ���� �������κ��� �ش� ���� ������ �Ÿ��� ��Ÿ���� �迭
//�ʱ⿡�� �ƹ��͵� ������ ���� ���⿡ INF�� ������.

void addEdge(int u, int v, int w) {
	vnode *p1 = G->adj_list[u];
	vnode *newnode1 = getVnode(v, w);
	newnode1->next = p1->next;
	p1->next = newnode1;
}//���� ���� : stack���� �� ��带 top�� �������ִ� ��ó�� �� ��带 ��������.
//���⼺�� �ִ� �׷����̱� ������ �ݴ����� ���� ������ �� �ʿ� ����.

void Make_Graph() {
	for (int i = 0; i < M; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}
}//�ʱ� �׷��� ���� �Լ�

void Init_Heap() {
	H = (heap *)malloc(sizeof(heap));
	H->size = 0;
}//�� �ʱ�ȭ �Լ�

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
}//�ּ��� ���� �� upHeap �Լ� : �θ���� �ö󰡸鼭 
//1) ����ġ�� �������� 2) ����ġ�� ���ٸ� ���� ��ȣ�� ���� ������ �ֻ�ܿ� ���̰� ������.

void addHeap(vnode *E) {
	H->E_heap[++H->size] = E;
	upHeap(H->size);
}//���� �߰��ϴ� �Լ� 

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
}//downHeap �Լ�
// ���� ������ �ڽ� �� �� ���� �ڽ��� ��� �θ���� �� �� Ư�� ���� ������ ��ȯ

vnode *removeMin() {
	vnode *res = H->E_heap[1];
	H->E_heap[1] = H->E_heap[H->size--];
	downHeap(1);
	return res;
}//��Ʈ ��� ��ȯ �� ũ�� 1 ���̰� ��Ʈ�� ������ ���� ���� �� downHeap ���� : Heap�� Ư�� ����

void DaijkstraShortestPaths_Algorithm() {
	Init_Heap();//�� �̿� ���� �ʱ��� ����
	dist[s] = 0;
	int F = s;// ���� ���� ����
	addHeap(G->adj_list[s]);
	while (H->size != 0) {
		vnode *from = removeMin();//���� ���� �� ��ȯ
		vnode *traverse = G->adj_list[from->vertex]->next;
		F = from->vertex;
		if (dist[F] < from->weight) {
			continue;
		}//�ð� �ʰ��� ���� ���� �̹� �۴ٸ� ���� �ܰ�� ����
		while (traverse != NULL) {
			int comp = dist[F] + traverse->weight;
			if (dist[traverse->vertex] > comp) {
				dist[traverse->vertex] = comp;
				traverse->weight = comp;
				addHeap(traverse);
			}
			traverse = traverse->next;
		}//���� �ٲ��� �ʿ伺�� �ִٸ� Ž���ϸ� �� �ٲ��ְ� ���� �߰�
	}
	for (int i = 1; i <= N; i++) {
		if (dist[i] == INF) {
			printf("INF\n");
		}
		else {
			printf("%d\n", dist[i]);
		}
	}//���� ������� ���.
}


int main(void) {
	Init_Graph(); // �׷��� �ʱ� ���� �� ���� ����
	Make_Graph(); // ���� ����
	DaijkstraShortestPaths_Algorithm(); // ���ͽ�Ʈ�� �ִܰŸ� �Լ�
	return 0;
}