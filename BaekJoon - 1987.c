#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int R, C,res=0;
char arr[20 + 2][20 + 2] = { '\0', };
int visited[26] = { 0, };
void DFS(int i, int j,int cnt) {
	if (res < cnt) {
		res = cnt;
	}
	int dx[4] = { -1,1,0,0 };
	int dy[4] = { 0,0,-1,1 };
	for (int k = 0; k < 4; k++) {
		int newi = dy[k] + i;
		int newj = dx[k] + j;
		if (newi<1 || newi>R || newj<1 || newj>C) {
			continue;
		}
		if(visited[arr[newi][newj]-'A']==0) {
			visited[arr[newi][newj] - 'A'] = 1;
			DFS(newi, newj,cnt+1);
			visited[arr[newi][newj] - 'A'] = 0;
		}
	}
}

int main(void) {
	scanf("%d %d", &R, &C);
	getchar();
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			scanf("%c", &arr[i][j]);
		}
		getchar();
	}
	visited[arr[1][1] - 'A'] = 1;
	DFS(1, 1,1);
	printf("%d", res);
	return 0;
}