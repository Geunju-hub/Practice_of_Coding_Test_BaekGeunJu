#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int S;
int queue[100000 + 1][3] = { 0, };
int visited[1000 + 1][1000 + 1] = { 0, };
int front = 0, rear = 0;

void enqueue(int data, int clip, int cnt) {
	rear = (rear + 1) % (100000);
	queue[rear][0] = data;
	queue[rear][1] = clip;
	queue[rear][2] = cnt;
}

int *dequeue() {
	front = (front + 1) % (100000);
	return queue[front];
}

int main(void) {
	scanf("%d", &S);
	visited[1][0] = 1;
	enqueue(1, 0, 0);
	while (front != rear) {
		int *tmp = dequeue();
		int data = tmp[0];
		int clip = tmp[1];
		int Cnt = tmp[2];
		if (data == S) {
			printf("%d", Cnt);
			return 0;
		}
		else {
			if (data > 0 && data <= 1000 && visited[data][data]==0) {
				visited[data][data] = 1;
				enqueue(data, data, Cnt + 1);
			}
			if (clip > 0) {
				if (data + clip > 0 && data + clip <= 1000 && visited[data+clip][clip]==0) {
					visited[data + clip][clip] = 1;
					enqueue(data + clip, clip, Cnt + 1);
				}
				if (data - 1 >= 0 && data - 1 <= 1000 && visited[data-1][clip]==0) {
					visited[data - 1][clip] = 1;
					enqueue(data - 1, clip, Cnt + 1);
				}
			}
		}
	}
	return 0;
}