#include <threading/threads.h>
#include <stdlib.h>
#include <utils/queue.h>
#include <stdbool.h>

#pragma once


typedef struct Scheduler {
    Queue* ready;
    TCB* running;
}Scheduler;

extern Scheduler* scheduler;

/** @brief initialize scheduler with queues and main thread
 * 
 * @returns True is successful, false if failed
*/
bool initScheduler(void);