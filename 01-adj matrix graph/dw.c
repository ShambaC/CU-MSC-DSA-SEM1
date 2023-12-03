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

    // calculate incidence matrix
    int edges = 0;
    int a, b, w;
    while (1)
    {
        printf("Enter -1, -1 to stop.\n");
        printf("Enter edge as vertex 1 vertex 2: ");
        scanf("%d%d", &a, &b);
        printf("Enter the weight of the edge: ");
        scanf("%d", &w);

        if(a == -1 || b == -1)
        {
            break;
        }

        edges++;
        if(edges > (vertices * (vertices - 1) / 2))
        {
            printf("\nMax number of edges added !!");
            break;
        }

        graph[a][b] = 1;
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