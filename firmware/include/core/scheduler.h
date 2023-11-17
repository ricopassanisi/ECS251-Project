#include <stddef.h>
#include <stdint.h>
#include <threading/threads.h>
#include <stdlib.h>




// typedef struct TCB {
//     int threadID;
//     int priority;
//     void* param;
//     TThreadContext thread;
// }TCB;


extern TCB* ready[];
extern TCB* waiting[];
extern int finished[];
extern TCB* running;

typedef struct Scheduler {
    TCB* ready;
    TCB* waiting;
    TCB* running;
    
    int* finished;
    
}Scheduler;

/* Init Scheduler  with main */
int initScheduler();

/* Moves next thread ready to running & running thread to ready list */
int switchThreads();

/**
 * Wakes thread from waiting list and adds it to ready list
*/
int wakeThread(int threadID);

int threadDone(int threadID);