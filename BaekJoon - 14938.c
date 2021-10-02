#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define INF 20000000

int Min(int a, int b) {
	return a > b ? b : a;
}//최솟값 구하는 함수

int n, m, r;
int dist[101][101] = { 0, };//최단거리 구하기 위한 인접행렬
int range[101] = { 0, };//해당 위치의 아이템 수

void func() {
	for (int k= 1; k<=n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dist[i][j] = Min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}//플로이드 와샬
}

int main(void) {
	int ans = 0;
	scanf("%d %d %d", &n, &m, &r);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}//인접행렬 초기화
	for (int i = 1; i <= n; i++) {
		scanf("%d", &range[i]);
	}//해당 위치의 아이템 수
	for (int i = 0; i < r; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		dist[u][v] = w;
		dist[v][u] = w;
	}//양방향이므로 수정
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
	}//범위 안에 들어간 아이템의 최대 개수 갱신
	printf("%d", ans);//정답 출력
	return 0;
}