#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <core/scheduler.h>
#include <threading/threads.h>
#include <threading/locks.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile uint32_t *MEDIUM_PALETTE = (volatile uint32_t *)(0x500F2000);
volatile uint32_t cmd_interrupt = 0;
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
volatile uint32_t *CartridgeStatus = (volatile uint32_t *)(0x4000001C);
typedef void (*FunctionPtr)(void);

void func1(void*);
void func2(void*);

Lock newLock;

int max_counter = 1000;



int main() {

    int a = 4;
    int b = 12;
    int last_global = 42;

    initScheduler();

    // threadCreate(func1, NULL);
    // threadCreate(func2, NULL);

    int counter = 0;

    int x_pos = 12;
    char *Buffer = malloc(32);
    itoa(counter, Buffer, 10);
    strcpy((char *)VIDEO_MEMORY,Buffer);
    
    //Wait for cartridge 
    bool flag = false;
    while (1){
        if(*CartridgeStatus & 0x1){
            FunctionPtr cartridge = (FunctionPtr)((*CartridgeStatus) & 0xFFFFFFFC);

            threadCreate(cartridge, NULL);
            while (1){
              threadYield();
            }
        }

        itoa(counter, Buffer, 10);
        strcpy((char *)VIDEO_MEMORY,Buffer);
        counter = (counter + 1) % max_counter;

        // threadYield();
    }

    // Some cleanup code here

    return 0;
}

extern char _heap_base[];
extern char _stack[];

char *_sbrk(int numbytes){
  static char *heap_ptr = NULL;
  char *base;

  if (heap_ptr == NULL) {
    heap_ptr = (char *)&_heap_base;
  }

  if((heap_ptr + numbytes) <=_stack) {
    base = heap_ptr;
    heap_ptr += numbytes;
    return (base);
  }
  else {
    //errno = ENOMEM;
    return NULL;
  }

}


void func1(void* num) {

  int number = 0;

  lockAcquire(&newLock);
  threadYield();

  while(1) {
    number++;

    if(number > 5) {
      lockRelease(&newLock);
    }

    threadYield();

  }

  return;
}

void func2(void* num) {

  int i = 12;
  while(1) {

    lockAcquire(&newLock);
    // Critical section

    int newnum = 12;
    lockRelease(&newLock);
    int num = (int)num;
    num++;
    num++;

  }
  
  return;
}