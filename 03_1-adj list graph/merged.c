#include<stdio.h>
#include<stdlib.h>

// Graph vertex
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// The adjacency list
typedef struct List {
    Node* head;
} List;

/**
 * Method to create a node for the adjacency list
 * @param vertex value of the node in the graph
 * @param weight weight of the edge this node is a part of
*/
Node* createNode(int vertex, int weight) {
    Node* node = (Node*) malloc(sizeof(Node));

    node -> vertex = vertex;
    node -> weight = weight;
    node -> next = NULL;

    return node;
}

/**
 * Method to add edge to the adjacency list
 * @param adjList adjacency list array that stores the head to each of the lists
 * @param src source vertex of the edge
 * @param dst destination vertex of the edge
 * @param weight weight of the edge
 * @param isDir if the graph is a directed graph
*/
void addEdge(List* adjList[], int src, int dst, int weight, int isDir) {
    // src to dst
    Node* tmp = adjList[src] -> head;
    while(tmp -> next != NULL) {
        tmp = tmp -> next;
    }

    Node* dstNode = createNode(dst, weight);
    tmp -> next = dstNode;

    // dst to src
    if(!isDir) {
        tmp = adjList[dst] -> head;
        while(tmp -> next != NULL) {
            tmp = tmp -> next;
        }

        Node* srcNode = createNode(src, weight);
        tmp -> next = srcNode;
    }
}

// method to display the adjacency list
void DisplayAdjList(List* adjList[], int size) {
    for(int i = 0; i < size; i++) {
        Node* iterator = adjList[i] -> head;
        while(iterator != NULL) {
            printf("%d", iterator -> vertex);
            if(iterator -> weight != -1) {
                printf("(%d)", iterator -> weight);
            }
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
        adjList[i] -> head = createNode(i, -1);
    }

    int choice;
    printf("Types of graph:\n1. Undirected unweighted\n2. Undirected weighted\n3. Directed unweighted\n4. Directed weighted\nEnter your choice: ");
    scanf("%d", &choice);
    if(choice < 1 || choice > 4) {
        printf("Wrong input!!");
        return 1;
    }

    while(1) {
        int src, dst;
        printf("Enter edge as (source destination) (Enter -1 -1 to stop): ");
        scanf("%d%d", &src, &dst);

        if(src == -1 || dst == -1) {
            printf("Stopping\n");
            break;
        }

        int w = -1;
        if(choice == 2 || choice == 4) {
            printf("Enter the wright for the edge: ");
            scanf("%d", &w);
        }

        addEdge(adjList, src, dst, w, (choice == 3 || choice == 4));
    }

    printf("Adjacency list: \n");
    DisplayAdjList(adjList, size);

    return 0;
}