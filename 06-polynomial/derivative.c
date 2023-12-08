#include <stdio.h>
#include <stdlib.h>
int i;
 
void printPoly(int poly[], int n)
{
    for (i = n-1; i >= 0; i--) {
        printf("%d", poly[i]);
        if (i >= 0)
            printf("x^%d", i);
        if (i != 0)
            printf(" + ");
    }
    printf("\n");
}
 
int main() {
    int m;
 
 
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &m);
 
    int* A = (int*)malloc(m * sizeof(int));
    int* res = (int*)malloc(m * sizeof(int));
    printf("\nEnter coefficients for the first polynomial:\n");
    for ( i = m - 1; i >= 0; i--) {
        printf("Coefficient for x^%d: ", i);
        scanf("%d", &A[i]);
    }
 
    for(i = 0; i < m-1; i++) {
        res[i] = A[i+1]*(i+1);
    }
 
    printf("Derivative polynomial: ");
    printPoly(res, m-1);
}
 
