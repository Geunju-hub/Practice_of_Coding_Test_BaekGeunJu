#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int element;
	struct node *next;
}node;

typedef struct stack {
	node *top;
}stack;

stack *s;

node *getnode(int i) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = i;
	newnode->next = NULL;
	return newnode;
}

void Init_Stack() {
	s = (stack *)malloc(sizeof(stack));
	s->top = NULL;
	return;
}

void push(int i) {
	node *newnode = getnode(i);
	newnode->next = s->top;
	s->top = newnode;
	return;
}

int pop() {
	int res = s->top->element;
	node *F = s->top;
	s->top = s->top->next;
	free(F);
	return res;
}


int main(void) {
	Init_Stack();
	int N;
	int height[100000] = { 0, };
	long long res = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &height[i]);
	}
	for (int i = 0; i < N; i++) {
		while (s->top != NULL && height[s->top->element] > height[i]) {
			int tmp = pop();
			long long h = height[tmp];
			long long width = i;
			if (s->top != NULL) {
				width = i - s->top->element - 1;
			}
			if (width * h > res) {
				res = width * h;
			}
		}
		push(i);
	}
	while (s->top != NULL) {
		int top = pop();
		long long h = height[top];
		long long width = N;
		if (s->top != NULL) {
			width = N - s->top->element - 1;
		}
		if (width * h > res) {
			res = width * h;
		}
	}
	printf("%lld", res);
	return 0;
}