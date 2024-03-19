#include<stdio.h>
#include<stdlib.h>

int** createGraph(int *array, int size)
{
    int **graph = (int**) malloc(sizeof(int*) * size);
    for(int i = 0; i < size; i++)
    {
        graph[i] = (int*) malloc(sizeof(int) * size);
    }
    // init
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            graph[i][j] = 0;
        }
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(i == j)
                continue;
            if(((array[i] - array[j]) * (i - j)) >= 0 && j > i)
            {
                graph[i][j] = 1;
            }
        }
    }

    return graph;
}

void displayGraph(int **graph, int *array, int size)
{
    printf("X\t");
    for(int i = 0; i < size; i++)
    {
        printf("%d\t", array[i]);
    }
    printf("\n");

    for(int i = 0; i < size; i++)
    {
        for(int j = -1; j < size; j++)
        {
            if(j == -1)
            {
                printf("%d\t", array[i]);
                continue;
            }
            printf("%d\t", graph[i][j]);
        }

        printf("\n");
    }
}

void graphSort(int **graph, int* array, int size)
{
    int sortedArray[size];
    int sortArrCounter = 0;
    
    for(int k = 0; k < size; k++)
    {
        int sourceList[size];
        int sourceListCounter = 0;

        // Get a list of sources in the graph
        for(int i = 0; i < size; i++)
        {
            int isSource = 1;
            for(int j = 0; j < size; j++)
            {
                if(graph[j][i] == 1 || graph[j][i] == -1)
                {
                    isSource = 0;
                    break;
                }
            }

            if(isSource)
            {
                sourceList[sourceListCounter++] = i;
            }
        }

        sourceListCounter--;
        // Add highest positional source to the sorted array
        sortedArray[sortArrCounter++] = array[sourceList[sourceListCounter]];

        // Remove that source from the graph
        for(int i = 0; i < size; i++)
        {
            if(graph[sourceList[sourceListCounter]][i] != -1)
                graph[sourceList[sourceListCounter]][i] = 0;
            graph[i][sourceList[sourceListCounter]] = -1;
        }

        printf("The graph right now: \n");
        displayGraph(graph, array, size);
    }

    printf("\nThe sorted array: \n");
    for(int i = 0; i< size; i++)
    {
        printf("%d ", sortedArray[i]);
    }
}

int main()
{
    int size;
    printf("Enter the number of elements: ");
    scanf("%d", &size);

    int *array = (int*) malloc(sizeof(int) * size);

    printf("Enter the elements of the array: \n");
    for(int i = 0; i < size; i++)
    {
        scanf("%d", &array[i]);
    }

    int **graph = createGraph(array, size);

    printf("The graph: \n");
    displayGraph(graph, array, size);

    graphSort(graph, array, size);

    return 0;
}