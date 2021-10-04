#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000

int F, S, G, U, D;
int visited[MAX_SIZE+1] = { 0, };//방문 여부 체크 배열
int queue[MAX_SIZE + 1][2] = { 0, };//위치와 횟수 담아줄 배열 선언
int front = 0, rear = 0;//큐의 인덱스

void enqueue(int i,int cnt) {
	rear = (rear + 1) % (MAX_SIZE);
	queue[rear][0] = i;
	queue[rear][1] = cnt;
}

int *dequeue() {
	front = (front + 1) % (MAX_SIZE+1);
	return queue[front];
}//원형큐로 구현

void BFS() {
	visited[S] = 1;
	enqueue(S,0);//시작지점 넣어줌
	while (front != rear) {//큐가 빌 때까지
		int *data = dequeue();//큐에서 데이터 추출
		int tmp = data[0];
		int cnt = data[1];//값 변수에 담아둠
		if (tmp == G) {
			printf("%d", cnt);
			return;//종료
		}//같은 위치라면 해당 위치까지 도달하는 최소 횟수 출력
		if (tmp+U>=1 && tmp + U <= F && visited[tmp + U] == 0) {
			visited[tmp + U] = 1;
			enqueue(tmp + U,cnt+1);
		}//방문하지 않았으면서 범위 내라면 방문표시 후 큐에 넣기
		if (tmp - D >=1 && tmp-D<=F&& visited[tmp - D] == 0) {
			visited[tmp - D] = 1;
			enqueue(tmp - D,cnt+1);
		}//마찬가지로 방문하지 않았으면서 범위 내라면 방문표시 후 큐에 넣기
	}
	printf("use the stairs");//와일문을 빠져나왔다 = 해당 층에 엘리베이터로 도달할 수 없다.
}

int main(void) {
	scanf("%d %d %d %d %d", &F, &S, &G, &U, &D);
	BFS();//최솟값 찾기 -> 큐를 이용한 BFS!
	return 0;
}