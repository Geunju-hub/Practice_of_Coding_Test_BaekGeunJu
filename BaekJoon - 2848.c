#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N,res;
int graph[26][26] = { 0, };//소문자로 인접행렬 생성
int visited[26] = { 0, };//방문여부체크 배열
int indegree[26] = { 0, };//진입차수 배열
int queue[1000 + 1] = { 0, };//원형 큐 선언
int front = 0, rear = 0;
char str[100][11] = { '\0' };
char ans[100] = { '\0' };//정답문자열

void enqueue(int v) {
	rear = (rear + 1) % 1000;
	queue[rear] = v;
}//큐의 맨 뒤에 넣어주는 작업

int dequeue() {
	front = (front + 1) % 1000;
	return queue[front];
}//큐의 맨 앞의 원소를 빼는 작업

void Init_Graph() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", str[i]);
		int size = strlen(str[i]);
		for (int j = 0; j < size; j++) {
			visited[str[i][j] - 'a'] = 1;
		}//문자열 입력 후 방문여부체크
	}
}//그래프 초기화 함수

void Make_Graph() {
	for (int i = 0; i < N; i++) {
		int size1 = strlen(str[i]);
		for (int j = i + 1; j < N; j++) {
			int size2 = strlen(str[j]);
			for (int k = 0; k < size1; k++) {
				if (k >= size2) {
					res = -1;
					break;
				}//비교 불가일 경우
				else {
					int u = str[i][k] - 'a', v = str[j][k] - 'a';
					if (u == v) {
						continue;
					}
					if (graph[u][v] == 0) {
						graph[u][v] = 1;
						indegree[v]++;
						if (graph[v][u] == 1) {
							res = -1;
						}
					}//없을 때 방향 체크 + 진입차수 늘리기 (만약 반대방향 존재 -> 결정 x )
					break;
				}
			}
		}
	}
}//그래프 생성 함수

void topologicalsort() {
	if (res == -1) {
		printf("!");
		return;
	}//res=-1 즉 올바른 순서가 없다면 !
	else {
		int Qcnt=0,cnt=0;
		for (int i = 0; i < 26; i++) {
			if (visited[i] == 1 && indegree[i] == 0) {
				enqueue(i);
				Qcnt++;
			}
		}//방문했으면서 진입차수가 0이면 큐에 넣어줌
		if (Qcnt == 0) {
			printf("!");
			return;
		}//큐 안에 원소가 0이면 !출력
		while (front != rear) {
			if (Qcnt > 1) {
				printf("?");
				return;
			}//큐에 들어간 원소가 2개이상이다 = 순서가 여러가지 가능
			int v = dequeue();
			Qcnt--;
			ans[cnt++]=v+'a';
			for (int i = 0; i < 26; i++) {
				if (graph[v][i] == 1) {
					indegree[i]--;
					if (indegree[i] == 0) {
						enqueue(i);
						Qcnt++;
					}
				}
			}//그래프의 진입차수 줄여가면서 진입차수가 0이면 큐에 넣어줌
		}//큐가 비워질 때까지
		for (int i = 0; i < cnt; i++) {
			printf("%c", ans[i]);
		}//가능한 순서가 있다면 출력
	}

}

int main(void) {
	Init_Graph();
	Make_Graph();
	topologicalsort();//위상정렬
	return 0;
}