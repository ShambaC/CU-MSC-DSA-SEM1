#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Key {
    int key;
    struct key* next;
} Key;

typedef struct Links {
    Node* link;
    struct Links* next;
} Links;

typedef struct Node {
    Key* keys;
    Links* links;
    struct Node* prev;
} Node;

int lenKeys(Key* head) {
    int count = 0;
    while(head != NULL) {
        count++;
        head = head -> next;
    }
    return count;
}

int lenLinks(Links* head) {
    int count = 0;
    while(head != NULL) {
        count++;
        head = head -> next;
    }
    return count;
}

Key* createKeys(int key) {
    Key* keys = (Key*) malloc(sizeof(Key));

    keys -> key = key;
    keys -> next = NULL;

    return keys;
}

Links* createLinks() {
    Links* links = (Links*) malloc(sizeof(Links));

    links -> link = NULL;

    return links;
}

Node* createNode(int key) {
    Node* node = (Node*) malloc(sizeof(Node));

    node -> keys = createKeys(key);
    node -> links = createLinks();
    node -> prev = NULL;

    return node;
}

Node* insertNode(int key, Node* root, int order) {
    Node* iterator = root;

    if(root == NULL) {
        root = createNode(key);
        return root;
    }

    bool isInserted = false;
    while (!isInserted) {
        int keyCount = -1;
        int insertPos = 0;
        Key* keyIterator = iterator -> keys;
        while(keyIterator != NULL) {
            keyCount++;
            if(key < keyIterator -> key)
                break;
            if(key > keyIterator -> key) {
                insertPos = keyCount + 1;
            }

            keyIterator = keyIterator -> next;
        }

        if(iterator -> links != NULL) {
            int linkCount = -1;
            Links* links = iterator -> links;
            while(links != NULL) {
                linkCount++;
                if(insertPos == linkCount) {
                    iterator = links -> link;
                    break;
                }
                links = links -> next;
            }
        }
        else {
            Key* newKey = createKeys(key);
            if(insertPos == 0) {
                newKey -> next = iterator -> keys;
                iterator -> keys = newKey;
            }
            else {
                keyCount = -1;
                keyIterator = iterator -> keys;
                while(keyIterator != NULL) {
                    keyCount++;
                    if(insertPos == keyCount + 1) {
                        newKey -> next = keyIterator -> next;
                        keyIterator -> next = newKey;
                    }
                }
            }

            isInserted = true;
            break;
        }
    }
    
}