#include<stdio.h>
#include<stdlib.h>

struct node {
    int vertex;
    int weight;
    struct node* next;
};
struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));

    newNode -> vertex = v;
    newNode -> next = NULL;

    return newNode;
}

struct Graph {
    int numVertices;
    struct node** adjLists;
};
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));

    graph -> numVertices = vertices;
    graph -> adjLists = malloc(vertices * sizeof(struct node*));

    for(int i = 0; i < vertices; i++) {
        graph -> adjLists[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int a, int b, int w) {
    // edge from a to b
    struct node* newNode = createNode(b);
    newNode -> next = graph -> adjLists[a];
    newNode -> weight = w;
    graph -> adjLists[a] = newNode;

    // edge from b to a
    newNode = createNode(a);
    newNode -> next  = graph -> adjLists[b];
    newNode -> weight = w;
    graph -> adjLists[b] = newNode;
}

void displayGraph(struct Graph* graph) {
    for(int v = 0; v < graph -> numVertices; v++) {
        struct node* temp = graph -> adjLists[v];
        printf("\nVertex %d\n", v);
        while (temp) {
            printf("%d/%d", temp -> vertex, temp -> weight);
            if(temp -> next) {
                printf("-> ");
            }
            temp = temp -> next;
        }
        printf("\n"); 
    }
}

int main() {
    int n, a, b;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    struct Graph* graph = createGraph(n);

    int numEdges = 0;
    printf("Enter the edges:\n");
    while(1) {
        printf("Enter the edge as vertex1 vertex2 and -1 -1 to stop: ");
        scanf("%d%d", &a, &b);

        if(a == -1 || b == -1) {
            break;
        }

        numEdges++;
        if(numEdges > n*(n-1)/2) {
            printf("\nMax number of edges added!!!");
            break;
        }

        int w;
        printf("Enter the weight of the edge: ");
        scanf("%d", &w);

        addEdge(graph, a, b, w);
    }

    displayGraph(graph);

    return 0;
}