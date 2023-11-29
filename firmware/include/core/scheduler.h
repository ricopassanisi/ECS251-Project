#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <threading/threads.h>
#include <stdlib.h>
#include <utils/queue.h>
#include <stdbool.h>





typedef struct Scheduler {
    Queue* ready;
    uint32_t threadID;
    TCB* running;
}Scheduler;

extern Scheduler* scheduler;


/** @brief initialize scheduler with queues and main thread
 * 
 * @returns True is successful, false if failed
*/
bool initScheduler(void);

/** @brief Free memory associated with scheduler
 * 
 * @returns void
*/
void destroyScheduler(void);

#endif