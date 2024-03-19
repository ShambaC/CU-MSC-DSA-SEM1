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

int lenExp(struct term* Term) {
    int size = 0;
    while (Term != NULL)
    {
        size++;
        Term = Term -> next;
    }
    return size;
}

void sortExp(struct term* Exp) {
    struct term* Term = Exp;
    int size = lenExp(Term);

    for(int i = 0; i < size - 1; i++) {
            for(int j = 0; j < size - i - 1; j++) {
                if(Term -> pow < Term -> next -> pow) {
                    int temp = Term -> pow;
                    Term -> pow = Term -> next -> pow;
                    Term -> next -> pow = temp;

                    temp = Term -> coeff;
                    Term -> coeff = Term -> next -> coeff;
                    Term -> next -> coeff = temp;
                }
                Term = Term -> next;
            }
        }
}

void printExp(struct term* Term)
{
    sortExp(Term);

    while(1)
    {
        if(Term -> coeff != 0) {
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

struct term* add(struct term* expA, struct term* expB)
{
    struct term* headA = expA;
    struct term* headB = expB;

    struct term* res;
    struct term* resHead;

    int isResAssigned = 0;    

    while(1)
    {
        int coeff = expA -> coeff;
        int pow = expA -> pow;

        int isLooping = 1;
        expB = headB;
        while(isLooping)
        {
            if(pow == expB -> pow)
            {
                coeff += expB -> coeff;
            }

            if(expB -> next != NULL)
            {
                expB = expB -> next;
                continue;
            }

            isLooping = 0;
        }

        struct term* tempterm = createTerm(pow, coeff);

        if(isResAssigned == 0)
        {
            resHead = tempterm;
            res = tempterm;
            isResAssigned = 1;
        }
        else
        {
            res -> next = tempterm;
            res = tempterm;
        }

        if(expA -> next == NULL)
        {
            break;
        }

        expA = expA -> next;
    }

    // Iterating second expression for strays
    expB = headB;
    while (1)
    {
        int coeff = expB -> coeff;
        int pow = expB -> pow;

        int isLooping = 1;
        int isFound = 0;
        struct term* resIterator = resHead;

        while(isLooping)
        {
            if(pow == resIterator -> pow)
            {
                isFound = 1;
                isLooping = 0;
            }

            if(resIterator -> next == NULL)
            {
                isLooping = 0;
            }

            resIterator = resIterator -> next;
        }   
        
        if(isFound == 0)
        {
            struct term* tempTerm = createTerm(pow, coeff);
            res -> next = tempTerm;
            res = tempTerm;
        }

        if(expB -> next == NULL)
        {
            break;
        }

        expB = expB -> next;
    }

    return resHead;
}

int main()
{
    int n;
    int pow, coeff;

    printf("Enter the number of terms for the first expression: ");
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

    // for second expression
    printf("Enter the number of terms for the second expression: ");
    scanf("%d", &n);

    if(n < 1)
    {
        printf("Illegal input !!!!");
        return 1;
    }

    struct term* ExpB;
    struct term* iteratorB;
    
    isHeadAssigned = 0;

    for(int i = 0; i < n; i++)
    {
        printf("Enter power and coefficient: ");
        scanf("%d%d", &pow, &coeff);
        struct term* tempTerm = createTerm(pow, coeff);
        
        if(isHeadAssigned == 0)
        {
            iteratorB = tempTerm;
            ExpB = tempTerm;
            isHeadAssigned = 1;
            continue;
        }

        iteratorB -> next = tempTerm;
        iteratorB = tempTerm;
    }

    printf("Expressions: \n");
    printExp(ExpA);
    printf("\n");
    printExp(ExpB);
    printf("\n");
    struct term* res = add(ExpA, ExpB);
    printf("Result: \n");
    printExp(res);

    return 0;
}