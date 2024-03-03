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

void addEdge(List* adjList[], int src, int dst, int isDir) {
    Node* tmp = adjList[src] -> head;
    while(tmp -> next != NULL) {
        tmp = tmp -> next;
    }

    Node* dstNode = createNode(dst);
    tmp -> next = dstNode;

    if(!isDir) {
        tmp = adjList[dst] -> head;
        while(tmp -> next != NULL) {
            tmp = tmp -> next;
        }

        Node* srcNode = createNode(src);
        tmp -> next = srcNode;
    }
}

int lenNodeList(Node* listHead) {
    int size = 0;
    while(listHead != NULL) {
        size++;
        listHead = listHead -> next;
    }
    return size;
}

void SortAdjList(List* adjList[], int size) {
    for(int a = 0; a < size; a++) {
        Node* listHead = adjList[a] -> head -> next;
        Node* iterator = listHead;
        int len = lenNodeList(listHead);
        
        for(int i = 0; i < len - 1; i++) {
            iterator = listHead;
            for(int j = 0; j < len - i - 1; j++) {
                if(iterator -> vertex > iterator -> next -> vertex) {
                    int temp = iterator -> vertex;
                    iterator -> vertex = iterator -> next -> vertex;
                    iterator -> next -> vertex = temp;
                }
                iterator = iterator -> next;
            }
        }
    }
}

int isEdge(int a, int b, List* adjList[]) {
    Node* listHead = adjList[a] -> head -> next;
    while(listHead != NULL) {
        if(listHead -> vertex == b) {
            return 1;
        }
        listHead = listHead -> next;
    }
    return 0;
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

int DFSnumCount = 0;
int DFScompCount = 0;

void DFS(List* adjList[], int start, int visited[], int DFSnum[], int DFScompNum[], int DFSPred[], int parent) {
    Node* listHead = adjList[start] -> head;
    printf("%d", listHead -> vertex);
    DFSPred[listHead -> vertex] = parent;
    parent = listHead -> vertex;
    visited[listHead -> vertex] = 1;
    DFSnum[listHead -> vertex] = ++DFSnumCount;

    while(listHead != NULL) {
        if(!visited[listHead -> vertex]) {
            printf("->");
            DFS(adjList, listHead -> vertex, visited, DFSnum, DFScompNum, DFSPred, parent);
            DFScompNum[listHead -> vertex] = ++DFScompCount;
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
    int DFSnum[size];
    int DFScompNum[size];
    int DFSPred[size];
    // init
    for(int i = 0; i < size; i++) {
        adjList[i] = (List*) malloc(sizeof(List));
        adjList[i] -> head = createNode(i);
        visited[i] = 0;
        DFSnum[i] = 0;
        DFScompNum[i] = 0;
        DFSPred[i] = -1;
    }

    int dir = 0;
    printf("Choose the type of graph:\n1. Undirected graph\n2. Directed Graph\nEnter choice: ");
    scanf("%d", &dir);

    while(1) {
        int src, dst;
        printf("Enter edge as (source destination) (Enter -1 -1 to stop): ");
        scanf("%d%d", &src, &dst);

        if(src == -1 || dst == -1) {
            printf("Stopping\n");
            break;
        }

        addEdge(adjList, src, dst, dir-1);
    }

    SortAdjList(adjList, size);

    printf("Adjacency list: \n");
    DisplayAdjList(adjList, size);

    int start;
    printf("Enter the node to start traversal from: ");
    scanf("%d", &start);

    printf("DFS of the graph: \n");
    DFS(adjList, start, visited, DFSnum, DFScompNum, DFSPred, -1);
    printf("\n");
    DFScompNum[start] = ++DFScompCount;

    // DFS for the remaining vertices
    for(int i = 0; i < size; i++) {
        if(visited[i])
            continue;
        
        DFS(adjList, i, visited, DFSnum, DFScompNum, DFSPred, -1);
        printf("\n");
        DFScompNum[i] = ++DFScompCount;
    }

    printf("\n(DFS number / completion number) for elements: \n");
    for(int i = 0; i < size; i++) {
        printf("%d - (%d, %d)\n", i, DFSnum[i], DFScompNum[i]);
    }

    printf("Tree Edges: ");
    for(int i = 1; i < size; i++) {
        int a = -1;
        int b = -1;
        for(int j = 0; j < size; j++) {
            if(DFSnum[j] == i + 1) {
                a = j;
                b = DFSPred[j];
                break;
            }
        }
        if(a != -1 && b != -1 && isEdge(b, a, adjList)) {
            printf("{%d, %d} ", b, a);
        }
    }

    printf("\nForward edges: ");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(i == j)
                continue;
            if(DFSnum[j] > DFSnum[i] && DFScompNum[j] < DFScompNum[i] && isEdge(i, j, adjList) && i != DFSPred[j] && j != DFSPred[i]) {
                printf("{%d, %d} ", i, j);
            }
        }
    }

    printf("\nBack edges: ");
    if(dir == 1) {
        for(int i = 1; i < size; i++) {
            int a = -1;
            int b = -1;
            for(int j = 0; j < size; j++) {
                if(DFSnum[j] == i + 1) {
                    a = j;
                    b = DFSPred[j];
                }
            }
            if(a != -1 && b != -1 && isEdge(a, b, adjList)) {
                printf("{%d, %d} ", a, b);
            }
        }
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(i == j)
                    continue;
                if(DFSnum[j] > DFSnum[i] && DFScompNum[j] < DFScompNum[i] && isEdge(j, i, adjList) && i != DFSPred[j] && j != DFSPred[i]) {
                    printf("{%d, %d} ", j, i);
                }
            }
        }
    }
    else {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(i == j)
                    continue;
                if(DFSnum[j] < DFSnum[i] && DFScompNum[j] > DFScompNum[i] && isEdge(i, j, adjList) && i != DFSPred[j] && j != DFSPred[i]) {
                    printf("{%d, %d} ", i, j);
                }
            }
        }
    }

    if(dir == 2) {
        printf("\nCross edges: ");
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(i == j)
                    continue;
                if(DFSnum[j] < DFSnum[i] && DFScompNum[j] < DFScompNum[i] && isEdge(i, j, adjList) && i != DFSPred[j] && j != DFSPred[i]) {
                    printf("{%d, %d} ", i, j);
                }
            }
        }
    }

    return 0;
}