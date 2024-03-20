#include<stdio.h>
#include<stdlib.h>

// UTILITY
// method for factorial
int fact(int z)
{
    int f = 1, i;
    if (z == 0) {
        return(f);
    }
    else {
        for (i = 1; i <= z; i++) {
            f = f * i;
	    }
    }
    return f;
}
// method to find nCr
// used to find number of nodes at a certain depth
int nCr(int n, int r) {
    return (fact(n) / (fact(r) * fact(n - r)));
}

// BINOMIAL HEAP

typedef struct Node {
    int key;
    int order;
    struct Node* child;
    struct Node* parent;
    struct Node* right;
    struct Node* left;
} Node;

Node* createNode(int key) {
    Node* node = (Node*) malloc(sizeof(Node));
    node -> key = key;
    node -> order = 0;
    node -> child = NULL;
    node -> parent = NULL;
    node -> right = NULL;
    node -> left = NULL;

    return node;
}

// method to count the number of trees in a heap
int heapLen(Node* head) {
    int count = 0;
    while(head != NULL) {
        count++;
        head = head -> right;
    }
    return count;
}

// Swap method assuming b is on right of a
void swap(Node* a, Node* b) {
    a -> right = b -> right;
    b -> left = a -> left;

    a -> left = b;
    b -> right = a;
    
    // a and b are now swapped
    // now make the elements on either side of a and b point to the correct swapped elements
    if(b -> left != NULL)
        b -> left -> right = b;
    if(a -> right != NULL)
        a -> right -> left = a;
}

// sort the binomial heap on the basis of order of the binomial trees
Node* sortHeap(Node* head) {
    Node* iterator = head;
    int len = heapLen(head);

    // bubble sort
    for(int i = 0; i < len - 1; i++) {
        // reset iterator to the beginning of the heap
        while(iterator -> left != NULL) {
            iterator = iterator -> left;
        }
        for(int j = 0; j < len - i - 1; j++) {
            if(iterator -> order > iterator -> right -> order) {
                swap(iterator, iterator -> right);
            }
            else {
                iterator = iterator -> right;
            }
        }
    }

    // sorting done
    // take pointer back to head
    while(iterator -> left != NULL) {
        iterator = iterator -> left;
    }

    return iterator;
}

// Insert to the left
Node* insert(Node* head, Node* node) {
    node -> right = head;
    head -> left = node;
    head = node;
    return head;
}

// Iterate through the heap to find trees of same order and merge them
Node* merge(Node* head) {
    Node* iterator = head;

    // Iterating through the heap
    while(iterator -> right != NULL) {
        // get the right sibling
        Node* sib = iterator -> right;
        // if the trees are of same order
        if(iterator -> order == sib -> order) {
            // right tree goes down
            if(iterator -> key < sib -> key) {
                // 'sib' tree is going down and merging with 'iterator' tree as a child, hence check if iterator has any child
                if(iterator -> child != NULL) {
                    // get current child
                    Node* childNode = iterator -> child;

                    // make sibling child
                    iterator -> child = sib;
                    //remove sibling from main heap
                    iterator -> right = sib -> right;

                    // set the previous child next to new child (sibling)
                    sib -> right = childNode;
                    sib -> left = NULL;

                    childNode -> left = sib;
                }
                // if there are no children
                else {
                    // simply make the sibling a child
                    iterator -> child = sib;
                    iterator -> right = sib -> right;

                    sib -> left = NULL;
                    sib -> right = NULL;
                }

                sib -> parent = iterator;
            }
            // left tree goes down
            else {
                if(sib -> child != NULL) {
                    Node* childNode = sib -> child;

                    sib -> child = iterator;
                    sib -> left = iterator -> left;

                    iterator -> right = childNode;
                    iterator -> left = NULL;

                    childNode -> left = iterator;
                }
                else {
                    sib -> child = iterator;
                    sib -> left = iterator -> left;

                    iterator -> left = NULL;
                    iterator -> right = NULL;
                }

                iterator -> parent = sib;
                iterator = sib;
            }

            iterator -> order++;

            // move the tree to right by swapping until it is at the correct position
            if(heapLen(head) > 1) {
                while(iterator -> order > iterator -> right -> order) {
                    swap(iterator, iterator -> right);
                }
                // go back to begining
                while(iterator -> left != NULL) {
                    iterator = iterator -> left;
                }
            }
        }
        else {
            iterator = iterator -> right;
        }
    }

    while(iterator -> left != NULL) {
        iterator = iterator -> left;
    }

    head = iterator;
    return head;
}

