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
                if(iterator -> child != NULL) {
                    Node* childNode = iterator -> child;

                    iterator -> child = sib;
                    iterator -> right = sib -> right;

                    sib -> right = childNode;
                    sib -> left = NULL;

                    childNode -> left = sib;
                }
                else {
                    iterator -> child = sib;
                    iterator -> right = sib -> right;

                    sib -> left = NULL;
                    sib -> right = NULL;
                }

                sib -> parent = iterator;
            }
            // left tree goes down
            else {
                if(sib -> child != NULL) {
                    Node* childNode = sib -> child;

                    sib -> child = iterator;
                    sib -> left = iterator -> left;

                    iterator -> right = childNode;
                    iterator -> left = NULL;

                    childNode -> left = iterator;
                }
                else {
                    sib -> child = iterator;
                    sib -> left = iterator -> left;

                    iterator -> left = NULL;
                    iterator -> right = NULL;
                }

                iterator -> parent = sib;
                iterator = sib;
            }

            iterator -> order *= 2;
        }
        else {
            iterator = iterator -> right;
        }
    }

    while(iterator -> left != NULL) {
        iterator = iterator -> left;
    }

    head = iterator;
    return head;
}

void displayHeap(Node* head) {
    printf("\n");
    // while(head != NULL) {
    //     Node* iterator = head;
    //     int treeOrder = iterator -> order;
    //     for(int i = 0; i < treeOrder; i++)
    //         printf("\t");
    //     printf("%d", iterator -> key);
    //     iterator = iterator -> child;
    //     while(iterator != NULL) {
    //         Node* iterator2 = iterator;
    //         while(iterator2 != NULL) {

    //         }
    //     }
    // }
    while(head != NULL) {
        Node* iterator = head;
        int isRootDisplayed = 0;
        while(iterator != NULL) {
            Node* iterator2 = iterator;

            // displaying the root
            if(!isRootDisplayed) {
                printf("%d\t", iterator2 -> key);
                printf("\n");
                iterator = iterator -> child;
                isRootDisplayed = 1;
                continue;
            }

            // Then the children
            while(iterator2 != NULL) {
                printf("%d\t", iterator2 -> key);
                iterator2 = iterator2 -> right;
            }
            printf("\n");
            iterator = iterator -> child;
        }
        printf("---------------------\n");
        head = head -> right;
    }
}

int main() {
    int isInit = 0;
    Node* head;
    while(1) {
        printf("Enter element (Enter -1 to stop): ");
        int tmp;
        scanf("%d", &tmp);

        if(tmp == -1) {
            printf("STOPPING");
            break;
        }

        if(!isInit) {
            head = createNode(tmp);
            isInit = 1;
        }
        else {
            Node* tempNode = createNode(tmp);
            head = insert(head, tempNode);
            head = merge(head);
        }
        
        displayHeap(head);
    }

    return 0;
}