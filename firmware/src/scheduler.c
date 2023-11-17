/**
 * @file scheduler.c
 * 
 * Implementation for scheduler
*/
#include <threading/threads.h>
#include <core/scheduler.h>

TCB* ready[3];

// int initScheduler() {

//     // Add kernel thread to running list
//     TCB* kernel = malloc(sizeof(TThreadContext));
//     kernel -> threadID = 0;
//     kernel -> thread = malloc(sizeof(TThreadContext));

//     ready[0] = kernel;

//     return 0;
    
// }

// int threadNum = 0;
// int switchThreads() {
//     int temp = threadNum;
//     threadNum = (threadNum + 1) % 2;
//     SwitchThread(&(ready[temp] -> thread), ready[threadNum] -> thread);

//     return 0;
// }