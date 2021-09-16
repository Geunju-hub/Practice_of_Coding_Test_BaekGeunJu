#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 10000001

int n, m;
int dist[100 + 1][100 + 1] = { 0, };


int Min(int a, int b) {
	return a > b ? b : a;
}

void floydwarshall() {
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dist[i][j] = Min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

int main(void) {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		if (dist[u][v] > w) {
			dist[u][v] = w;
		}
	}
	floydwarshall();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (dist[i][j] == INF) {
				printf("0 ");
			}
			else {
				printf("%d ",dist[i][j]);
			}
		}
		printf("\n");
	}
	return 0;
}