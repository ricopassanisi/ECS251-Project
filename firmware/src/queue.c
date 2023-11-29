/**
 * @file bounded-buffer.c
*/

#include <utils/queue.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <threading/threads.h>

Queue* queueNew(int size) {
    // Allocate new instance of queue_t
    Queue* ret = malloc(sizeof(Queue));


    // Initialize queue variables
    ret->MAX_SIZE = size;
    ret->in = 0;
    ret->out = 0;
    ret->size = 0;

    // Initiailize queue itself
    ret->queue = (void **) calloc(size, sizeof(void *));

    // Return new Queue type
    return ret;
}

void queueDelete(Queue** q) {
    // delete the queue
    free((*q)->queue);

    // delete struct
    free(*q);

    return;
}

bool queuePush(Queue* q, void* elem) {
    // If Q doesn't exist
    if (q == NULL) {
        return false;
    }

    // If queue is full, return false
    if (q->size == q->MAX_SIZE) {
        return false;
    }

    int in = q -> in;
    int out = q -> out;


    // Insert elem into queue and increment in counter
    q->queue[q->in] = elem;

    int newThread = ((TCB*)(q->queue[q->out])) -> threadID;
    q->in = (q->in + 1) % (q->MAX_SIZE);
    q->size += 1;

    return true;
}

bool queuePop(Queue* q, void** elem) {

    // If queue doesn't exist
    if (q == NULL) {
        return false;
    }

    // While queue is empty, return false
    if (q->size == 0) {
        return false;
    }

    int in = q -> in;
    int out = q -> out;

    // Insert elem into queue and increment in counter
    *elem = (q->queue[q->out]);
    int number = ((TCB*)*elem) -> threadID;

    q->out = (q->out + 1) % (q->MAX_SIZE);
    q->size -= 1;


    return true;
}

bool queuePeek(Queue* q, void** elem){
    if (q == NULL) {
        return false;
    }

    // If q empty, return false
    if (q -> size == 0) {
        return false;
    }

    // Set pointer to top element
    *elem = (q->queue[q->out]);

    return true;
}

// typedef struct Node {
//     int id;
// } Node;

// int main(void) {

//     Node* elem1 = malloc(sizeof(Node));
//     elem1 -> id = 123;

//     Node* elem2 = malloc(sizeof(Node));
//     elem2 -> id = 456;

//     Queue* q = queueNew(20);

//     Node* res;
//     queuePush(q, (void*)elem1);
//     queuePop(q, (void*)&res);

//     printf("Gotten\t%i\n", res -> id);

//     queueDelete(&q);

//     return 0;
// }