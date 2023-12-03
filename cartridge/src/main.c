#include <stdint.h>
#include <stdlib.h>
#include <threading/threads.h>
#include <threading/locks.h>
#include <string.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;


//Video memory and medium sprite stuff:
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);

//Syscall setup
uint32_t GetTicks(void);
uint32_t GetController(void);
uint32_t GetCmd(void);

void func1(void* param);
void func2(void* param);

void hang_print(char* str);


int main() {

  // threadCreate(func1, NULL);
  // threadCreate(func2, NULL);

  while (1) {
    hang_print("CARTRIDGE YIELDING");
    threadYield();

    hang_print("CARTRIDGE DONE YIELDING");
  }


  /* KEEP THIS HERE */
  threadExit(); // Calling thread exit in the in the main thread will 'eject' cartridge
  return 0;
}

void func1(void* param) {
  hang_print("FUNC ONE STARTED");

  while(1) {
    hang_print("Func ONE IN WHILE LOOP");
    threadYield();
  }

  hang_print("FUNC ONE ENDING");
  return;
}

void func2(void* param) {
  hang_print("FUNC TWO STARTED");

  threadYield();


  hang_print("FUNC TWO ENDING");

  return;
}


void hang_print(char* str) {
  for(int i = 0; i < 500000; i++)
  strcpy((char*)VIDEO_MEMORY, str);

  return;
}