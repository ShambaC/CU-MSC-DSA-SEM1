#include<stdio.h>
#include<stdlib.h>

void display(int array[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

void shellSort(int array[], int size) {
    // interval is 5,3,1
    for(int k = 5; k > 0; k -= 2) {
        printf("\nInterval %d\n", k);
        for(int i = 0; i < size; i++) {
            for(int j = i+k; j < size; j += k) {
                if(array[j-k] > array[k]) {
                    int temp = array[j-k];
                    array[j-k] = array[k];
                    array[k] = temp;
                }
                display(array, size);
                printf("\n");
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of elements in array: ");
    scanf("%d", &n);

    int array[n];
    printf("Enter the elements: \n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    shellSort(array, n);

    // display
    printf("Sorted array: \n");
    display(array, n);

    return 0;
}