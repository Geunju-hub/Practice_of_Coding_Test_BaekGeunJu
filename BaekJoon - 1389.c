#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 200000000//INF최대치 설정

int dist[101][101] = { 0, };//인접행렬
int res[101] = { 0, };//결과 담아둘 배열

int Min(int a, int b) {
	return a > b ? b : a;
}//최솟값 찾는 함수

int main(void) {
	int N, M, ans = 1;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			dist[i][j] = INF;
		}
		dist[i][i] = 0;
	}//인접행렬 초기화
	for (int i = 0; i < M; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		dist[u][v] = 1;
		dist[v][u] = 1;
	}//입력받고 친구끼리 간선 연결
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				dist[i][j] = Min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}//플로이드 이용

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (dist[i][j] != INF) {
				res[i] += dist[i][j];
			}
		}
		if (res[i] < res[ans]) {
			ans = i;
		}
	}//최솟값 위치 찾기

	printf("%d", ans);//결과 출력
	return 0;
}