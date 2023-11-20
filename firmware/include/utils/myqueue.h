#include <stdlib.h>

#ifndef MYQUEUE_H
#define MYQUEUE_H

/**
 * TCB Queue node
*/
typedef struct Node {
    struct Node* next;
    struct Node* prev;

    void* data;
}Node;

/**
 * TCB Queue (FIFO Scheduling, Cooperative)
 */
typedef struct Queue {
    Node* head;
    Node* tail;

    int size;
    int MAX_SIZE;
}Queue;

/**
 * Operations don't need to be 'thread safe' because 
 * uniprocessor & interrupts disabled during operations
*/
int queueEnqueue(Queue* Q, void* elem);

/**
 * Dequeue next item from queue and put in elem
*/
int queueDequeue(Queue* Q, void** elem);

/**
 * Removes an element from anywhere in the queue
*/
int queueRemove(Queue* Q, void** elem);

/**
 * Allocates space for new queue object
*/
Queue* queueInit(int maxSize);

void printQueue(Queue* Q);
#endif