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

int* mul(int* A, int* B, int sizeA, int sizeB)
{
    sizeA *= 2;
    sizeB *= 2;

    int* res = (int*)malloc((sizeA * sizeB) * sizeof(int));
    for(int i = 0; i < (sizeA * sizeB); i++)
    {
        res[i] = -1;
    }

    int k = 0;
    for(int i = 0; i < sizeA; i+=2)
    {
        for(int j = 0; j < sizeB; j+=2)
        {
            int t_pow = A[i] + B[j];
            int t_coeff = A[i+1] * B[j+1];
                
            int prevFound = 0;
            for(int p = 0; p < k; p+=2)
            {
                if(t_pow == res[p])
                {
                    prevFound = 1;
                    res[p+1] += t_coeff;
                    break;
                }
            }

            if(prevFound == 0)
            {
                res[k] = t_pow;
                res[k+1] = t_coeff;
                k += 2;
            }
        }
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
    int m, n;

    printf("Enter the number of terms for the first expression: ");
    scanf("%d", &m);
    int* expA = create_exp(m);

    printf("\nEnter the number of terms for the second expression: ");
    scanf("%d", &n);
    int* expB = create_exp(n);

    int* res = mul(expA, expB, m, n);

    printf("\nPolynomial 1: ");
    displayPoly(expA, m);
    printf("\nPolynomial 2: ");
    displayPoly(expB, n);
    printf("\nProduct: ");
    displayPoly(res, m*n);

    return 0;
}