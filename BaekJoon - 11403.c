#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 100000
int N;
int dist[101][101] = { 0, };

int Min(int a, int b) {
	return a > b ? b : a;
}//최솟값 찾는 함수

void func() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				dist[i][j] = Min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}//최솟값 넣기
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (dist[i][j] != INF) {
				printf("1 ");
			}
			else {
				printf("0 ");
			}
		}
		printf("\n");
	}//출력
}//플로이드 와샬 함수

int main(void) {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &dist[i][j]);
			if (dist[i][j] == 0) {
				dist[i][j] = INF;
			}
		}
	}//초기화 및 입력
	func();//플로이드 와샬 함수
	return 0;
}