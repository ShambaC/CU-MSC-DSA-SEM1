#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct subArr {
    int key;

    struct subArr* prev;
    struct subArr* next;
};

struct subArrList {
    struct subArr* list;
    struct subArrList* next;
};

struct subArr* createNode(int key, struct subArr* prev) {
    struct subArr* term = (struct subArr*) malloc(sizeof(struct subArr));

    if(prev != NULL)    prev -> next = term;

    term -> key = key;
    term -> prev = prev;
    term -> next = NULL;

    return term;
}

struct subArrList* createNodeList(struct subArr* node) {
    struct subArrList* term = (struct subArrList*) malloc(sizeof(struct subArrList));

    term -> list = node;
    term -> next = NULL;

    return term;
}

void displayList(struct subArr* head) {
    while(1) {
        printf("%d", head -> key);

        if(head -> next == NULL)
            break;
        
        printf("->");
        head = head -> next;
    }
    printf("\n");
}

// dir = 0 => left to right, dir = 1 => right to left
void sort(struct subArrList* head, int dir) {
    struct subArrList* iterator = head;
    struct subArrList* newHead = NULL;
    struct subArrList* newIterator = NULL;

    while(1) {
        struct subArr* list = iterator -> list;
        struct subArr* newList = NULL;

        if(dir == 0) {
            int comp = list -> key;
            newList = createNode(comp, newList);

            if(newIterator == NULL) {
                newIterator = createNodeList(newList);
                newHead = newIterator;
            }
            else {
                newIterator = head;
                while(newIterator -> next != NULL) {
                    newIterator = newIterator -> next;
                }
                newIterator -> next = createNodeList(newList);
                newIterator = newIterator -> next;
            }

            list = list -> next;

            while(list != NULL) {
                if(list -> key <= comp) {
                    newList -> next = createNode(list -> key, newList);
                    newList = newList -> next;
                    list = list -> next;
                }
                else {
                    newIterator = newHead;
                    bool isAssigned = false;
                    while(1) {
                        if(list -> key < newIterator -> list -> key) {
                            struct subArr* tempA = newIterator -> list;
                            while(tempA -> next != NULL) {
                                tempA = tempA -> next;
                            }
                            tempA -> next = createNode(list -> key, tempA);
                            isAssigned = true;
                            break;
                        }
                        else if(newIterator -> next != NULL) {
                            newIterator = newIterator -> next;
                            continue;
                        }
                        break;
                    }

                    if(!isAssigned) {
                        newIterator -> next = createNodeList(createNode(list -> key, NULL));
                        newIterator = newIterator -> next;
                    }
                }
            }
        }
    }
}

int main() {
    int size;
    printf("Enter the number of elements: ");
    scanf("%d", &size);

    struct subArr* head;
    struct subArr* iterator = NULL;

    bool isHeadAssigned = false;
    printf("Enter the elements: \n");
    for(int i = 0; i < size; i++) {
        int key;
        scanf("%d", &key);

        struct subArr* term = createNode(key, iterator);

        if(!isHeadAssigned) {
            head = term;
            iterator = term;

            isHeadAssigned = true;
            continue;
        }

        iterator = term;
    }

    printf("The list: \n");
    displayList(head);

    return 0;
}