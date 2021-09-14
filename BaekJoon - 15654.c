#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int N, M;
int arr[8] = { 0, };
int res[8] = { 0, };
int used[10000 + 1] = { 0, };

int compare(const void *a, const void *b) {
	if (*(int *)a > *(int *)b) {
		return 1;
	}
	else if (*(int *)a == *(int *)b) {
		return 0;
	}
	else {
		return -1;
	}
}

void func(int cnt) {
	if (cnt == M) {
		for (int i = 0; i < M; i++) {
			printf("%d ", res[i]);
		}
		printf("\n");
		return;
	}
	else {
		for (int i = 0; i < N; i++) {
			if (used[arr[i]] == 0) {
				res[cnt] = arr[i];
				used[arr[i]] = 1;
				func(cnt + 1);
				used[arr[i]] = 0;
			}
		}
	}
}

int main(void) {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	qsort(arr, N, sizeof(int), compare);
	func(0);
	return 0;
}