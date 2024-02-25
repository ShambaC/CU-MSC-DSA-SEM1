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

int front = 0;
int rear = -1;

void BFS(List* adjList[], int start, int visited[], int queue[]) {
    
    queue[++rear] = adjList[start] -> head -> vertex;

    while(front <= rear) {
        Node* listHead = adjList[queue[front]] -> head;
        printf("%d->", listHead -> vertex);
        visited[listHead -> vertex] = 1;

        while(listHead != NULL) {
            if(!visited[listHead -> vertex]) {
                queue[++rear] = listHead -> vertex;
                visited[listHead -> vertex] = 1;
            }

            listHead = listHead -> next;
        }
        front++;
    }
}

int main() {
    int size;
    printf("Enter the number of vertices: ");
    scanf("%d", &size);

    List* adjList[size];
    int visited[size];
    int queue[size];
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

    printf("BFS of the graph: \n");
    BFS(adjList, start, visited, queue);

    return 0;
}