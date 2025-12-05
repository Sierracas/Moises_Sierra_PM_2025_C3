#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int v;
    struct Node *next;
} Node;

Node* add(Node *head, int v) {
    Node *n = malloc(sizeof(Node));
    n->v = v;
    n->next = head;
    return n;
}

void main(void) {
    int N = 3;
    Node *graph[3] = {NULL};

    graph[0] = add(graph[0], 1);
    graph[1] = add(graph[1], 2);
    graph[2] = add(graph[2], 0);

    for (int i = 0; i < N; i++) {
        printf("N%d: ", i);
        Node *p = graph[i];
        while (p) {
            printf("%d ", p->v);
            p = p->next;
        }
        printf("\n");
    }
    return 0;
}
