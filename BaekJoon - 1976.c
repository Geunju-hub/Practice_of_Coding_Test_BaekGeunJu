#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int parent[200 + 1] = { 0, };
int arr[1000 + 1] = { 0, };
int graph[200 + 1][200 + 1] = { 0, };
int find(int a) {
	if (parent[a]==a) {
		return a;
	}
	else {
		return parent[a] = find(parent[a]);
	}
}

int main(void) {
	int N,M;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &graph[i][j]);
			if (graph[i][j] == 1) {
				int pi = find(i);
				int pj = find(j);
				if (pi < pj) {
					parent[pj] = pi;
				}
				else {
					parent[pi] = pj;
				}
			}
		}
	}
	for (int i = 0; i < M; i++) {
		scanf("%d", &arr[i]);
	}
	int flag = 0, comp = find(arr[0]);
	for (int i = 1; i < M; i++)
	{
		if (comp != find(arr[i])) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		printf("NO");
	}
	else {
		printf("YES");
	}

	return 0;
}