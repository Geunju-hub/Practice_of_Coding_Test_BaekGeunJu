#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000

int F, S, G, U, D;
int visited[MAX_SIZE+1] = { 0, };//�湮 ���� üũ �迭
int queue[MAX_SIZE + 1][2] = { 0, };//��ġ�� Ƚ�� ����� �迭 ����
int front = 0, rear = 0;//ť�� �ε���

void enqueue(int i,int cnt) {
	rear = (rear + 1) % (MAX_SIZE);
	queue[rear][0] = i;
	queue[rear][1] = cnt;
}

int *dequeue() {
	front = (front + 1) % (MAX_SIZE+1);
	return queue[front];
}//����ť�� ����

void BFS() {
	visited[S] = 1;
	enqueue(S,0);//�������� �־���
	while (front != rear) {//ť�� �� ������
		int *data = dequeue();//ť���� ������ ����
		int tmp = data[0];
		int cnt = data[1];//�� ������ ��Ƶ�
		if (tmp == G) {
			printf("%d", cnt);
			return;//����
		}//���� ��ġ��� �ش� ��ġ���� �����ϴ� �ּ� Ƚ�� ���
		if (tmp+U>=1 && tmp + U <= F && visited[tmp + U] == 0) {
			visited[tmp + U] = 1;
			enqueue(tmp + U,cnt+1);
		}//�湮���� �ʾ����鼭 ���� ����� �湮ǥ�� �� ť�� �ֱ�
		if (tmp - D >=1 && tmp-D<=F&& visited[tmp - D] == 0) {
			visited[tmp - D] = 1;
			enqueue(tmp - D,cnt+1);
		}//���������� �湮���� �ʾ����鼭 ���� ����� �湮ǥ�� �� ť�� �ֱ�
	}
	printf("use the stairs");//���Ϲ��� �������Դ� = �ش� ���� ���������ͷ� ������ �� ����.
}

int main(void) {
	scanf("%d %d %d %d %d", &F, &S, &G, &U, &D);
	BFS();//�ּڰ� ã�� -> ť�� �̿��� BFS!
	return 0;
}