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
int threadCounter = 1;
TCB* threadCreate(TThreadEntry entry, void* param) {

    // Init new TCB
    TCB* newTCB = malloc(sizeof(TCB));
    newTCB -> threadID = threadCounter;
    
    // Don't allocate stack top for main thread
    if(threadCounter != 0){
        newTCB -> stacktop = InitThread(newTCB -> stack + 128, entry, param);
    }

    ++threadCounter;
    return newTCB;
}

int threadDestroy(TCB* thread) {
    int threadID = thread -> threadID;
}