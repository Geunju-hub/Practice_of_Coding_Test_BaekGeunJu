#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct Point {
	long long x, y;
}point;

int ccw(point a, point b, point c) {
	long long tmp = a.x * b.y + b.x * c.y + c.x * a.y - (a.y * b.x + b.y * c.x + c.y * a.x);
	if (tmp > 0) {
		return 1;
	}
	else if (tmp == 0) {
		return 0;
	}
	else {
		return -1;
	}
}

int main(void) {
	point arr[4];
	scanf("%lld %lld %lld %lld", &arr[0].x, &arr[0].y, &arr[1].x, &arr[1].y);
	scanf("%lld %lld %lld %lld", &arr[2].x, &arr[2].y, &arr[3].x, &arr[3].y);
	if (ccw(arr[0], arr[1], arr[2]) * ccw(arr[0], arr[1], arr[3]) <= 0 && ccw(arr[2], arr[3], arr[0]) * ccw(arr[2], arr[3], arr[1]) <= 0) {
		printf("1");
	}
	else {
		printf("0");
	}
	return 0;
}