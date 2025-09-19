#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

// 스택 초기화
void initStack(Stack* s) {
    s->top = -1;
}

// 스택이 비었는지 체크
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택이 가득 찼는지 체크
int isFull(Stack* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

// push: 스택에 값 넣기
void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("스택이 가득 찼습니다! push 실패\n");
        return;
    }
    s->data[++(s->top)] = value;
    printf("push: %d\n", value);
}

// pop: 스택에서 값 꺼내기
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("스택이 비어 있습니다! pop 실패\n");
        return -1; // 에러 표시
    }
    int value = s->data[(s->top)--];
    printf("pop: %d\n", value);
    return value;
}

// 스택 상태 출력 (top -> bottom)
void printStack(Stack* s) {
    printf("스택 상태: ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

int main() {
    Stack s;
    initStack(&s);

    push(&s, 5);
    push(&s, 10);
    push(&s, 15);

    printStack(&s);

    pop(&s);
    pop(&s);

    printStack(&s);

    pop(&s);
    pop(&s); // 빈 스택에서 pop 시도

    return 0;
}
