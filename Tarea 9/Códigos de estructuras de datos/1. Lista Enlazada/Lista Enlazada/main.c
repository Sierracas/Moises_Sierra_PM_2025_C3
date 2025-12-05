#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* push_front(Node *head, int x) {
    Node *n = malloc(sizeof(Node));
    n->data = x;
    n->next = head;
    return n;
}

void print_list(Node *head) {
    Node *p = head;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
}

void main(void) {
    Node *head = NULL;
    head = push_front(head, 30);
    head = push_front(head, 20);
    head = push_front(head, 10);
    print_list(head);
    return 0;
}
