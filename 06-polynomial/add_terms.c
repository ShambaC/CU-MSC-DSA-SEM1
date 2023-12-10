#include<stdio.h>
#include<stdlib.h>

int getArraySize(int* arr)
{
    return sizeof(arr) / sizeof(int);
}

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

int* sum(int* A, int* B)
{
    int sizeA = getArraySize(A);
    int sizeB = getArraySize(B);

    int* res = (int*)malloc((sizeA + sizeB) * sizeof(int));
    for(int i = 0; i < (sizeA + sizeB); i++)
    {
        res[i] = -1;
    }

    for(int i = 0; i < (sizeA + sizeB); i+=2)
    {
        if(i < sizeA)
        {
            res[i] = A[i];
            res[i+1] = A[i+1];
            for(int j = 0; j < sizeB; j+=2)
            {
                if(B[j] == A[i])
                {
                    res[i+1] += B[j+1];
                }
            }
        }
        else
        {
            for(int j = 0; j < sizeA; j+=2)
            {
                if(B[i-sizeA] != A[j])
                {
                    res[i] = B[i-sizeA];
                    res[i+1] = B[i-sizeA + 1];
                }
            }
        }
    }

    return res;
}

void displayPoly(int* A)
{
    int size = getArraySize(A);

    for(int i = 0; i < size; i+=2)
    {
        if(A[i] == -1)
        {
            break;
        }
        printf("%dx^%d ", A[i+1], A[i]);
        if(i < size - 2)
        {
            printf("+ ");
        }
    }
    printf("\n");
}

int main()
{
    int n;

    printf("Enter the number of terms for the first expression: ");
    scanf("%d", &n);
    int* expA = create_exp(n);

    printf("\nEnter the number of terms for the second expression: ");
    scanf("%d", &n);
    int* expB = create_exp(n);

    int* res = sum(expA, expB);

    printf("\nPolynomial 1: ");
    displayPoly(expA);
    printf("\nPolynomial 2: ");
    displayPoly(expB);
    printf("\nSum: ");
    displayPoly(res);

    return 0;
}