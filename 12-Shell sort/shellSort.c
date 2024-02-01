#include<stdio.h>
#include<stdlib.h>

void shellSort(int* array, int n)
{
    for(int interval = 5; interval > 0; interval -= 2)
    {
        for(int i = interval; i < n; i++)
        {
            int temp = array[i];
            int j;
            for(j = i; j >= interval && array[j - interval] > temp; j -= interval)
            {
                array[j] = array[j - interval];
                displayArray(array, n);
            }
            array[j] = temp;
            displayArray(array, n);
        }
    }
}

void displayArray(int* array, int size)
{
    printf("\n");
    for(int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}

int main()
{
    int size;
    printf("Enter the number of elements to sort: ");
    scanf("%d", &size);

    int* array = (int*) malloc(sizeof(int) * size);

    printf("Enter the elements: \n");
    for(int i = 0; i < size; i++)
    {
        scanf("%d", &array[i]);
    }

    shellSort(array, size);
    printf("The sorted array: ");
    displayArray(array, size);
}