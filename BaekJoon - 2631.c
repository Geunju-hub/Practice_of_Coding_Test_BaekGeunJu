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
}//이분탐색

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
		}//갱신
		else {
			int index = binarysearch(0, cnt, arr[i]);
			if (index != -1) {
				res[index] = arr[i];
			}//이분탐색해서 적절한 위치에 넣기
		}
	}
	printf("%d", n - (cnt + 1));//전체 길이 - 가장 긴 증가하는 부분수열의 길이
	return 0;
}