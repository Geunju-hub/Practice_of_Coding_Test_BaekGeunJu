#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int N, M;
int graph[1002][1002] = { 0, };//2차원 배열
int visited[1002][1002][2] = { 0, };//벽의 개수에 따른 방문여부 체크
typedef struct Node {
	int i_idx;
	int j_idx;
	int cnt;
	int wall;
	struct Node *next;
}node;//큐에 들어가는 노드 구조체

node *getnode(int i, int j, int cnt, int wall) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->i_idx = i;
	newnode->j_idx = j;
	newnode->cnt = cnt;
	newnode->wall = wall;
	newnode->next = NULL;
	return newnode;
}//큐에 들어가는 노드 생성 함수

typedef struct Queue {
	node *front;
	node *rear;
}queue;//큐 구조체

queue *Q;

void Init_Queue() {
	Q = (queue *)malloc(sizeof(queue));
	Q->front = NULL;
	Q->rear = NULL;
	return Q;
}//큐 초기화

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
}//큐에 삽입

node *dequeue() {
	node *res = Q->front;
	Q->front = Q->front->next;
	if (Q->front == NULL) {
		Q->rear = NULL;
	}
	return res;
}//큐에서 빼기

void BFS(int start_i_idx, int start_j_idx, int cnt, int wallcnt) {
	Init_Queue();//큐 초기화
	visited[start_i_idx][start_j_idx][1] = 1;//1,1,1방문(벽의개수1)
	enqueue(start_i_idx, start_j_idx, cnt, wallcnt);
	while (Q->front != NULL && Q->rear != NULL) {//큐가 빌 때까지
		node *tmp = dequeue();//큐의 front원소 제거
		int Wcnt = tmp->wall;
		if (tmp->i_idx == N && tmp->j_idx == M) {
			printf("%d", tmp->cnt+1);
			return;
		}//최단거리 찾으면 cnt출력
		else {//최단거리 못 찾았을 경우
			int dx[4] = { -1,1,0,0 };
			int dy[4] = { 0,0,-1,1 };//x,y방향 움직임 확인
			for (int i = 0; i < 4; i++) {
				int newi = dy[i] + tmp->i_idx;
				int newj = dx[i] + tmp->j_idx;//움직인 좌표
				if (newi >= 1 && newi <= N && newj >= 1 && newj <= M) {//좌표가 범위 안에 있을 때
					if (graph[newi][newj] == 1 && Wcnt == 1) {
						enqueue(newi, newj, tmp->cnt + 1, Wcnt - 1);
						visited[newi][newj][Wcnt - 1] = 1;
					}//벽이 존재한 위치면서 벽을 부술 수 있을 때, 벽 부수고 이동 후 방문 체크
					else if(graph[newi][newj]==0 && visited[newi][newj][Wcnt]==0) {
						enqueue(newi, newj, tmp->cnt + 1, Wcnt);
						visited[newi][newj][Wcnt] = 1;
					}//벽이 존재하지 않는 위치면서 방문하지 않았을 때, 방문표시
				}	
			}
		}
	}
	printf("-1");//최단거리 못찾으면 -1출력
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