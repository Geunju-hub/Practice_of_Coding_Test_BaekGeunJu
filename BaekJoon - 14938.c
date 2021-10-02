#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define INF 20000000

int Min(int a, int b) {
	return a > b ? b : a;
}//�ּڰ� ���ϴ� �Լ�

int n, m, r;
int dist[101][101] = { 0, };//�ִܰŸ� ���ϱ� ���� �������
int range[101] = { 0, };//�ش� ��ġ�� ������ ��

void func() {
	for (int k= 1; k<=n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dist[i][j] = Min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}//�÷��̵� �ͼ�
}

int main(void) {
	int ans = 0;
	scanf("%d %d %d", &n, &m, &r);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}//������� �ʱ�ȭ
	for (int i = 1; i <= n; i++) {
		scanf("%d", &range[i]);
	}//�ش� ��ġ�� ������ ��
	for (int i = 0; i < r; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		dist[u][v] = w;
		dist[v][u] = w;
	}//������̹Ƿ� ����
	func();
	for (int i = 1; i <= n; i++) {
		int Max = 0;
		for (int j = 1; j <= n; j++) {
			if (dist[i][j] != INF && dist[i][j]<=m) {
				Max += range[j];
			}
			if (Max > ans) {
				ans = Max;
			}
		}
	}//���� �ȿ� �� �������� �ִ� ���� ����
	printf("%d", ans);//���� ���
	return 0;
}