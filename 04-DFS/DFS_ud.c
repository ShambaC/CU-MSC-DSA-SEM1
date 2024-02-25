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

    tmp = adjList[dst] -> head;
    while(tmp -> next != NULL) {
        tmp = tmp -> next;
    }

    Node* srcNode = createNode(src);
    tmp -> next = srcNode;
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

void DFS(List* adjList[], int start, int visited[]) {
    Node* listHead = adjList[start] -> head;
    printf("%d", listHead -> vertex);
    visited[listHead -> vertex] = 1;

    while(listHead != NULL) {
        if(!visited[listHead -> vertex]) {
            printf("->");
            DFS(adjList, listHead -> vertex, visited);
        }
        listHead = listHead -> next;
    }
}

int main() {
    int size;
    printf("Enter the number of vertices: ");
    scanf("%d", &size);

    List* adjList[size];
    int visited[size];
    // init
    for(int i = 0; i < size; i++) {
        adjList[i] = (List*) malloc(sizeof(List));
        adjList[i] -> head = createNode(i);
        visited[i] = 0;
    }

    while(1) {
        int src, dst;
        printf("Enter edge as (source destination) (Enter -1 -1 to stop): ");
        scanf("%d%d", &src, &dst);

        if(src == -1 || dst == -1) {
            printf("Stopping\n");
            break;
        }

        addEdge(adjList, src, dst);
    }

    printf("Adjacency list: \n");
    DisplayAdjList(adjList, size);

    int start;
    printf("Enter the node to start traversal from: ");
    scanf("%d", &start);

    printf("DFS of the graph: \n");
    DFS(adjList, start, visited);

    return 0;
}