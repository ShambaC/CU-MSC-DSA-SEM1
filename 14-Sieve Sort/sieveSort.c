#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct subList {
    int key;
    struct subList* prev;
    struct subList* next;
} SubArray;

typedef struct superList {
    SubArray* list;
    struct superList* next;
} SuperArray;

SubArray* createSubNode(int data) {
    SubArray* temp = (SubArray*) malloc(sizeof(SubArray));

    temp -> key = data;
    temp -> prev = NULL;
    temp -> next = NULL;

    return temp;
}

SubArray* appendSubNode(SubArray* head, SubArray* node, int dir) {
    if(head == NULL) {
        head = node;
        return head;
    }

    SubArray* tmp = head;
    if(dir == 0) {
        while(head -> next != NULL)
        {
            head = head -> next;
        }

        head -> next = node;
        node -> prev = head;
    }
    else if(dir == 1) {
        while(head -> prev != NULL)
        {
            head = head -> prev;
        }

        head -> prev = node;
        node -> next = head;

        tmp = node;
    }

    return tmp;
}

int lenSubNode(SubArray* head) {
    int size = 0;
    while(head != NULL) {
        head = head -> next;
        size++;
    }

    return size;
}

void displaySubList(SubArray* head) {
    while(true) {
        printf("%d", head -> key);

        if(head -> next == NULL) {
            break;
        }

        printf("->");
        head = head -> next;
    }
    printf("\n");
}

SuperArray* createSuperNode(SubArray* list) {
    SuperArray* temp = (SuperArray*) malloc(sizeof(SuperArray));

    temp -> list = list;
    temp -> next = NULL;

    return temp;
}

SuperArray* appendSuperNode(SuperArray* head, SuperArray* node) {
    if(head == NULL) {
        head = node;
        return head;
    }

    SuperArray* tmp = head;

    while(head -> next != NULL)
    {
        head = head -> next;
    }

    head -> next = node;

    return tmp;
}

int lenSuperNode(SuperArray* head) {
    int size = 0;
    while(head != NULL) {
        head = head -> next;
        size++;
    }

    return size;
}

void displaySuperList(SuperArray* head) {
    while(true) {
        displaySubList(head -> list);

        if(head -> next == NULL)
        {
            break;
        }

        head = head -> next;
    }
    printf("\n");
}

SuperArray* Sort(SuperArray* superlist, int size, int dir) {
    printf("SuperList now: \n");
    displaySuperList(superlist);

    if(lenSuperNode(superlist) == size) {
        return superlist;
    }

    SuperArray* newSuperList = NULL;

    while(superlist != NULL) {
        SubArray* sublistExtracted = superlist -> list;
        if(dir == 0) {
            SubArray* newTempSubNode = createSubNode(sublistExtracted -> key);
            newSuperList = appendSuperNode(newSuperList, createSuperNode(newTempSubNode));

            sublistExtracted = sublistExtracted -> next;
            while(sublistExtracted != NULL) {
                int ele = sublistExtracted -> key;
                bool isAssigned = false;

                SuperArray* tempNewSuperIterator = newSuperList;
                while (tempNewSuperIterator != NULL)
                {
                    if(ele < tempNewSuperIterator -> list -> key) {
                        tempNewSuperIterator -> list = appendSubNode(tempNewSuperIterator -> list, createSubNode(ele), dir);
                        isAssigned = true;
                        break;
                    }

                    tempNewSuperIterator = tempNewSuperIterator -> next;
                }

                if(!isAssigned) {
                    newSuperList = appendSuperNode(newSuperList, createSuperNode(createSubNode(ele)));
                }
                
                sublistExtracted = sublistExtracted -> next;
            }
        }
        else if(dir == 1) {
            while(sublistExtracted -> next != NULL) {
                sublistExtracted = sublistExtracted -> next;
            }

            SubArray* newTempSubNode = createSubNode(sublistExtracted -> key);
            newSuperList = appendSuperNode(newSuperList, createSuperNode(newTempSubNode));

            sublistExtracted = sublistExtracted -> prev;
            while(sublistExtracted != NULL) {
                int ele = sublistExtracted -> key;
                bool isAssigned = false;

                SuperArray* tempNewSuperIterator = newSuperList;
                while (tempNewSuperIterator != NULL)
                {
                    if(ele < tempNewSuperIterator -> list -> key) {
                        tempNewSuperIterator -> list = appendSubNode(tempNewSuperIterator -> list, createSubNode(ele), dir);
                        isAssigned = true;
                        break;
                    }

                    tempNewSuperIterator = tempNewSuperIterator -> next;
                }

                if(!isAssigned) {
                    newSuperList = appendSuperNode(newSuperList, createSuperNode(createSubNode(ele)));
                }
                
                sublistExtracted = sublistExtracted -> prev;
            }
        }

        superlist = superlist -> next;
    }

    return Sort(newSuperList, size, abs(dir - 1));
}

int main() {
    int size;
    printf("Enter the number of elements: ");
    scanf("%d", &size);

    SubArray* subArr = NULL;

    printf("Enter the elements: ");
    for(int i = 0; i < size; i++) {
        int temp;
        scanf("%d", &temp);

        subArr = appendSubNode(subArr, createSubNode(temp), 0);
    }

    SuperArray* supArr = NULL;
    supArr = appendSuperNode(supArr, createSuperNode(subArr));

    printf("Sieve Sort: \n");
    SuperArray* sortedArray = Sort(supArr, size, 0);

    printf("\nSorted Array: \n");
    displaySuperList(sortedArray);

    return 0;
}