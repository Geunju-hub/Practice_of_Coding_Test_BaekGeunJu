#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int Min(int a, int b) {
	return a > b ? b : a;
}

int dp[1001][3] = { 0, };
int arr[1001][3] = { 0, };

int main(void) {
	int N,res=1000000000;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
	}//ют╥б

	for (int c = 0; c < 3; c++) {
		for (int i = 0; i < 3; i++) {
			if (i == c) {
				dp[1][i] = arr[1][i];
			}
			else {
				dp[1][i] = 1000000000;
			}
		}
		for (int i = 2; i <= N; i++) {
			dp[i][0] = Min(dp[i - 1][1], dp[i - 1][2]) + arr[i][0];
			dp[i][1] = Min(dp[i - 1][0], dp[i - 1][2]) + arr[i][1];
			dp[i][2] = Min(dp[i - 1][0], dp[i - 1][1]) + arr[i][2];
		}
		for (int i = 0; i < 3; i++) {
			if (i != c) {
				res = Min(res, dp[N][i]);
			}
		}
	}
	printf("%d", res);
	return 0;
}