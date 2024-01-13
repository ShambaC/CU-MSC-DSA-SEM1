#include<stdio.h>
#include<stdlib.h>

struct term
{
    int pow, coeff;
    struct term* next;
};

struct term* createTerm(int pow, int coeff)
{
    struct term* Term = (struct term*)malloc(sizeof(struct term));

    Term -> pow = pow;
    Term -> coeff = coeff;
    Term -> next = NULL;

    return Term;
}

void printExp(struct term* Term)
{
    while(1)
    {
        if(Term -> coeff != 1 && Term -> coeff != 0) {
            if(Term -> coeff > 0)
                printf("%d", Term -> coeff);
            else
                printf("(%d)", Term -> coeff);
        }

        if(Term -> pow != 0)
            printf("x^%d", Term -> pow);
        
        if(Term -> next != NULL)
        {
            printf(" + ");
            Term = Term -> next;
            continue;
        }

        break;
    }
}

void diff(struct term* Term)
{
    while(1)
    {
        Term -> coeff *= Term -> pow;
        Term -> pow -= 1;

        if(Term -> next == NULL)
        {
            break;
        }

        Term = Term -> next;
    }
}

int main()
{
    int n;
    int pow, coeff;

    printf("Enter the number of terms in the expression: ");
    scanf("%d", &n);

    if(n < 1)
    {
        printf("Illegal input !!!!");
        return 1;
    }

    struct term* ExpA;
    struct term* iteratorA;
    
    int isHeadAssigned = 0;

    for(int i = 0; i < n; i++)
    {
        printf("Enter power and coefficient: ");
        scanf("%d%d", &pow, &coeff);
        struct term* tempTerm = createTerm(pow, coeff);
        
        if(isHeadAssigned == 0)
        {
            iteratorA = tempTerm;
            ExpA = tempTerm;
            isHeadAssigned = 1;
            continue;
        }

        iteratorA -> next = tempTerm;
        iteratorA = tempTerm;
    }

    printf("Expression: \n");
    printExp(ExpA);
    printf("\nDerivative: \n");
    diff(ExpA);
    printExp(ExpA);

    return 0;
}