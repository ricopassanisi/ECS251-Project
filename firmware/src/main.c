#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <core/scheduler.h>
#include <threading/threads.h>
#include <mem.c>

volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile uint32_t cmd_interrupt = 0;
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
volatile uint32_t *CartridgeStatus = (volatile uint32_t *)(0x4000001C);
typedef void (*FunctionPtr)(void);


int main() {
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;
    char *Buffer = malloc(32);
    strcpy(Buffer,"OS STARTED");
    strcpy((char *)VIDEO_MEMORY,Buffer);

    /* Initialization Stuff */
    initScheduler();
    
    //Wait for cartridge 
    while (1){
        if(*CartridgeStatus & 0x1){
            
            FunctionPtr cartridge = (FunctionPtr)((*CartridgeStatus) & 0xFFFFFFFC);
            threadCreate(cartridge, NULL);

            while(threadYield() == true) {
              ; // Spin while the cartridge thread still exists
            };

            // Once here, the cartridge has exited
            break;
        }
    }
    // Cleanup code here...
    destroyScheduler();
    return 0;
}

/*
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
*/