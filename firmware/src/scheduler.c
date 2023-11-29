/**
 * @file scheduler.c
 * 
 * Implementation for scheduler
*/
#include <core/scheduler.h>

Scheduler* scheduler = NULL;

bool initScheduler(void) {
    scheduler = malloc(sizeof(Scheduler));
    // Allocate new queue for lists
    scheduler -> ready = queueNew(32);
    scheduler -> running = NULL;

    // Allocate main thread
    threadCreate(NULL, NULL);
    scheduler -> threadID = 0;

    return true;
}

void destroyScheduler(void) {
    TCB* runner = NULL;

    // While something is still in the ready list, destroy it
    while(queuePop(scheduler -> ready, (void*)&runner) == true) {
        free(runner -> stack);
        free(runner);
    }

    // Finally free scheduler
    queueDelete(&scheduler -> ready);
    free(scheduler);

    return;
}