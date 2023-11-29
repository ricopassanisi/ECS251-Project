/**
 * @file locks.c
 * 
 * Implementation for locks
 * Interrupts should already be disabled by the syscalls
*/

#include <stdint.h>
#include <stdbool.h>
#include <threading/locks.h>
#include <utils/utils.h>
#include <core/scheduler.h>



Lock* lockCreate(void) {

    Lock* newLock = malloc(sizeof(Lock));
    newLock -> acquired = false;
    newLock -> holderID = 0;

    return newLock;
}
bool lockAcquire(Lock* lock){
    int number = lock -> holderID;
    // Check if current thread holds lock
    if(lock -> holderID == scheduler -> threadID && lock -> acquired == true) {
        return false; // Can't acquire a lock that is acquired and owned by current thread
    }

    // Spin until lock is free
    while(lock -> acquired == true) {
        threadYield();
    }

    lock -> acquired = true;
    lock -> holderID = scheduler -> threadID;                   

    return true;
}


bool lockRelease(Lock* lock) {
    // Check if current thread is not the owner of the lock
    if(lock -> holderID != scheduler -> threadID) {
        return false; // Can't release an unowned lock (covers lock already unlocked too)
    }

    lock -> holderID = 0;
    lock -> acquired = false;

    return true;
}

