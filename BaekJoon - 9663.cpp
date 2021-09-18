#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 300000000

int N, E;
int dist[800+1][800+1] = { 0, };

void func() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
}

int main(void) {
	int s, e;
	scanf("%d %d", &N, &E);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}
	for (int i = 0; i < E; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		if (dist[u][v] > w) {
			dist[u][v] = w;
		}
		if (dist[v][u] > w) {
			dist[v][u] = w;
		}
	}
	scanf("%d %d", &s, &e);
	func();
	if (dist[1][e] == 0) {
		printf("-1");
	}
	else {
		printf("%d", dist[1][e]);
	}
	return 0;
}