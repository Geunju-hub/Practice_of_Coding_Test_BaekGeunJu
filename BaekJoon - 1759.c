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
}//�� ���Ŀ� ���Ǵ� compare�Լ�

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
}//���� ���� �ּҰ��� Ȯ�� �Լ�

void func(int cnt) {
	if (cnt == L) {
		if (accept()) {
			for (int i = 0; i < L; i++) {
				printf("%c", res[i]);
			}
			printf("\n");
		}//�����ּ�2��, ���� �ּ� 1�� ���� ���� + ���� ������ ���
	}
	else {
		//���� Ȯ��
		for (int i = 0; i < C; i++) {
			if (visited[str[i] - 'a'] == 0) {
				res[cnt] = str[i];
				visited[str[i] - 'a'] = 1;//�湮 ǥ��
				if (res[cnt] - 'a' > res[cnt - 1]-'a') {
					func(cnt + 1);
				}//���ĺ������ϴ¼����� ��� ����
				visited[str[i] - 'a'] = 0;//��Ʈ��ŷ
			}
		}
	}
}


int main(void) {
	char ch;
	scanf("%d %d", &L, &C);//L,C �Է�
	getchar();
	for (int i = 0; i < C; i++) {
		scanf("%c", &str[i]);
		getchar();
	}//�Է�
	qsort(str, C, sizeof(char), compare);//���ĺ� ����
	func(0);
	return 0;
}