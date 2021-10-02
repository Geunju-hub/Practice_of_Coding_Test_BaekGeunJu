#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 200

int n;
int arr[MAX_SIZE + 1] = { 0, };
int res[MAX_SIZE + 1] = { 0, };

int binarysearch(int start, int end, int k) {
	while (start <= end) {
		int mid = (start + end) / 2;
		if (res[mid] > k) {
			end = mid - 1;
		}
		else if (res[mid] == k) {
			return mid;
		}
		else {
			start = mid + 1;
		}
	}
	return start;
}//�̺�Ž��

int main(void) {
	int cnt = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	res[cnt] = arr[0];
	for (int i = 1; i < n; i++) {
		if (res[cnt] < arr[i]) {
			res[++cnt] = arr[i];
		}//����
		else {
			int index = binarysearch(0, cnt, arr[i]);
			if (index != -1) {
				res[index] = arr[i];
			}//�̺�Ž���ؼ� ������ ��ġ�� �ֱ�
		}
	}
	printf("%d", n - (cnt + 1));//��ü ���� - ���� �� �����ϴ� �κм����� ����
	return 0;
}