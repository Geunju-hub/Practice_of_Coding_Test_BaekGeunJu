#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N,res;
int graph[26][26] = { 0, };//�ҹ��ڷ� ������� ����
int visited[26] = { 0, };//�湮����üũ �迭
int indegree[26] = { 0, };//�������� �迭
int queue[1000 + 1] = { 0, };//���� ť ����
int front = 0, rear = 0;
char str[100][11] = { '\0' };
char ans[100] = { '\0' };//���乮�ڿ�

void enqueue(int v) {
	rear = (rear + 1) % 1000;
	queue[rear] = v;
}//ť�� �� �ڿ� �־��ִ� �۾�

int dequeue() {
	front = (front + 1) % 1000;
	return queue[front];
}//ť�� �� ���� ���Ҹ� ���� �۾�

void Init_Graph() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", str[i]);
		int size = strlen(str[i]);
		for (int j = 0; j < size; j++) {
			visited[str[i][j] - 'a'] = 1;
		}//���ڿ� �Է� �� �湮����üũ
	}
}//�׷��� �ʱ�ȭ �Լ�

void Make_Graph() {
	for (int i = 0; i < N; i++) {
		int size1 = strlen(str[i]);
		for (int j = i + 1; j < N; j++) {
			int size2 = strlen(str[j]);
			for (int k = 0; k < size1; k++) {
				if (k >= size2) {
					res = -1;
					break;
				}//�� �Ұ��� ���
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
					}//���� �� ���� üũ + �������� �ø��� (���� �ݴ���� ���� -> ���� x )
					break;
				}
			}
		}
	}
}//�׷��� ���� �Լ�

void topologicalsort() {
	if (res == -1) {
		printf("!");
		return;
	}//res=-1 �� �ùٸ� ������ ���ٸ� !
	else {
		int Qcnt=0,cnt=0;
		for (int i = 0; i < 26; i++) {
			if (visited[i] == 1 && indegree[i] == 0) {
				enqueue(i);
				Qcnt++;
			}
		}//�湮�����鼭 ���������� 0�̸� ť�� �־���
		if (Qcnt == 0) {
			printf("!");
			return;
		}//ť �ȿ� ���Ұ� 0�̸� !���
		while (front != rear) {
			if (Qcnt > 1) {
				printf("?");
				return;
			}//ť�� �� ���Ұ� 2���̻��̴� = ������ �������� ����
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
			}//�׷����� �������� �ٿ����鼭 ���������� 0�̸� ť�� �־���
		}//ť�� ����� ������
		for (int i = 0; i < cnt; i++) {
			printf("%c", ans[i]);
		}//������ ������ �ִٸ� ���
	}

}

int main(void) {
	Init_Graph();
	Make_Graph();
	topologicalsort();//��������
	return 0;
}