#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	int x[3], y[3];
	for (int i = 0; i < 3; i++) {
		scanf("%d %d", &x[i], &y[i]);
	}
	int res = (x[0] * y[1] + x[1] * y[2] + x[2] * y[0]) - (x[1] * y[0] + x[2] * y[1] + x[0] * y[2]);
	if (res > 0) {
		printf("1");
	}
	else if (res == 0) {
		printf("0");
	}
	else {
		printf("-1");
	}
	return 0;
}