/**
 * @file bounded-buffer.h
*/

#include <stdint.h>
#include <stdbool.h>

#pragma once

typedef struct Queue {
    uint32_t MAX_SIZE;
    uint32_t in;
    uint32_t out;
    uint32_t size;

    void** queue;
} Queue;


/** @brief Dynamically allocates and initializes a new queue with a
 *         maximum size, size
 *
 *  @param size the maximum size of the queue
 *
 *  @return a pointer to a new queue_t
 */
Queue* queueNew(int size);

/** @brief Delete your queue and free all of its memory.
 *
 *  @param q the queue to be deleted.  Note, you should assign the
 *  passed in pointer to NULL when returning (i.e., you should set
 *  *q = NULL after deallocation).
 *
 */
void queueDelete(Queue** q);


/** @brief push an element onto a queue
 *
 *  @param q the queue to push an element into.
 *
 *  @param elem th element to add to the queue
 *
 *  @return A bool indicating success or failure.  Note, the function
 *          should succeed unless the q parameter is NULL.
 */
bool queuePush(Queue* q, void *elem);


/** @brief pop an element from a queue.
 *
 *  @param q the queue to pop an element from.
 *
 *  @param elem a place to assign the popped element.
 *
 *  @return A bool indicating success or failure.  Note, the function
 *          should succeed unless the q parameter is NULL.
 */
bool queuePop(Queue* q, void **elem);

/** @brief pop an element from a queue.
 *
 *  @param q the queue to pop an element from.
 *
 *  @param elem a place to assign the front element without popping
 *
 *  @return A bool indicating success or failure.  Note, the function
 *          should succeed unless the q parameter is NULL.
 */
bool queuePeek(Queue* q, void** elem);
