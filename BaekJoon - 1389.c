#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 200000000//INF�ִ�ġ ����

int dist[101][101] = { 0, };//�������
int res[101] = { 0, };//��� ��Ƶ� �迭

int Min(int a, int b) {
	return a > b ? b : a;
}//�ּڰ� ã�� �Լ�

int main(void) {
	int N, M, ans = 1;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}//������� �ʱ�ȭ
	for (int i = 0; i < M; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		dist[u][v] = 1;
		dist[v][u] = 1;
	}//�Է¹ް� ģ������ ���� ����
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				dist[i][j] = Min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}//�÷��̵� �̿�

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (dist[i][j] != INF) {
				res[i] += dist[i][j];
			}
		}
		if (res[i] < res[ans]) {
			ans = i;
		}
	}//�ּڰ� ��ġ ã��

	printf("%d", ans);//��� ���
	return 0;
}