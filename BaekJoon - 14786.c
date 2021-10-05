#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define LD 0.00000000000000000001

int A, B, C;

int main(void) {
	scanf("%d %d %d", &A, &B, &C);//A,B,C입력
	long double start = (C - B) / (double)A;
	long double end = (C + B) / (double)A;
	long double mid=0;
	int cycle = 50000;
	while (start < end && cycle--) {
		mid = (start + end) / 2;
		if (mid > (C - (B * (long double)sin(mid))) / A) {
			end=mid;
		}//x가 mid보다 작으면 end줄이기
		else if (mid < (C - (B * (long double)sin(mid))) / A) {
			start=mid+ LD;
		}//x가 mid보다 크면 start늘리기
	}
	printf("%.19Lf",mid+ 0.00000000000000000005);
	return 0;
}