#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char arr[102][102] = { 0, };//RGB문자로 입력받을 배열
int graph[102][102] = { 0, };//RGB문자를 숫자로 대체하는 배열
int N;//배열의 크기
int dx[4] = { -1,1,0,0 };//j방향 이동경우의 수
int dy[4] = { 0,0,-1,1 };//i방향 이동경우의 수
int visited[102][102] = { 0, };//방문여부체크배열

void DFS(int color, int i_idx, int j_idx) {
	visited[i_idx][j_idx] = 1;//방문표시
	for (int i = 0; i < 4; i++) {
		int newi = i_idx + dy[i];
		int newj = j_idx + dx[i];
		if (graph[newi][newj] == color && visited[newi][newj]==0) {
			DFS(color, newi, newj);
		}//같은 컬러면서 방문하지 않았을 경우 재귀적으로 실행
	}
}

void RGBcase() {
	int red = 0, green = 0, blue = 0;//구역의 수 정해줌
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j] == 0) {
				if (graph[i][j] == 1) {
					DFS(1, i, j);
					red++;
				}//방문하지 않았으면서 R인 경우 DFS실행 후 red증가
				else if (graph[i][j] == 2) {
					DFS(2, i, j);
					green++;
				}//방문하지 않았으면서 G인 경우 DFS실행후 green증가
				else if(graph[i][j]==3){
					DFS(3, i, j);
					blue++;
				}//방문하지 않았으면서 B인 경우 DFS 실행 후 blue증가
			}
		}
	}
	printf("%d ", red + green + blue);//세 구역의 합 출력
}

void RedGreen(int i_idx, int j_idx) {
	visited[i_idx][j_idx] = 1;
	for (int i = 0; i < 4; i++) {
		int newi = dy[i] + i_idx;
		int newj = dx[i] + j_idx;
		if ((graph[newi][newj] == 1 || graph[newi][newj] == 2) &&visited[newi][newj]==0) {
			RedGreen(newi, newj);
		}//R또는 G이면서 방문하지 않았을 경우 재귀적으로 함수 실행
	}
}

void RGcase() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			visited[i][j] = 0;
		}
	}//visited배열 다시 초기화 : 재사용 위함
	int redgreen=0, blue = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j] == 0) {
				if (graph[i][j] == 1||graph[i][j]==2) {
					RedGreen(i, j);
					redgreen++;
				}//방문하지 않았으면서 RG인 경우 RedGreen함수 실행 후 redgreen증가
				else {
					DFS(3, i, j);
					blue++;
				}//graph의 값이 3인 경우 DFS함수 실행 후 blue증가 
			}
		}
	}
	printf("%d", redgreen + blue);//적록색약인 사람이 본 구역 수 출력
}

int main(void) {
	scanf("%d", &N),getchar();//N입력 엔터 지우기
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%c", &arr[i][j]);
			switch (arr[i][j]) {
			case'R':
				graph[i][j] = 1;
				break;
			case'G':
				graph[i][j] = 2;
				break;
			case'B':
				graph[i][j] = 3;
				break;
			}
		}//arr배열의 인덱스가 R인경우 1 G인 경우 2 B인 경우 3으로 값 할당
		getchar();//엔터 지우기
	}
	RGBcase();//정상인 사람이 본 구역의 수
	RGcase();//적록색약인 사람이 본 구역의 수
	return 0;
}