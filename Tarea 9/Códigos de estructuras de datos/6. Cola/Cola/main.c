#include <stdio.h>
#define MAX 5

typedef struct {
    int a[MAX];
    int front, rear, count;
} Queue;

void init(Queue *q) { q->front = 0; q->rear = 0; q->count = 0; }

void enqueue(Queue *q, int x) {
    if (q->count < MAX) {
        q->a[q->rear] = x;
        q->rear = (q->rear + 1) % MAX;
        q->count++;
    }
}

int dequeue(Queue *q) {
    if (q->count == 0) return -1;
    int v = q->a[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return v;
}

void main(void) {
    Queue q;
    init(&q);
    enqueue(&q, 5);
    enqueue(&q, 10);
    printf("%d ", dequeue(&q));
    printf("%d ", dequeue(&q));
    return 0;
}
