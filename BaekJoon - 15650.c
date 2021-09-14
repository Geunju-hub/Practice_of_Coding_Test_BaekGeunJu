#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N, M;
int arr[8] = { 0, };
int used[8 + 1] = { 0, };

void func(int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		return;
	}
	else {
		for (int i = 1; i <= N; i++) {
			if (used[i] == 0) {
				arr[cnt] = i;
				used[i] = 1;
				if (arr[cnt] > arr[cnt - 1]) {
					func(cnt + 1);
				}
				used[i] = 0;
			}
		}
	}
}

int main(void) {
	scanf("%d %d", &N, &M);
	func(0);
	return 0;
}