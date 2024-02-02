#include<stdio.h>

struct Node
{
    int data;
    struct Node *left, *right, *parent;
};

struct Node* createNode(int data)
{
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));

    node -> data = data;
    node -> left = node -> right = node -> parent = NULL;
}
