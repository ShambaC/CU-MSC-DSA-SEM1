#include<stdio.h>
#include<stdlib.h>

int main()
{
    int vertices, i, j;
    int graph[50][50];

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    // initialize
    int edges = vertices * (vertices - 1) / 2;
    for(i = 0; i < vertices; i++)
    {
        for(j = 0; j < edges; j++)
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
    edges = -1;
    int a, b, w;
    while (1)
    {
        printf("Enter -1, -1 to stop.\n");
        printf("Enter edge as vertex 1, vertex 2: ");
        scanf("%d%d", &a, &b);
        if(a == -1 || b == -1)
        {
            break;
        }

        if(choice == 2 || choice == 4) {
            printf("Enter the wright for the edge: ");
            scanf("%d", &w);
        }

        edges++;
        switch (choice)
        {
        case 1:
            graph[a][edges] = 1;
            graph[b][edges] = 1;
            break;
        case 2:
            graph[a][edges] = w;
            graph[b][edges] = w;
            break;
        case 3:
            graph[a][edges] = 1;
            graph[b][edges] = -1;
            break;
        case 4:
            graph[a][edges] = w;
            graph[b][edges] = -w;
            break;
        
        default:
            break;
        }
    }

    // display
    for(i = 0; i < vertices; i++)
    {
        for(j = 0; j <= edges; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    return 0;
}