/**
 * @file threads.h
 * 
 * Declares all objects and functions regarding thread creation and destruction
*/

#ifndef THREADS_H
#define THREADS_H

#include <stdint.h>
#include <stddef.h>
#include <utils/queue.h>

typedef void (*TThreadEntry)(void *);
typedef uint32_t *TThreadContext;

/**
 * Function Defined in interrupt.s
*/
TThreadContext InitThread(uint32_t* stacktop, TThreadEntry threadWrapper, void *param, TThreadEntry entry);
void SwitchThread(TThreadContext* oldStacktop, TThreadContext newStacktop);
void StartThread(TThreadContext newStacktop);


typedef struct TCB {

    uint32_t threadID;

    uint32_t* stacktop;
    uint32_t* stack;
}TCB;

/** @brief Creates a new thread and adds it to the ready list
 * 
 * @param entry entry function for new thread
 * 
 * @param param parameter for new thread's function
 * 
 * @return True if thread added, false if no more room for threads
*/
bool threadCreate(TThreadEntry entry, void* param);

/** @brief Yields thread and does a context switch with next ready threade
 * 
 * @returns true if yield successful, false if there are no other threads on ready
 * list
*/
bool threadYield(void);

/** @brief stub for threads
 * 
 * @param entry entry function for new thread
 * 
 * @param param parameter for new thread's function
 * 
 * @returns void
*/
void threadWrapper(TThreadEntry entry, void* param);

/** @brief Gracefully destroys thread an does a context switch with new thread
 * 
 * @returns void
*/
void threadExit(void);

#endif 