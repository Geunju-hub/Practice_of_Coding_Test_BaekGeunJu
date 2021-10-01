#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N,Max=2000000000;
int arr[100000];
int R1, R2;

int abs(int a) {
	return a > 0 ? a : (-1) * a;
}//�������� �������ִ� �Լ�

int compare(const void *a, const void *b) {
	if (*(int *)a > *(int *)b) {
		return 1;
	}
	else {
		return -1;
	}
}//c��� ���� ����Ʈ�Լ� ���� ���Լ�

void binarysearch(int start, int end) {
	if (start < end) {
		int sum = arr[start] + arr[end];
		if (abs(sum) < Max) {
			Max = abs(sum);
			R1 = arr[start];
			R2 = arr[end];
		}
		if (sum <= 0) {
			binarysearch(start+1,end);
		}
		else {
			binarysearch(start, end - 1);
		}
	}
}//�̺�Ž�� ����

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	qsort(arr, N, sizeof(int), compare);//c��� �����Լ� qsort
	binarysearch(0, N - 1);
	printf("%d %d", R1, R2);
	return 0;
}