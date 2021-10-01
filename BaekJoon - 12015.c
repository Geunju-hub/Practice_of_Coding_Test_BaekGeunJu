#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000//최대크기 정의

int N;//입력받을 크기
int arr[MAX_SIZE + 1] = { 0, };//입력받을 배열
int res[MAX_SIZE + 1] = { 0, };
//index = 가장 긴 증가하는 부분수열의 길이
//해당 배열의 값 = 부분수열의 값

int lower_bound(int start, int end,int k) {
	while (start < end) {
		int mid = (start + end) / 2;
		if (res[mid] < k) {
			start = mid + 1;
		}//시작점 올리기
		else if (res[mid] > k) {
			end = mid;
		}//끝점 mid값으로 그대로 두기
		else {
			return -1;
		}//값이 같은 경우
	}
	return end;//while문 성공적으로 나오면 끝점 반환
}//하한 정하기

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}//배열 입력
	int cnt = 0;
	res[0] = arr[0];//임시로 시작 값 넣어줌
	for (int i = 1; i < N; i++) {
		if (res[cnt] < arr[i]) {
			res[++cnt] = arr[i];
		}//맨끝값보다 arr[i]의 값이 더 크다면 갱신
		else {
			int index = lower_bound(0, cnt,arr[i]);
			if (index != -1) {
				res[index] = arr[i];
			}
		}//그게 아니라면 res범위 내의 x값 갱신
	}
	printf("%d", cnt+1);//가장 긴 증가하는 부분수열의 길이 출력
	return 0;
}