#include <stdio.h>
#define MAX 5

typedef struct {
    int a[MAX];
    int top;
} Stack;

void init(Stack *s) { s->top = -1; }
void push(Stack *s, int x) { if (s->top < MAX-1) s->a[++s->top] = x; }
int pop(Stack *s) { return (s->top >= 0) ? s->a[s->top--] : -1; }

void main(void) {
    Stack s;
    init(&s);
    push(&s, 10);
    push(&s, 20);
    printf("%d ", pop(&s));
    printf("%d ", pop(&s));
    return 0;
}
