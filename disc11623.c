// Discussion for ECS 251 on November 6, 2023
// Creating threads, Switch Context

// In main.c
#include <stddef.h>
// These are declarations
void OtherThreadFunction(void *);
typedef void (*TThreadEntry)(void *);
typedef uint32_t *TThreadContext;

uint32_t *InitThread(unint32_t *stacktop, TThreadEntry entry, void *param);
void SwitchThread(uint32_t *oldcontext, uint32_t newcontext);

// In main
uint32_t OtherThreadStack[128];
TThreadContext OtherThread;
TThreadContext ThisThread;

OtherThread = InitThread(OtherThreadStack + 128, OtherThreadFunction, &ThisThread);

SwitchThread(&ThisThread, OtherThread);

void OtherThreadFunction(void *) {
    int lastglobal = global;
    while(1) {
        if(global != lastglobal) {
            SwitchThread()
        }
    }
}
