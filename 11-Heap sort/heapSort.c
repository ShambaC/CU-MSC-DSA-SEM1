#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int* arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[left] > arr[largest])
        largest = left;
    if(right < n && arr[right] > arr[largest])
        largest = right;

    if(largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int* arr, int n)
{
    for(int i = n - 1; i >= 0; i--)
    {
        printf("%d, ", arr[0]);

        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void display(int *arr, int n, int start)
{
    printf("%d->", arr[start]);

    int left = 2 * start + 1;
    int right = 2 * start + 2;

    if(left < n)
        display(arr, n, left);
    if(right < n)
        display(arr, n, right);
    
}

int main()
{
    int size;
    printf("Enter the number of elements: ");
    scanf("%d", &size);

    int* arr = (int*) malloc(sizeof(int) * size);

    for(int i = 0; i < size; i++)
    {
        printf("\nEnter the element: ");
        scanf("%d", &arr[i]);

        for(int j = (i+1)/2 - 1; j >= 0; j--)
            heapify(arr, i+1, j);

        printf("Heap now: \n");
        display(arr, i+1, 0);
    }

    printf("\nThe sorted array is: \n");
    heapSort(arr, size);

    return 0;
}