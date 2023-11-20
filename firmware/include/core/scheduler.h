#include <threading/threads.h>
#include <stdlib.h>
#include <utils/myqueue.h>

#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct Scheduler {
    Queue* ready;
    Queue* waiting;
    TCB* running;
    
    int* finished;
    
}Scheduler;

extern Scheduler scheduler;
extern int MAX_THREADS;
extern int THREAD_STACK_SIZE;
extern int threadCounter;

// Queue Sizes
// Need to be outside of struct because Q -> size returns memory address of struct for some reason
extern int readySize;
extern int waitingSize;
extern int finishedSize;

/* Init Scheduler  with main */
int initScheduler();

#endif