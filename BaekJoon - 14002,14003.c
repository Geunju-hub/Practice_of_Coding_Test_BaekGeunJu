#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000

int compare(const void *a, const void *b) {
	return *(int *)a > *(int *)b ? 1 : -1;
}

int N;
int arr[MAX_SIZE + 1] = { 0, };//기본적으로 입력받는 수열
int lis[MAX_SIZE + 1] = { 0, };//가장 긴 증가하는 부분수열(임시)
int len[MAX_SIZE + 1] = { 0, };//수열의 길이 체크
int ans[MAX_SIZE + 1] = { 0, };//가장 긴 증가하는 부분수열(최종)

int binarysearch(int start, int end, int k) {
	while (start < end) {
		int mid = (start + end) / 2;
		if (lis[mid] < k) {
			start = mid + 1;
		}
		else {
			end=mid;
		}
	}
	return start;
}//lowerbound구하는 함수

int main(void) {
	int cnt0 = 0,cnt1=0;//lis에 쓰일 cnt수
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
	}//입력
	for (int i = 1; i <= N; i++) {
		if (cnt0==0|| lis[cnt0-1] < arr[i]) {
			lis[cnt0++] = arr[i];
			len[i] = cnt0-1;
		}
		else{
			int index = binarysearch(0, cnt0-1, arr[i]);
			lis[index] = arr[i];
			len[i] = index;
		}
	}//가장 긴 증가하는 부분수열 갱신
	int lis_size = cnt0-1;
	for (int i = N; i >= 1; i--) {
		if (len[i] == lis_size) {
			ans[cnt1++] = arr[i];
			lis_size--;
		}
	}//역추적해가면서 갱신
	printf("%d\n", cnt1);
	for (int i = cnt1-1; i >=0; i--) {
		printf("%d ", ans[i]);
	}//최종적인 가장 긴 증가하는 부분수열 출력
	return 0;
}