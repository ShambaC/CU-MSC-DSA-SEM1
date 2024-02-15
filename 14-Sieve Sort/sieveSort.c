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
    struct subArrList* newIterator;

    while(1) {
        struct subArr* list = iterator -> list;
        struct subArr* newList;

        if(dir == 0) {
            int comp = list -> key;
            list = list -> next;

            while(list != NULL) {
                if(list -> key < comp) {

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