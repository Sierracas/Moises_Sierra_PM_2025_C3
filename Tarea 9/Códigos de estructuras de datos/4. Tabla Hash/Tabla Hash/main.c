#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

typedef struct Node {
    int key;
    struct Node *next;
} Node;

int hash(int k) { return k % SIZE; }

void insert(Node* table[], int k) {
    int h = hash(k);
    Node *n = malloc(sizeof(Node));
    n->key = k;
    n->next = table[h];
    table[h] = n;
}

void print_table(Node* table[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d: ", i);
        Node *p = table[i];
        while (p) {
            printf("%d ", p->key);
            p = p->next;
        }
        printf("\n");
    }
}

void main(void) {
    Node* table[SIZE] = {0};
    insert(table, 1);
    insert(table, 6);
    insert(table, 12);
    print_table(table);
    return 0;
}
