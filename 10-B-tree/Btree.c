#include<stdio.h>
#include<stdlib.h>

#include<stdbool.h>
#include<math.h>

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

void insertKey(Node* node, Key* keyToInsert, int pos) {
    if(pos == 0) {
        keyToInsert -> next = node -> keys;
        node -> keys = keyToInsert;
    }
    else {
        int keyCount = -1;
        Key* keyIterator = node -> keys;
        while(keyIterator != NULL) {
            keyCount++;
            if(pos == keyCount + 1) {
                keyToInsert -> next = keyIterator -> next;
                keyIterator -> next = keyToInsert;
            }
        }
    }
}

Key* popKey(Key* head, int index) {
    Key* iterator = head;
    bool isExist = false;
    int count = 0;

    while(iterator != NULL) {
        if(count == index) {
            isExist = true;
            break;
        }
        count++;
        iterator = iterator -> next;
    }

    if(!isExist) {
        return NULL;
    }
    else {

        for(int i = 0; i < count; i++) {
            head = head -> next;
        }
        head -> next = iterator -> next;
        iterator -> next = NULL;
        return iterator;
    }
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

Node** splitNode(Node* head, int pos) {
    Node* splitResult[2];

    Key* keyIter = head -> keys;
    Links* linkIter = head -> links;

    splitResult[0] = (Node*) malloc(sizeof(Node));
    splitResult[1] = (Node*) malloc(sizeof(Node));

    splitResult[0] -> keys = keyIter;
    splitResult[0] -> links = linkIter;
    splitResult[0] -> prev = head -> prev;

    for(int i = 0; i < pos; i++) {
        keyIter = keyIter -> next;
        linkIter = linkIter -> next;
    }

    linkIter = linkIter -> next;

    splitResult[1] -> keys = keyIter -> next;
    splitResult[1] -> links = linkIter -> next;
    splitResult[1] -> prev = head -> prev;

    keyIter -> next = NULL;
    linkIter -> next = NULL;

    return splitResult;
}

Node* insertNode(int key, Node* root) {
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
            insertKey(iterator, newKey, insertPos);

            isInserted = true;
            break;
        }
    }
    return root;    
}

Node* balanceTree(Node* root, int order) {
    Node* iterator = root;

    while(iterator != NULL) {
        if(lenKeys(iterator -> keys) == order) {
            if(iterator -> prev != NULL) {
                int median = floorf(order / 2.0f);
                Key* keyToMove = popKey(iterator -> keys, median);

                Node* prevNode = iterator -> prev;
                Key* prevKeyIterator = prevNode -> keys;
                Links* prevLinkIterator = prevNode -> links;
                int prevKeyCount = 0;
                while(prevKeyIterator != NULL) {
                    if(keyToMove -> key > prevKeyIterator -> key) {
                        prevKeyCount++;
                    }
                    else {
                        break;
                    }
                    prevKeyIterator = prevKeyIterator -> next;
                    prevLinkIterator = prevLinkIterator -> next;
                }

                insertKey(prevNode, keyToMove, prevKeyCount);
                Node* splitResult[] = splitNode(iterator, median);
                prevLinkIterator -> link = splitResult[0];
                Links* newLink = createLinks();
                newLink -> link = splitResult[1];
                newLink -> next = prevLinkIterator -> next;
                prevLinkIterator -> next = newLink;
            }
        }
    }
}