#include <stdint.h>
#include <stdlib.h>
#include <threading/threads.h>
#include <threading/locks.h>
#include <string.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;


uint32_t MediumControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index);

//Video memory and medium sprite stuff:
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
volatile uint8_t *MEDIUM_DATA = (volatile uint8_t *)(0x500D0000);
volatile uint32_t *MEDIUM_PALETTE = (volatile uint32_t *)(0x500F2000);
volatile uint32_t *MEDIUM_CONTROL = (volatile uint32_t *)(0x500F5F00);
volatile uint32_t *MODE_REGISTER = (volatile uint32_t *)(0x500F6780);

//Syscall setup
uint32_t GetTicks(void);
uint32_t GetController(void);
uint32_t GetCmd(void);

void func1(void* param);
void func2(void* param);

Lock* newLock2;

int main() {

    newLock2 = lockCreate();

    threadCreate(func1, NULL);
    threadCreate(func2, NULL);

    while (1) {
        char* buffer = "Cartridge Thread";
        strcpy((char*)VIDEO_MEMORY, buffer);
        threadYield();
    }
    return 0;
}

uint32_t MediumControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index){
    return (((uint32_t)index)<<24) | (((uint32_t)z)<<21) | (((uint32_t)y+32)<<12) | (((uint32_t)x+32)<<2) | (palette & 0x3);
}

void func1(void* num) {

  int number = 0;

  lockAcquire(newLock2);
  threadYield();

  while(1) {
    number++;
    char* buffer = "Thread One";
    strcpy((char*)VIDEO_MEMORY, buffer);

    if(number > 5) {
      lockRelease(newLock2);
    }

    threadYield();

  }

  return;
}

void func2(void* num) {

  int i = 12;
  while(1) {
    char* buffer = "Thread Two";
    strcpy((char*)VIDEO_MEMORY, buffer);

    lockAcquire(newLock2);
    // Critical section
    char* buffer2 = "Thread Two Unlocked";
    strcpy((char*)VIDEO_MEMORY, buffer2);

    int newnum = 12;
    lockRelease(newLock2);
    int num = (int)num;
    num++;
    num++;

  }
  
  return;
}