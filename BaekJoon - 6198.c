#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int arr[80000 + 1] = { 0, };
int res[80000 + 1] = { 0, };
//���������� �Է¹��� �迭, �� �� �ִ� ������ �� �迭 ����
typedef struct Node {
	int element;
	struct Node *next;
}node;

typedef struct Stack {
	node *top;
}stack;

stack *s;
// ���� ����ü�� ���� �ȿ� ���� ��� ����ü ����
node *getnode(int e) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = e;
	newnode->next = NULL;
	return newnode;
}//��� ���� �Լ�

void Init_Stack() {
	s = (stack *)malloc(sizeof(stack));
	s->top = NULL;
}//���� �ʱ�ȭ �Լ�

void push(int e) {
	node *newnode = getnode(e);
	newnode->next = s->top;
	s->top = newnode;
}//���ÿ� �� �־��ִ� �Լ�

int pop() {
	int res = s->top->element;
	node *F = s->top;
	s->top = s->top->next;
	free(F);
	return res;
}//������ �� ���� �� ��ȯ�ް� top��ġ �����ϴ� �Լ�

int main(void) {
	Init_Stack();//���� �ʱ�ȭ
	int N;
	long long ans=0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
	}//�Է¹���
	for (int i = N; i >= 1; i--) {
		while (s->top != NULL && arr[s->top->element] < arr[i]) {
			pop();
		}//top�� ���� �����鼭 top�� ������ ���̰� ���� ��ġ�� ���̺��� ũ�ų� ������ pop
		if (s->top == NULL) {
			res[i] = N-i;
		}//top�� �ƹ��͵� ���� ��� N-i ��������� �־���
		else {
			res[i] = s->top->element -i-1 ;
		}//�װ� �ƴ϶�� top�� ������ i+1 ���ֱ�
		push(i);//i��° �ε��� push
	}//�̷��� �ϰ� �Ǹ� �����ð��� �ذ� ����
	for (int i = 1; i <= N; i++) {
		ans += res[i];
	}//������� �� ���� ���� ���� ��.
	printf("%lld", ans);//�� ���
	return 0;
}