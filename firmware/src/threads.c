/**
 * @file threads.c
 * 
 * Implements threading functions
*/

#include <threading/threads.h>
#include <core/scheduler.h>
#include <utils/queue.h>
#include <stdbool.h>
#include <utils/utils.h>

void _setGP(void);

uint32_t threadCounter = 0;
/**
 * Creates a new thread and adds it to the scheduler
*/
bool threadCreate(TThreadEntry entry, void* param) {
    TCB* newThread = malloc(sizeof(TCB));
    newThread -> threadID = threadCounter;
    newThread -> stacktop = 0x0;
    newThread -> stack = calloc(sizeof(uint32_t), 128);

    // If not creating main thread, set stacktop
    if(threadCounter != 0) {
            newThread -> stacktop = InitThread(newThread -> stack + 128, threadWrapper, entry, param);

    }

    if(queuePush(scheduler -> ready, (void*)newThread) == false) {
        free(newThread -> stack);
        free(newThread);
        return false; // Return false if thread list full
    }


    threadCounter++;

    return true;

}

bool threadYield(uint32_t threadSP) {

    TCB* finishedThread, *chosenThread;
    if(scheduler -> ready -> size <= 1) {
        return false;
    }

    // Get finished thread
    queuePop(scheduler -> ready, (void*)&finishedThread);

    // Peek new thread
    queuePeek(scheduler -> ready, (void*)&chosenThread);

    // Put finished thread back into ready list at the end
    queuePush(scheduler -> ready, (void*)finishedThread);

    // Context Switch
    scheduler -> threadID = chosenThread -> threadID;
    SwitchThread(&(finishedThread -> stacktop), chosenThread -> stacktop, threadSP, cartridgeGP);

    return true;
}

void threadWrapper(TThreadEntry entry, void* param) {

    entry(param);

    _setGP(); // set firmware global pointer before proceeding
    threadExit();

    return;
}

void threadExit(void) {
    // TODO: Disable interrupts
    TCB* chosenThread, *finishedThread;

    queuePop(scheduler -> ready, (void*)&finishedThread);
    queuePeek(scheduler -> ready, (void*)&chosenThread);

    free(finishedThread -> stack);
    free(finishedThread);

    scheduler -> threadID = chosenThread -> threadID;
    StartThread(chosenThread -> stacktop, cartridgeGP);

    return;
}