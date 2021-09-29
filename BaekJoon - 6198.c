#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int arr[80000 + 1] = { 0, };
int res[80000 + 1] = { 0, };
//전역변수로 입력받을 배열, 볼 수 있는 정원의 수 배열 선언
typedef struct Node {
	int element;
	struct Node *next;
}node;

typedef struct Stack {
	node *top;
}stack;

stack *s;
// 스택 구조체와 스택 안에 들어가는 노드 구조체 선언
node *getnode(int e) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = e;
	newnode->next = NULL;
	return newnode;
}//노드 생성 함수

void Init_Stack() {
	s = (stack *)malloc(sizeof(stack));
	s->top = NULL;
}//스택 초기화 함수

void push(int e) {
	node *newnode = getnode(e);
	newnode->next = s->top;
	s->top = newnode;
}//스택에 값 넣어주는 함수

int pop() {
	int res = s->top->element;
	node *F = s->top;
	s->top = s->top->next;
	free(F);
	return res;
}//스택의 맨 위의 값 반환받고 top위치 변경하는 함수

int main(void) {
	Init_Stack();//스택 초기화
	int N;
	long long ans=0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
	}//입력받음
	for (int i = N; i >= 1; i--) {
		while (s->top != NULL && arr[s->top->element] < arr[i]) {
			pop();
		}//top에 값이 있으면서 top의 원소의 높이가 현재 위치의 높이보다 크거나 같으면 pop
		if (s->top == NULL) {
			res[i] = N-i;
		}//top에 아무것도 없을 경우 N-i 결과값으로 넣어줌
		else {
			res[i] = s->top->element -i-1 ;
		}//그게 아니라면 top의 값에서 i+1 빼주기
		push(i);//i번째 인덱스 push
	}//이렇게 하게 되면 선형시간에 해결 가능
	for (int i = 1; i <= N; i++) {
		ans += res[i];
	}//결과값들 다 더한 값이 답이 됨.
	printf("%lld", ans);//답 출력
	return 0;
}