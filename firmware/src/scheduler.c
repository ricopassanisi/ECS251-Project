/**
 * @file scheduler.c
 * 
 * Implementation for scheduler
*/
#include <core/scheduler.h>

Scheduler* scheduler;


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