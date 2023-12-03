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

    if(lock -> holderID == scheduler -> threadID) {
        lock -> acquired = true;
        return true;
    }

    // Lock unowned
    if(lock -> acquired == false) {
        lock -> holderID = true;
        return true;
    }

    return false;
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

