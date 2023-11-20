/**
 * @file scheduler.c
 * 
 * Implementation for scheduler
*/
#include <threading/threads.h>
#include <core/scheduler.h>
#include <stdbool.h>


Scheduler scheduler;
int MAX_THREADS = 32;
int THREAD_STACK_SIZE = 128;
int threadCounter = 0;

// Queue sizes
int readySize = 0;
int waitingSize = 0;
int finishedSize = 0;

int initScheduler() {
    scheduler.ready = queueInit(MAX_THREADS);
    scheduler.waiting = queueInit(MAX_THREADS - 1);
    scheduler.finished = calloc(sizeof(uint32_t), 128);

    TCB* mainThread = threadCreate(NULL, NULL);

    scheduler.running = mainThread;

    return 0;
}