Node* extractMin(Node* head) {
    Node* min = head;
    Node* iterator = head;

    // find minimum root
    while(iterator != NULL) {
        if(iterator -> key < min -> key) {
            min = iterator;
        }
        iterator = iterator -> right;
    }

    printf("\nMin value in heap is: %d", min -> key);
    
    // Extract min, rmeove min from heap
    if(min -> left != NULL)
        min -> left -> right = min -> right;
    if(min -> right != NULL)
        min -> right -> left = min -> left;

    // If head is min
    if(min -> left == NULL)
        head = min -> right;

    // heap child of min
    if(min -> child != NULL) {
        Node* newHeap = min -> child;
        while(newHeap -> right != NULL) {
            newHeap -> parent = NULL;
            newHeap = newHeap -> right;
        }
        newHeap -> right = head;
        if(head != NULL)
            head -> left = newHeap;
        head = min -> child;
    }

    free(min);

    return head;
}

void displayHeap(Node* head) {
    printf("\n");
    while(head != NULL) {
        Node* iterator = head;
        
        // Perform BFS on individual Binomial heap
        int front = -1;
        int rear = -1;
        Node* BFSQueue[(1 << iterator -> order)];

        BFSQueue[++rear] = iterator;

        int depth = 0;
        int height = iterator -> order;
        int nodeCountAtDepth = 0;
        // int gapCount = (1 << (height - 1 - depth)) - 1;

        while(front <= rear && depth <= height) {
            Node* currNode = BFSQueue[++front];

            // Create appropriate gap
            if(nodeCountAtDepth == 0 && (height - 1 - depth) >= 0) {
                for(int i = 0; i < ((1 << (height - 1 - depth)) - 1)*2 - 1; i++) {
                    printf("\t");
                }
            }
            printf("%d\t", currNode -> key);

            // go to next line when a level of tree has finished displaying
            nodeCountAtDepth++;
            int nodesAtDepth_i = nCr(height, depth);
            if(nodeCountAtDepth >= nodesAtDepth_i) {
                nodeCountAtDepth = 0;
                depth++;
                printf("\n");
            }
            
            // Add adjacent nodes to queue
            Node* childIterator = currNode -> child;
            while(childIterator != NULL) {
                BFSQueue[++rear] = childIterator;
                childIterator = childIterator -> right;
            }
        }

        printf("\n---------------------\n");
        head = head -> right;
    }
}

int main() {
    int isInit = 0;
    Node* head;
    while(1) {
        printf("Enter element (Enter -1 to stop): ");
        int tmp;
        scanf("%d", &tmp);

        if(tmp == -1) {
            printf("STOPPING");
            break;
        }

        if(!isInit) {
            head = createNode(tmp);
            isInit = 1;
        }
        else {
            Node* tempNode = createNode(tmp);
            head = insert(head, tempNode);
            head = merge(head);
        }
        
        displayHeap(head);
    }

    char choice = 'y';
    while(choice == 'y' || choice == 'Y') {
        printf("\nExtract min ? (Y/N): ");
        getchar();
        scanf("%c", &choice);
        if(choice != 'y' && choice != 'Y') {
            break;
        }

        head = extractMin(head);
        head = sortHeap(head);
        head = merge(head);
        displayHeap(head);
    }

    return 0;
}