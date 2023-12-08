#include <stdio.h>
#include <stdlib.h>
int i;
int max(int m, int n)
 { 
 return (m > n) ? m : n; 
 }

int* add(int A[], int B[], int m, int n)
{
    int size = max(m, n);
    int* sum = (int*)malloc(size * sizeof(int));

     for ( i = 0; i < size; i++)
    {
        sum[i] = A[i];
        if (i>=m)
        sum[i]=0;
    }

  for ( i = 0; i < size; i++)
         if (i<n)
        sum[i] += B[i];


    return sum;
}

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
int main()
{
    int m, n;

    
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &m);
   
      int A[10];
      printf("\nEnter coefficients for the first polynomial:\n");
    for ( i = m - 1; i >= 0; i--) {
        printf("Coefficient for x^%d: ", i);
        scanf("%d", &A[i]);
    }

    printf("\nEnter the number of terms in the second polynomial: ");
    scanf("%d", &n);
 
    int B[10];
    printf("Enter coefficients for the second polynomial:\n");
    for ( i = n - 1; i >= 0; i--) {
        printf("Coefficient for x^%d: ", i);
        scanf("%d", &B[i]);
    }

    printf("\nFirst polynomial is \n");
    printPoly(A, m);
    printf("\nSecond polynomial is \n");
    printPoly(B, n);

    int* sum = add(A, B, m, n);
    int size = max(m, n);

    printf("\nSum polynomial is \n");
    printPoly(sum, size);
    
   
    return 0;
}


