#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n, m,ans=0;
int arr[9] = { 0, };
int res[9] = { 0, };

int accept() {
	int visited[10] = { 0, };//0~9���� �湮���� �迭
	int cnt=0;//���� �����ִ� ����
	for (int i = 0; i < n; i++) {
		visited[res[i]] = 1;
	}//�湮���� üũ
	for (int i = 0; i < m; i++) {
		if (visited[arr[i]] == 1) {
			cnt++;
		}//�� �ʿ��� ��ȣ�� �湮�Ǿ��ٸ� cnt ����
	}
	return cnt ==m ? 1 : 0;//�� �ʿ��� ��ȣ���� �� ���ٸ� 1 �ƴϸ� 0 ��ȯ
}

void func(int cnt) {
	if (cnt == n) {
		if (accept()) {
			ans++;
		}
	}//���ǿ� ������ ��й�ȣ��� ans�� 1 ����
	else {
		for (int i = 0; i < 10; i++) {
			res[cnt] = i;
			func(cnt + 1);
		}//��� �迭�� �� �ְ� ��������� ����
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