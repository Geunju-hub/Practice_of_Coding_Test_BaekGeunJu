#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>


typedef struct Stack {
	char str[10005];
	int top;
}stack;//���ڿ��� top��ġ ����ϴ� ���� ����

int addcarry = 0;
stack *A, *B,*C;

void Init_Stack() {
	A = (stack *)malloc(sizeof(stack));
	A->top = -1;
	B = (stack *)malloc(sizeof(stack));
	B->top = -1;
	C = (stack *)malloc(sizeof(stack));
	C->top = -1;
}//���� �ʱ�ȭ �Լ�

char pop(stack *s) {
	return s->str[s->top--];
}//�� ������ ������ ���Լ�

void push(stack *s, char num) {
	s->str[++s->top] = num;
}//Ǫ�� �Լ�

void Add(stack *a, stack *b) {
	while (a->top != -1 && b->top != -1) {
		int a_num = pop(a)-'0';
		int b_num = pop(b)-'0';
		int carry = (a_num + b_num+addcarry) / 10;
		int sum = (a_num + b_num+addcarry) % 10;
		push(C, sum + '0');
		addcarry = carry;
	}//������ ���� ����
	while (a->top != -1) {
		int a_num = pop(a) - '0';
		int carry = (a_num + addcarry) / 10;
		int sum = (a_num + addcarry) % 10;
		push(C, sum + '0');
		addcarry = carry;
	}//a�� �ڸ����� �� ū ���
	while(b->top != -1) {
		int b_num = pop(b) - '0';
		int carry = (b_num + addcarry) / 10;
		int sum = (b_num + addcarry) % 10;
		push(C, sum + '0');
		addcarry = carry;
	}//b�� �ڸ����� �� ū ���
	if (addcarry != 0) {
		push(C, addcarry + '0');
	}//������ ��� �����µ� carry�� ���� ��� �� ���� �־���.
}

void Print() {
	while (C->top != -1) {
		printf("%c", pop(C));
	}
}//���

int main(void) {
	Init_Stack();//���� �ʱ�ȭ
	scanf("%s %s", &A->str, &B->str);//���ڿ� A,B�Է�
	A->top = strlen(A->str)-1, B->top = strlen(B->str)-1;//������ top���� ������
	Add(A, B);//���� ����
	Print();//���� ����� ���
	return 0;
}