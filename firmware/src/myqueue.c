/**
 * @file scheduler.c
 * 
 * Implementation for scheduler
*/
#include <utils/myqueue.h>
#include <core/scheduler.h>
#include <threading/threads.h>




Queue* queueInit(int maxSize){
    Queue* Q = malloc(sizeof(Queue));
    Q -> MAX_SIZE = maxSize;
    Q -> size = 0x0;
    Q -> tail = NULL;
    Q -> head = NULL;

    int num = Q -> size;
    int num2 = (*Q).size;

    return Q;
}

int queueEnqueue(Queue* Q, void* elem) {

    int qSize = *(int*)(Q -> size);
    // If full
    if(qSize >= 32) {
        return 0;
    }

    Node* node = malloc(sizeof(Node));
    node -> next = NULL;
    node -> prev = NULL;
    node -> data = elem;

    // If queue is empty
    if(qSize == 0) {
        Q -> head = node;
        Q -> tail = node;

    // If there's only one node
    } else if(qSize == 1) {
        Q -> head -> next = node;
        Q -> tail = node;
        node -> prev = Q -> head;

    // Else, append to end
    } else {
        Q -> tail -> next = node;
        node -> prev = Q -> tail;
        Q -> tail = node;
    }

    *(int*)(Q -> size) = qSize + 1;
    return 1;
}

int queueDequeue(Queue* Q, void** elem) {
    int qSize = *(int*)(Q -> size);
    if(qSize <= 0) {
        return 0;
    }

    // 
    if(qSize == 1) {
        (*elem) = Q -> head -> data;
        Q -> head = NULL;
        Q -> tail = NULL;
    } else {
        (*elem) = Q -> head -> data;
        Node* temp = Q -> head;

        Q -> head = temp -> next;
        Q -> head -> prev = NULL;
    }

    *(int*)(Q -> size) = qSize -1;
    return 1;
}

/**
 * Implementation exclusively for removing a thread by ID in the queue
*/
int queueRemoveThread(Queue* Q, void** elem, int threadID) {
    int qSize = *(int*)(Q -> size);
    if(qSize <= 0) {
        return 0;
    }
    if(qSize == 1) {
        TCB* tcb = Q -> head -> data;
        if(tcb -> threadID == threadID) {
            *elem = tcb;
            Q -> size--;
            Q -> head = NULL;
            Q -> tail = NULL;
            return 1;
        } else {
            return 0;
        }
    }

    // Else, runner
    Node* runner = Q -> head;
    while(runner != NULL) {
        TCB* tcb = runner -> data;
        if(tcb -> threadID == threadID) {
            *elem = tcb;
            // Check if head
            if(Q -> head == runner) {
                Q -> head = runner -> next;
                Q -> head -> prev = NULL;
                *(int*)(Q->size) = qSize - 1;
                return 1;
            }

            // Check if tail
            if(Q -> tail == runner) {
                Q -> tail = runner -> prev;
                Q -> tail -> next = NULL;
                *(int*)(Q->size) = qSize - 1;
                return 1;
            }

            // Else, somewhere in the middle
            Node* tmp = runner -> prev;
            tmp -> next = runner -> next;
            runner -> next -> prev = tmp;
            *(int*)(Q->size) = qSize - 1;
            return 1;

        } else {
            runner = runner -> next;
        }
    }
    return 0;

}

void printQueue(Queue* Q) {
    Node* runner = Q -> head;
    while(runner != NULL) {
        TCB* tcb = runner -> data;
        // printf("%i, ", tcb -> threadID);
        runner = runner -> next;
    }
    // printf("\n");
    // runner = Q -> tail;
    // while(runner != NULL) {
    //     TCB* tcb = runner -> data;
    //     // printf("%i, ", tcb -> threadID);
    //     runner = runner -> prev;
    // }
    // printf("\n");

    return;
}

/**
 * Testing code
*/

// TCB* makeTCB(int i) {
//     TCB* newNode = malloc(sizeof(Node));
//     newNode -> threadID = i;
//     return newNode;
// }
// int main(void) {
//     printf("Starting\n\n");
//     Queue* queue = queueInit(100);
//     for(int i = 0; i < 10; ++i) {
//         TCB* tcb = makeTCB(i);
//         queueEnqueue(queue, (void*)tcb);
//     }
//     printQueue(queue);

//     TCB* elem;
//     queueDequeue(queue, (void*)&elem);
//     printf("Extracted: %i\n", elem -> threadID);
//     printQueue(queue);

//     queueDequeue(queue, (void*)&elem);

//     printf("Extracted: %i\n", elem -> threadID);
//     printQueue(queue);

//     queueRemoveThread(queue, (void*)&elem, 6);
//     printf("Extracted: %i\n", elem -> threadID);
//     printQueue(queue);

//     queueRemoveThread(queue, (void*)&elem, 2);
//     printf("Extracted: %i\n", elem -> threadID);
//     printQueue(queue);

//     queueRemoveThread(queue, (void*)&elem, 9);
//     printf("Extracted: %i\n", elem -> threadID);

//     printQueue(queue);
//     return 0;
// }