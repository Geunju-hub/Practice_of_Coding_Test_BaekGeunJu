#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000//�ִ�ũ�� ����

int N;//�Է¹��� ũ��
int arr[MAX_SIZE + 1] = { 0, };//�Է¹��� �迭
int res[MAX_SIZE + 1] = { 0, };
//index = ���� �� �����ϴ� �κм����� ����
//�ش� �迭�� �� = �κм����� ��

int lower_bound(int start, int end,int k) {
	while (start < end) {
		int mid = (start + end) / 2;
		if (res[mid] < k) {
			start = mid + 1;
		}//������ �ø���
		else if (res[mid] > k) {
			end = mid;
		}//���� mid������ �״�� �α�
		else {
			return -1;
		}//���� ���� ���
	}
	return end;//while�� ���������� ������ ���� ��ȯ
}//���� ���ϱ�

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}//�迭 �Է�
	int cnt = 0;
	res[0] = arr[0];//�ӽ÷� ���� �� �־���
	for (int i = 1; i < N; i++) {
		if (res[cnt] < arr[i]) {
			res[++cnt] = arr[i];
		}//�ǳ������� arr[i]�� ���� �� ũ�ٸ� ����
		else {
			int index = lower_bound(0, cnt,arr[i]);
			if (index != -1) {
				res[index] = arr[i];
			}
		}//�װ� �ƴ϶�� res���� ���� x�� ����
	}
	printf("%d", cnt+1);//���� �� �����ϴ� �κм����� ���� ���
	return 0;
}