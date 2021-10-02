#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char arr[102][102] = { 0, };//RGB���ڷ� �Է¹��� �迭
int graph[102][102] = { 0, };//RGB���ڸ� ���ڷ� ��ü�ϴ� �迭
int N;//�迭�� ũ��
int dx[4] = { -1,1,0,0 };//j���� �̵������ ��
int dy[4] = { 0,0,-1,1 };//i���� �̵������ ��
int visited[102][102] = { 0, };//�湮����üũ�迭

void DFS(int color, int i_idx, int j_idx) {
	visited[i_idx][j_idx] = 1;//�湮ǥ��
	for (int i = 0; i < 4; i++) {
		int newi = i_idx + dy[i];
		int newj = j_idx + dx[i];
		if (graph[newi][newj] == color && visited[newi][newj]==0) {
			DFS(color, newi, newj);
		}//���� �÷��鼭 �湮���� �ʾ��� ��� ��������� ����
	}
}

void RGBcase() {
	int red = 0, green = 0, blue = 0;//������ �� ������
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j] == 0) {
				if (graph[i][j] == 1) {
					DFS(1, i, j);
					red++;
				}//�湮���� �ʾ����鼭 R�� ��� DFS���� �� red����
				else if (graph[i][j] == 2) {
					DFS(2, i, j);
					green++;
				}//�湮���� �ʾ����鼭 G�� ��� DFS������ green����
				else if(graph[i][j]==3){
					DFS(3, i, j);
					blue++;
				}//�湮���� �ʾ����鼭 B�� ��� DFS ���� �� blue����
			}
		}
	}
	printf("%d ", red + green + blue);//�� ������ �� ���
}

void RedGreen(int i_idx, int j_idx) {
	visited[i_idx][j_idx] = 1;
	for (int i = 0; i < 4; i++) {
		int newi = dy[i] + i_idx;
		int newj = dx[i] + j_idx;
		if ((graph[newi][newj] == 1 || graph[newi][newj] == 2) &&visited[newi][newj]==0) {
			RedGreen(newi, newj);
		}//R�Ǵ� G�̸鼭 �湮���� �ʾ��� ��� ��������� �Լ� ����
	}
}

void RGcase() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			visited[i][j] = 0;
		}
	}//visited�迭 �ٽ� �ʱ�ȭ : ���� ����
	int redgreen=0, blue = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j] == 0) {
				if (graph[i][j] == 1||graph[i][j]==2) {
					RedGreen(i, j);
					redgreen++;
				}//�湮���� �ʾ����鼭 RG�� ��� RedGreen�Լ� ���� �� redgreen����
				else {
					DFS(3, i, j);
					blue++;
				}//graph�� ���� 3�� ��� DFS�Լ� ���� �� blue���� 
			}
		}
	}
	printf("%d", redgreen + blue);//���ϻ����� ����� �� ���� �� ���
}

int main(void) {
	scanf("%d", &N),getchar();//N�Է� ���� �����
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
		}//arr�迭�� �ε����� R�ΰ�� 1 G�� ��� 2 B�� ��� 3���� �� �Ҵ�
		getchar();//���� �����
	}
	RGBcase();//������ ����� �� ������ ��
	RGcase();//���ϻ����� ����� �� ������ ��
	return 0;
}