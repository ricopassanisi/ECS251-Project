/**
 * @file threads.h
 * 
 * Declares all objects and functions regarding thread creation and destruction
*/

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <utils/queue.h>

typedef void (*TThreadEntry)(void *);
typedef uint32_t *TThreadContext;

/**
 * Function Defined in interrupt.s
*/
TThreadContext InitThread(uint32_t* stacktop, TThreadEntry threadWrapper, void *param, TThreadEntry entry);
void SwitchThread(TThreadContext* oldStacktop, TThreadContext newStacktop, uint32_t threadSP, uint32_t cartgp);
void StartThread(TThreadContext newStacktop, uint32_t cartgp);


typedef struct TCB {

    uint32_t threadID;

    uint32_t* stacktop;
    uint32_t* stack;
}TCB;

extern uint32_t threadCounter;

/** @brief Creates a new thread and adds it to the ready list
 * 
 * @param entry entry function for new thread
 * 
 * @param param parameter for new thread's function
 * 
 * @return True if thread added, false if no more room for threads
*/
bool threadCreate(TThreadEntry entry, void* param);

/** @brief Yields thread and does a context switch with next ready thread
 * 
 * @param threadSP Stack Pointer for thread that is yielding
 * 
 * @returns true if yield successful, false if there are no other threads on ready
 * list
*/
bool threadYield(uint32_t threadSP);

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