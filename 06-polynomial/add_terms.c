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

int* sum(int* A, int* B, int sizeA, int sizeB)
{
    sizeA *= 2;
    sizeB *= 2;

    int* res = (int*)malloc((sizeA + sizeB) * sizeof(int));
    for(int i = 0; i < (sizeA + sizeB); i++)
    {
        res[i] = -1;
    }

    int k = sizeA;
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
            int isFound = 0;
            for(int j = 0; j < sizeA; j+=2)
            {
                
                if(B[i-sizeA] == res[j])
                {
                    isFound = 1;
                    break;
                }
            }

            if(isFound == 0)
            {
                res[k] = B[i-sizeA];
                res[k+1] = B[i-sizeA + 1];
                k += 2;
            }
        }
    }

    return res;
}

void sortPoly(int* poly, int size) {
    size *= 2;
    for(int i = 1; i < size - 1; i+=2) {
        for(int j = 1; j < size - i - 1; j+=2) {
            if(poly[i] > poly[i+2]) {
                int tmpCoeff = poly[i-1];
                int tmpPow = poly[i];
                poly[i-1] = poly[i+1];
                poly[i] = poly[i+2];
                poly[i+1] = tmpCoeff;
                poly[i+2] = tmpPow;
            }
        }
    }
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
    int m, n;

    printf("Enter the number of terms for the first expression: ");
    scanf("%d", &m);
    int* expA = create_exp(m);

    printf("\nEnter the number of terms for the second expression: ");
    scanf("%d", &n);
    int* expB = create_exp(n);

    int* res = sum(expA, expB, m, n);

    printf("\nPolynomial 1: ");
    sortPoly(expA, m);
    displayPoly(expA, m);
    printf("\nPolynomial 2: ");
    sortPoly(expB, n);
    displayPoly(expB, n);
    printf("\nSum: ");
    sortPoly(res, m+n);
    displayPoly(res, m+n);

    return 0;
}