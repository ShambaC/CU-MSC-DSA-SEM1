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

    // calculate incidence matrix
    edges = -1;
    int a, b, w;
    while (1)
    {
        printf("Enter -1, -1 to stop.\n");
        printf("Enter edge as vertex 1, vertex 2: ");
        scanf("%d%d", &a, &b);
        printf("Enter the wright for the edge: ");
        scanf("%d", &w);

        if(a == -1 || b == -1)
        {
            break;
        }

        edges++;
        graph[a][edges] = w;
        graph[b][edges] = w;
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