#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

Node* createNode(int vertex) {
    Node* node = (Node*) malloc(sizeof(Node));

    node -> vertex = vertex;
    node -> next = NULL;

    return node;
}

void addEdge(List* adjList[], int src, int dst) {
    Node* tmp = adjList[src] -> head;
    while(tmp -> next != NULL) {
        tmp = tmp -> next;
    }

    Node* dstNode = createNode(dst);
    tmp -> next = dstNode;
}

void DisplayAdjList(List* adjList[], int size) {
    for(int i = 0; i < size; i++) {
        Node* iterator = adjList[i] -> head;
        while(iterator != NULL) {
            printf("%d", iterator -> vertex);
            if(iterator -> next != NULL) {
                printf("->");
            }
            iterator = iterator -> next;
        }
        printf("\n");
    }
}

int main() {
    int size;
    printf("Enter the number of vertices: ");
    scanf("%d", &size);

    List* adjList[size];
    // init
    for(int i = 0; i < size; i++) {
        adjList[i] = (List*) malloc(sizeof(List));
        adjList[i] -> head = createNode(i);
    }

    while(1) {
        int src, dst;
        printf("Enter edge as (source destination) (Enter -1 -1 to stop): ");
        scanf("%d%d", &src, &dst);

        if(src == -1 || dst == -1) {
            printf("Stopping");
            break;
        }

        addEdge(adjList, src, dst);
    }

    printf("Adjacency list: \n");
    DisplayAdjList(adjList, size);

    return 0;
}