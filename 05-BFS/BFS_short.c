#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

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

    // Uncomment for undirected graph
    /*
    tmp = adjList[dst] -> head;
    while(tmp -> next != NULL) {
        tmp = tmp -> next;
    }

    Node* srcNode = createNode(src);
    tmp -> next = srcNode;
    */
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

int BFS(List* adjList[], int size, int src, int dest, int pred[], int dist[]) {
    
    int visited[size];
    for(int i = 0; i < size; i++) {
        visited[i] = 0;
        dist[i] = 999;
        pred[i] = -1;
    }

    int queue[size];
    queue[++rear] = adjList[src] -> head -> vertex;
    dist[src] = 0;

    while(front <= rear) {
        Node* listHead = adjList[queue[front]] -> head;
        visited[listHead -> vertex] = 1;

        while(listHead != NULL) {
            if(!visited[listHead -> vertex]) {
                queue[++rear] = listHead -> vertex;
                visited[listHead -> vertex] = 1;
                dist[listHead -> vertex] = dist[queue[front]]  + 1;
                pred[listHead -> vertex] = queue[front];
            }
            if(listHead -> vertex == dest) {
                return 1;
            }

            listHead = listHead -> next;
        }
        front++;
    }

    return 0;
}

void findShortestPath(List* adjList[], int src, int dst, int size) {
    
    int pred[size];
    int dist[size];

    if(BFS(adjList, size, src, dst, pred, dist) == 0) {
        printf("\nNo path from source to destination!");
        return;
    }

    // Backtracking
    int path[size];
    int crawl = dst;
    int pathCounter = -1;
    path[++pathCounter] = crawl;
    while(pred[crawl] != -1) {
        path[++pathCounter] = pred[crawl];
        crawl = pred[crawl];
    }

    printf("\nShortest path length is: %d", dist[dst]);
    printf("\nPath: ");
    for(int i = pathCounter; i >= 0; i--) {
        printf("%d", path[i]);
        if(i != 0) {
            printf("->");
        }
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
            printf("Stopping\n");
            break;
        }

        addEdge(adjList, src, dst);
    }

    printf("Adjacency list: \n");
    DisplayAdjList(adjList, size);

    int src, dst;
    printf("Enter the nodes to find path between: ");
    scanf("%d%d", &src, &dst);

    findShortestPath(adjList, src, dst, size);

    return 0;
}