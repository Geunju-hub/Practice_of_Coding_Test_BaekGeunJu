#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int L, C;
char str[16] = { 0, };
char res[16] = { 0, };
int visited[27] = { 0, };

int compare(const void *a, const void *b) {
	char A = *(char *)a;
	char B = *(char *)b;
	if (A - 'a' > B - 'a') {
		return 1;
	}
	else {
		return -1;
	}
}//퀵 정렬에 사용되는 compare함수

int accept() {
	int cnta = 0, cntb = 0;
	for (int i = 0; i < L; i++) {
		if (res[i] == 'a' || res[i] == 'e' || res[i] == 'i' || res[i] == 'o' || res[i] == 'u') {
			cnta++;
		}
		else {
			cntb++;
		}
	}
	if (cnta >= 1 && cntb >= 2) {
		return 1;
	}
	else {
		return 0;
	}
}//자음 모음 최소개수 확인 함수

void func(int cnt) {
	if (cnt == L) {
		if (accept()) {
			for (int i = 0; i < L; i++) {
				printf("%c", res[i]);
			}
			printf("\n");
		}//자음최소2개, 모음 최소 1개 조건 만족 + 개수 맞으면 출력
	}
	else {
		//조건 확인
		for (int i = 0; i < C; i++) {
			if (visited[str[i] - 'a'] == 0) {
				res[cnt] = str[i];
				visited[str[i] - 'a'] = 1;//방문 표시
				if (res[cnt] - 'a' > res[cnt - 1]-'a') {
					func(cnt + 1);
				}//알파벳증가하는순서일 경우 진행
				visited[str[i] - 'a'] = 0;//백트래킹
			}
		}
	}
}


int main(void) {
	char ch;
	scanf("%d %d", &L, &C);//L,C 입력
	getchar();
	for (int i = 0; i < C; i++) {
		scanf("%c", &str[i]);
		getchar();
	}//입력
	qsort(str, C, sizeof(char), compare);//알파벳 정렬
	func(0);
	return 0;
}