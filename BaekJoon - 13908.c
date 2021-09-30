#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n, m,ans=0;
int arr[9] = { 0, };
int res[9] = { 0, };

int accept() {
	int visited[10] = { 0, };//0~9까지 방문여부 배열
	int cnt=0;//개수 세어주는 변수
	for (int i = 0; i < n; i++) {
		visited[res[i]] = 1;
	}//방문여부 체크
	for (int i = 0; i < m; i++) {
		if (visited[arr[i]] == 1) {
			cnt++;
		}//꼭 필요한 번호가 방문되었다면 cnt 증가
	}
	return cnt ==m ? 1 : 0;//꼭 필요한 번호들이 다 들어갔다면 1 아니면 0 반환
}

void func(int cnt) {
	if (cnt == n) {
		if (accept()) {
			ans++;
		}
	}//조건에 만족한 비밀번호라면 ans값 1 증가
	else {
		for (int i = 0; i < 10; i++) {
			res[cnt] = i;
			func(cnt + 1);
		}//결과 배열에 값 넣고 재귀적으로 실행
	}
}

int main(void) {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &arr[i]);
	}
	func(0);
	printf("%d", ans);
	return 0;
}