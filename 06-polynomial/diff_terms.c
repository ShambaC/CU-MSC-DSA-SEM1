#include<stdio.h>
#include<stdlib.h>

int* create_exp(int n)
{
    int* exp = (int*)malloc(n*2*sizeof(int));

    for(int i = 0; i < n*2; i+=2)
    {
        int power, coeff;

        printf("Enter the power of the term and its coefficient: ");
        scanf("%d%d", &power, &coeff);

        exp[i] = power;
        exp[i+1] = coeff;
    }

    return exp;
}

int* diff(int* A, int sizeA)
{
    sizeA *= 2;

    int* res = (int*)malloc((sizeA) * sizeof(int));
    for(int i = 0; i < (sizeA); i++)
    {
        res[i] = -1;
    }

    for(int i = 0; i < sizeA; i+=2)
    {
        res[i] = A[i] - 1;
        res[i+1] = A[i+1] * A[i];
    }

    return res;
}

void displayPoly(int* A, int size)
{
    size *= 2;
    for(int i = 0; i < size; i+=2)
    {
        if(A[i] == -1)
        {
            break;
        }
        printf("%dx^%d ", A[i+1], A[i]);
        if(i < size - 2 && A[i+2] != -1)
        {
            printf("+ ");
        }
    }
    printf("\n");
}

int main()
{
    int m;

    printf("Enter the number of terms for the first expression: ");
    scanf("%d", &m);
    int* expA = create_exp(m);

    int* res = diff(expA, m);

    printf("\nPolynomial: ");
    displayPoly(expA, m);
    printf("\nDerivative: ");
    displayPoly(res, m);

    return 0;
}