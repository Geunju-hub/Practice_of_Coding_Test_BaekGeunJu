#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int M,N;
int res = 0;
int arr[500 + 2][500 + 2] = { 0, };
int dp[500 + 2][500 + 2] = { 0, };

int DFS(int row, int col) {
	if (dp[row][col] != -1) {
		return dp[row][col];
	}
	if (row < 0 || row >= M || col < 0 || col >= N) {
		return 0;
	}
	if (row == 0 && col == 0) {
		return 1;
	}
	dp[row][col] = 0;
	int dy[4] = { -1,1,0,0 };
	int dx[4] = { 0,0,-1,1 };
	for (int i = 0; i < 4; i++) {
		int newrow = row + dy[i];
		int newcol = col + dx[i];
		if (arr[newrow][newcol] > arr[row][col]) {
			dp[row][col] += DFS(newrow, newcol);
		}
	}
	return dp[row][col];
}

int main(void) {
	scanf("%d %d", &M, &N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
			dp[i][j] = -1;
		}
	}
	printf("%d",DFS(M - 1, N - 1));
	return 0;
}