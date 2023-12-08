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

    // TODO: Implement for when main thread is thread 0

    // This should only return false for the main thread since
    // that is never deleted until cleanup
    if(scheduler -> ready -> size <= 1) {
        return false;
    }

    TCB* chosenThread, *finishedThread;

    queuePop(scheduler -> ready, (void*)&finishedThread);
    queuePeek(scheduler -> ready, (void*)&chosenThread);
    queuePush(scheduler -> ready, (void*)finishedThread);

    if(finishedThread -> threadID != 0) {
        finishedThread -> stacktop = (uint32_t*)threadSP;
    }

    // If current thread is main thread, use switch context instead
    if(scheduler -> threadID == 0) {

        scheduler -> threadID = chosenThread -> threadID;
        SwitchThread(&(finishedThread -> stacktop), chosenThread -> stacktop, cartridgeGP);
        
        return true;

    }
    scheduler -> threadID = chosenThread -> threadID;

    bool setCartGP = true;
    if(chosenThread -> threadID == 0) {
        setCartGP = false;

    }

    StartThread(chosenThread -> stacktop, cartridgeGP, setCartGP);

    return true; // This only get's called for main
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

    // If the main cartridge is exiting
    // Delete all other threads except for thread 0;
    if(scheduler -> threadID == 1) {
        while(scheduler -> ready -> size > 1) {
            queuePop(scheduler -> ready, (void*)&chosenThread);
            if(chosenThread -> threadID == 0) {
                queuePush(scheduler -> ready, (void*)&chosenThread);
            } else {
                free(chosenThread -> stack);
                free(chosenThread);
            }
        }

        // Main thread should be the only thread in the queue by now
        queuePeek(scheduler -> ready, (void*)&chosenThread);
        csr_disable_interrupts();
        StartThread(chosenThread -> stacktop, cartridgeGP, false);

        return;
    }

    queuePop(scheduler -> ready, (void*)&finishedThread);
    queuePeek(scheduler -> ready, (void*)&chosenThread);

    free(finishedThread -> stack);
    free(finishedThread);

    scheduler -> threadID = chosenThread -> threadID;
    bool setCartGP = true;
    if(scheduler -> threadID == 0) {
        setCartGP = false;
    }
    StartThread(chosenThread -> stacktop, cartridgeGP, setCartGP);

    return;
}