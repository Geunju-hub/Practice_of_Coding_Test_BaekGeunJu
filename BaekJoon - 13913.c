#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N, K;
int parent[100000 + 1] = { 0, };
int res[100000 + 1] = { 0, };
int visited[100000 + 1] = { 0, };
int queue[100000 + 1][3];
int front = 0, rear = 0;

void enqueue(int p, int i,int cnt) {
	rear = (rear + 1) % (100000 + 1);
	queue[rear][0] = p;
	queue[rear][1] = i;
	queue[rear][2] = cnt;
}

int *dequeue() {
	front = (front + 1) % (100000 + 1);
	return queue[front];
}

int main(void) {
	scanf("%d %d", &N, &K);
	for (int i = 0; i <= K; i++) {
		parent[i] = i;
	}
	visited[N] = 1;
	enqueue(0, N,0);
	while (front != rear) {
		int *tmp = dequeue();
		int p = tmp[0];
		int idx = tmp[1];
		int Cnt = tmp[2];
		parent[idx] = p;
		if (idx == K) {
			printf("%d\n", tmp[2]);
			int i = 0;
			while(1) {
				res[i++] = idx;
				if (idx == N) {
					break;
				}
				idx = parent[idx];
			}
			for (int j = i-1; j >= 0; j--) {
				printf("%d ", res[j]);
			}
			return 0;
		}
		if (idx - 1 >= 0 && idx - 1 <=100000 && visited[idx-1]==0) {
			visited[idx - 1] = 1;
			enqueue(idx, idx - 1,Cnt+1);
		}
		if (idx + 1 >= 0 && idx + 1 <=100000 && visited[idx+1]==0) {
			visited[idx + 1] = 1;
			enqueue(idx, idx + 1,Cnt+1);
		}
		if (idx * 2 >= 0 && idx * 2 <=100000 && visited[idx*2]==0) {
			visited[idx * 2] = 1;
			enqueue(idx, idx * 2,Cnt+1);
		}
	}
	return 0;
}