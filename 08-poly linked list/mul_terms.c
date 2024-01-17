#include<stdio.h>
#include<stdlib.h>

int i;

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

struct term* mul(struct term* expA, struct term* expB)
{
    struct term* headA = expA;
    struct term* headB = expB;

    struct term* res;
    struct term* resHead;

    int isResAssigned = 0;    

    while(1)
    {
        

        int isLooping = 1;
        expB = headB;
        while(isLooping)
        {
        	int coeff = expA -> coeff;
        	int pow = expA -> pow;
            coeff *= expB -> coeff;
            pow += expB -> pow;
            
            int prevFound = 0;
            if(isResAssigned)
            {
            	struct term* resTemp = resHead;
            	int loopBool = 1;
            	
            	while(loopBool)
            	{
            		if(pow == resTemp -> pow)
            		{
            			resTemp -> coeff += coeff;
            			prevFound = 1;
            		}
            		
            		if(resTemp -> next != NULL)
            		{
            			resTemp = resTemp -> next;
            			continue;
            		}
            		
            		loopBool = 0;
            	}
            }
            if(prevFound == 0)
            {
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
            }
            
	
	        if(expB -> next != NULL)
	        {
	            expB = expB -> next;
	        	continue;
	        }
	
	        isLooping = 0;
	    }

        if(expA -> next == NULL)
        {
            break;
        }

        expA = expA -> next;
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

    for(i = 0; i < n; i++)
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

    for(i = 0; i < n; i++)
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
    struct term* res = mul(ExpA, ExpB);
    printf("Result: \n");
    printExp(res);

    return 0;
}