#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int k;
int arr[13] = { 0, };
int res[6] = { 0, };
int visited[49] = { 0, };

void func(int cnt) {
	if (cnt == 6) {
		for (int i = 0; i < 6; i++) {
			printf("%d ", res[i]);
		}
		printf("\n");
	}
	else {
		for (int i = 0; i < k; i++) {
			if (visited[arr[i]]==0) {
				visited[arr[i]] = 1;
				res[cnt] = arr[i];
				if (res[cnt] > res[cnt - 1]) {
					func(cnt + 1);
				}
				visited[arr[i]] = 0;
			}
		}
	}
}

int main(void) {
	while (1) {
		scanf("%d", &k);
		if (k == 0) {
			break;
		}
		else {
			for (int i = 0; i < k; i++) {
				scanf("%d", &arr[i]);
			}
			func(0);
			for (int i = 0; i < k; i++) {
				arr[i] = 0;
			}
			printf("\n");
		}
	}
	return 0;
}