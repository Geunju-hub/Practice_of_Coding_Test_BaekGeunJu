#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int N, M;
int graph[1002][1002] = { 0, };//2���� �迭
int visited[1002][1002][2] = { 0, };//���� ������ ���� �湮���� üũ
typedef struct Node {
	int i_idx;
	int j_idx;
	int cnt;
	int wall;
	struct Node *next;
}node;//ť�� ���� ��� ����ü

node *getnode(int i, int j, int cnt, int wall) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->i_idx = i;
	newnode->j_idx = j;
	newnode->cnt = cnt;
	newnode->wall = wall;
	newnode->next = NULL;
	return newnode;
}//ť�� ���� ��� ���� �Լ�

typedef struct Queue {
	node *front;
	node *rear;
}queue;//ť ����ü

queue *Q;

void Init_Queue() {
	Q = (queue *)malloc(sizeof(queue));
	Q->front = NULL;
	Q->rear = NULL;
	return Q;
}//ť �ʱ�ȭ

void enqueue(int start_i_idx, int start_j_idx, int cnt, int wall) {
	node *newnode = getnode(start_i_idx, start_j_idx, cnt, wall);
	if (Q->front == NULL) {
		Q->front = newnode;
		Q->rear = newnode;
	}
	else {
		Q->rear->next = newnode;
		Q->rear = newnode;
	}
}//ť�� ����

node *dequeue() {
	node *res = Q->front;
	Q->front = Q->front->next;
	if (Q->front == NULL) {
		Q->rear = NULL;
	}
	return res;
}//ť���� ����

void BFS(int start_i_idx, int start_j_idx, int cnt, int wallcnt) {
	Init_Queue();//ť �ʱ�ȭ
	visited[start_i_idx][start_j_idx][1] = 1;//1,1,1�湮(���ǰ���1)
	enqueue(start_i_idx, start_j_idx, cnt, wallcnt);
	while (Q->front != NULL && Q->rear != NULL) {//ť�� �� ������
		node *tmp = dequeue();//ť�� front���� ����
		int Wcnt = tmp->wall;
		if (tmp->i_idx == N && tmp->j_idx == M) {
			printf("%d", tmp->cnt+1);
			return;
		}//�ִܰŸ� ã���� cnt���
		else {//�ִܰŸ� �� ã���� ���
			int dx[4] = { -1,1,0,0 };
			int dy[4] = { 0,0,-1,1 };//x,y���� ������ Ȯ��
			for (int i = 0; i < 4; i++) {
				int newi = dy[i] + tmp->i_idx;
				int newj = dx[i] + tmp->j_idx;//������ ��ǥ
				if (newi >= 1 && newi <= N && newj >= 1 && newj <= M) {//��ǥ�� ���� �ȿ� ���� ��
					if (graph[newi][newj] == 1 && Wcnt == 1) {
						enqueue(newi, newj, tmp->cnt + 1, Wcnt - 1);
						visited[newi][newj][Wcnt - 1] = 1;
					}//���� ������ ��ġ�鼭 ���� �μ� �� ���� ��, �� �μ��� �̵� �� �湮 üũ
					else if(graph[newi][newj]==0 && visited[newi][newj][Wcnt]==0) {
						enqueue(newi, newj, tmp->cnt + 1, Wcnt);
						visited[newi][newj][Wcnt] = 1;
					}//���� �������� �ʴ� ��ġ�鼭 �湮���� �ʾ��� ��, �湮ǥ��
				}	
			}
		}
	}
	printf("-1");//�ִܰŸ� ��ã���� -1���
}

int main(void) {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%1d", &graph[i][j]);
		}
	}
	BFS(1, 1,0,1);
	return 0;
}