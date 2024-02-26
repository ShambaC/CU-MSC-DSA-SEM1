#include<stdio.h>
#include<stdlib.h>

int main()
{
    int vertices, i, j;
    int graph[50][50];

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    // initialize
    for(i = 0; i < vertices; i++)
    {
        for(j = 0; j < vertices; j++)
        {
            graph[i][j] = 0;
        }
    }

    int choice;
    printf("Types of graph:\n1. Undirected unweighted\n2. Undirected weighted\n3. Directed unweighted\n4. Directed weighted\nEnter your choice: ");
    scanf("%d", &choice);
    if(choice < 1 || choice > 4) {
        printf("Wrong input!!");
        return 1;
    }

    // calculate incidence matrix
    int edges = 0;
    int a, b, w;
    while (1)
    {
        printf("Enter edge as vertex 1 vertex 2 (Enter -1, -1 to stop): ");
        scanf("%d%d", &a, &b);
        if(a == -1 || b == -1)
        {
            break;
        }
        if(choice == 2 || choice == 4) {
            printf("Enter the weight of the edge: ");
            scanf("%d", &w);
        }        

        edges++;
        if(edges > (vertices * (vertices - 1) / 2))
        {
            printf("\nMax number of edges added !!");
            break;
        }

        switch (choice)
        {
        case 1:
            graph[a][b] = 1;
            graph[b][a] = 1;
            break;
        case 2:
            graph[a][b] = w;
            graph[b][a] = w;
            break;
        case 3:
            graph[a][b] = 1;
            break;
        case 4:
            graph[a][b] = w;
            break;
        
        default:
            break;
        }
    }

    // display
    for(i = 0; i < vertices; i++)
    {
        for(j = 0; j < vertices; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    return 0;
}