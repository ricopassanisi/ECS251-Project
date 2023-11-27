#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "mem.c"

volatile int global = 42;
volatile uint32_t controller_status = 0;
volatile uint32_t *MEDIUM_PALETTE = (volatile uint32_t *)(0x500F2000);
volatile uint32_t cmd_interrupt = 0;
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
volatile uint32_t *CartridgeStatus = (volatile uint32_t *)(0x4000001C);
typedef void (*FunctionPtr)(void);

int main() {
    char *Buffer = malloc(32);
    strcpy(Buffer,"OS STARTED");
    strcpy((char *)VIDEO_MEMORY,Buffer);
    
    //Wait for cartridge 
    while (1){
        if(*CartridgeStatus & 0x1){
            FunctionPtr Fun = (FunctionPtr)((*CartridgeStatus) & 0xFFFFFFFC);
            Fun();
        }
    }

    return 0;
}
