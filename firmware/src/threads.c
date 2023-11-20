/**
 * @file threads.c
 * 
 * Implements threading functions
*/

#include <threading/threads.h>
#include <core/scheduler.h>

// If this changes, then change interrupt.s as well
// Stack pointer needs to be adjusted accordingly

/**
 * Creates a new thread and adds it to the scheduler
*/
TCB* threadCreate(TThreadEntry entry, void* param) {

    // Init new TCB
    TCB* newTCB = malloc(sizeof(TCB));
    newTCB -> threadID = threadCounter;
    newTCB -> waitingFor = NONE;
    newTCB -> waitingItemID = -1;
    
    // Don't allocate stack top for main thread
    if(threadCounter != 0){
        newTCB -> stacktop = InitThread(newTCB -> stack + 128, entry, param);
    }

    threadCounter++;
    return newTCB;
}

int threadDestroy(TCB* thread) {
    int threadID = thread -> threadID;
    free(thread);
    // Add ID to finished list
}

int threadYieldCall(void) {
    TCB* chosenTCB;
    TCB* finishedTCB;

    // Context Switch
    if(queueDequeue(scheduler.ready, (void*)&chosenTCB) == 0) {
        // Nothing to do if there are no other threads on the ready list
    } else {
        // Else, move around pointers
        finishedTCB = scheduler.running;
        queueEnqueue(scheduler.ready, (void*)finishedTCB);
        scheduler.running = chosenTCB;

        int num1 = (int)chosenTCB -> stacktop;
        int num2 = (int)finishedTCB -> stacktop;
        
        // Context Switch
        SwitchThread(&(finishedTCB -> stacktop), chosenTCB -> stacktop);
    }

    // This won't ever run?
    return 0;
}