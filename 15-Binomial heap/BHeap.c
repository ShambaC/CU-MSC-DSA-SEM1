#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int key;
    int order;
    struct Node* child;
    struct Node* parent;
    struct Node* right;
    struct Node* left;
} Node;

Node* createNode(int key) {
    Node* node = (Node*) malloc(sizeof(Node));
    node -> key = key;
    node -> order = 1;
    node -> child = NULL;
    node -> parent = NULL;
    node -> right = NULL;
    node -> left = NULL;

    return node;
}

Node* insert(Node* head, Node* node) {
    node -> right = head;
    head -> left = node;
    head = node;
    return head;
}

Node* merge(Node* head) {
    Node* iterator = head;

    while(iterator -> right != NULL) {
        Node* sib = iterator -> right;
        if(iterator -> order == sib -> order) {
            // right tree goes down
            if(iterator -> key < sib -> key) {

            }
            // left tree goes down
            else {
                if(sib -> child != NULL) {
                    Node* childNode = sib -> child;
                    sib -> child = iterator;
                    sib -> left = iterator -> left;
                    iterator -> right = childNode;
                    childNode -> left = iterator;
                }
                else {
                    sib -> child = iterator;
                    iterator -> right = NULL;
                }

                iterator -> parent = sib;
                iterator = sib;
            }
        }
        else {
            iterator = iterator -> right;
        }
    }
}

int main() {

}