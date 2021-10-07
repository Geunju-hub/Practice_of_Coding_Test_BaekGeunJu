#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>


typedef struct Stack {
	char str[10005];
	int top;
}stack;//문자열과 top위치 기억하는 변수 설정

int addcarry = 0;
stack *A, *B,*C;

void Init_Stack() {
	A = (stack *)malloc(sizeof(stack));
	A->top = -1;
	B = (stack *)malloc(sizeof(stack));
	B->top = -1;
	C = (stack *)malloc(sizeof(stack));
	C->top = -1;
}//스택 초기화 함수

char pop(stack *s) {
	return s->str[s->top--];
}//맨 위에꺼 꺼내는 팝함수

void push(stack *s, char num) {
	s->str[++s->top] = num;
}//푸시 함수

void Add(stack *a, stack *b) {
	while (a->top != -1 && b->top != -1) {
		int a_num = pop(a)-'0';
		int b_num = pop(b)-'0';
		int carry = (a_num + b_num+addcarry) / 10;
		int sum = (a_num + b_num+addcarry) % 10;
		push(C, sum + '0');
		addcarry = carry;
	}//꺼내서 덧셈 연산
	while (a->top != -1) {
		int a_num = pop(a) - '0';
		int carry = (a_num + addcarry) / 10;
		int sum = (a_num + addcarry) % 10;
		push(C, sum + '0');
		addcarry = carry;
	}//a의 자릿수가 더 큰 경우
	while(b->top != -1) {
		int b_num = pop(b) - '0';
		int carry = (b_num + addcarry) / 10;
		int sum = (b_num + addcarry) % 10;
		push(C, sum + '0');
		addcarry = carry;
	}//b의 자릿수가 더 큰 경우
	if (addcarry != 0) {
		push(C, addcarry + '0');
	}//연산이 모두 끝났는데 carry가 남은 경우 맨 위로 넣어줌.
}

void Print() {
	while (C->top != -1) {
		printf("%c", pop(C));
	}
}//출력

int main(void) {
	Init_Stack();//스택 초기화
	scanf("%s %s", &A->str, &B->str);//문자열 A,B입력
	A->top = strlen(A->str)-1, B->top = strlen(B->str)-1;//끝점을 top으로 정해줌
	Add(A, B);//덧셈 연산
	Print();//더한 결과값 출력
	return 0;
}