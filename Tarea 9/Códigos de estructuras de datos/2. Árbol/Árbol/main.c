#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* new_node(int x) {
    Node *n = malloc(sizeof(Node));
    n->data = x;
    n->left = n->right = NULL;
    return n;
}

Node* insert(Node* root, int x) {
    if (!root) return new_node(x);
    if (x < root->data) root->left = insert(root->left, x);
    else root->right = insert(root->right, x);
    return root;
}

void inorder(Node *r) {
    if (!r) return;
    inorder(r->left);
    printf("%d ", r->data);
    inorder(r->right);
}

void main(void) {
    Node *root = NULL;
    root = insert(root, 5);
    root = insert(root, 2);
    root = insert(root, 8);
    inorder(root);
    return 0;
}
