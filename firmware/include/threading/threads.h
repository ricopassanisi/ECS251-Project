/**
 * @file threads.h
 * 
 * Declares all objects and functions regarding thread creation and destruction
*/

#ifndef THREADS_H
#define THREADS_H

#include <stdint.h>
#include <stddef.h>
#include <utils/myqueue.h>

typedef void (*TThreadEntry)(void *);
typedef uint32_t *TThreadContext;

/**
 * Function Defined in interrupt.s
*/
TThreadContext InitThread(uint32_t* stacktop, TThreadEntry entry,void *param);
void SwitchThread(TThreadContext* oldStacktop, TThreadContext newStacktop);

// const int STACK_SIZE = 128;

enum WaitingFor {
    LOCK = 1,
    THREAD,
    NONE
};

/**
 * Thread Control Block
*/
typedef struct TCB{
    int threadID;
    int priority;

    int waitingFor;
    int waitingItemID;

    uint32_t* stacktop;
    uint32_t stack[128];
}TCB;

/**
 * Creates a new thread and adds it to the scheduler
*/
TCB* threadCreate(TThreadEntry entry, void* param);

/**
 * Moves thread to waiting list to wait for some event to happen
*/
// int threadWait(TCB* thread, int eventID);

/**
 * Thread yields CPU and moves to ready list
*/
// int threadYield(TCB* thread);
// /**
//  * Destroys thread and frees memory
// */
// int threadDestroy(TCB* thread);

int threadYieldCall(void);


#endif