#include <stdint.h>
#include <stdlib.h>
#include <sprite.c>
#include <background.c>
#include "video.c"
#include <threading/threads.h>
#include <threading/locks.h>
#include "../include/controller.h"

extern uint8_t _erodata[];
extern uint8_t _data[];
extern uint8_t _edata[];
extern uint8_t _sdata[];
extern uint8_t _esdata[];
extern uint8_t _bss[];
extern uint8_t _ebss[];

// Adapted from https://stackoverflow.com/questions/58947716/how-to-interact-with-risc-v-csrs-by-using-gcc-c-code
__attribute__((always_inline)) inline uint32_t csr_mstatus_read(void){
    uint32_t result;
    asm volatile ("csrr %0, mstatus" : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void csr_mstatus_write(uint32_t val){
    asm volatile ("csrw mstatus, %0" : : "r"(val));
}

__attribute__((always_inline)) inline void csr_write_mie(uint32_t val){
    asm volatile ("csrw mie, %0" : : "r"(val));
}

__attribute__((always_inline)) inline void csr_enable_interrupts(void){
    asm volatile ("csrsi mstatus, 0x8");
}

__attribute__((always_inline)) inline void csr_disable_interrupts(void){
    asm volatile ("csrci mstatus, 0x8");
}

__attribute__((always_inline)) inline uint32_t csr_read_mip(void) {
    uint32_t result;
    asm volatile ("csrr %0, mip" : "=r"(result));
    return result;
}

__attribute__((always_inline)) inline void csr_write_mip(uint32_t val) {
    asm volatile ("csrw mip, %0" : : "r"(val));
} 

#define MTIME_LOW       (*((volatile uint32_t *)0x40000008))
#define MTIME_HIGH      (*((volatile uint32_t *)0x4000000C))
#define MTIMECMP_LOW    (*((volatile uint32_t *)0x40000010))
#define MTIMECMP_HIGH   (*((volatile uint32_t *)0x40000014))
#define CONTROLLER      (*((volatile uint32_t *)0x40000018))
#define INTERRUPT_ENABLE (*((volatile uint32_t *)0x40000000))
#define INTERRUPT_PENDING (*((volatile uint32_t *)0x40000004))

void init(void){
    uint8_t *Source = _erodata;
    uint8_t *Base = _data < _sdata ? _data : _sdata;
    uint8_t *End = _edata > _esdata ? _edata : _esdata;

    while(Base < End){
        *Base++ = *Source++;
    }
    Base = _bss;
    End = _ebss;
    while(Base < End){
        *Base++ = 0;
    }
    INTERRUPT_ENABLE = INTERRUPT_ENABLE | 0xFFF;
    csr_write_mie(0x88F);       // Enable all interrupt soruces
    csr_enable_interrupts();    // Global interrupt enable

    MTIMECMP_LOW = 1;
    MTIMECMP_HIGH = 0;
}

extern volatile int global;
extern volatile uint32_t controller_status;
extern volatile uint32_t cmd_interrupt;

void c_interrupt_handler(uint32_t cause){
    
    if((INTERRUPT_PENDING) & 0x4) { //Cmd interrupt?
        cmd_interrupt = 1;
        INTERRUPT_PENDING = INTERRUPT_PENDING | 0x4;
    } else if((INTERRUPT_PENDING) & 0x2) { //Video interrupt?
        //write all video memory
        load_video_data();
        clear_video_queue();
        //clear pending bit
        INTERRUPT_PENDING = INTERRUPT_PENDING | 0x2;
    } else { //Assume any other is a timer interrupt
        uint64_t NewCompare = (((uint64_t)MTIMECMP_HIGH)<<32) | MTIMECMP_LOW;
        NewCompare += 100;
        MTIMECMP_HIGH = NewCompare>>32;
        MTIMECMP_LOW = NewCompare;
        global++;
        controller_status = CONTROLLER;
    }
}

uint32_t c_system_call(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t call){
    switch(call) {
        case 1:
            return global;
        case 2: //clear cmd_interrupt
            cmd_interrupt = 0;
            return 0;
        case 3:
            return cmd_interrupt;
        case 4:
            return load_sprite(*((sprite_t*)arg0));

        case 5:
            return load_sprite_data((SPRITE_TYPE)arg0, (uint8_t*)arg1, (uint8_t)arg2);

        case 6:
            return load_palette((SPRITE_TYPE) arg0, (uint32_t*) arg1, (uint8_t) arg2);

        case 7:
            return display_sprite((uint16_t) arg0, (uint16_t) arg1, (uint16_t) arg2, (uint8_t) arg3);

        case 8:
            return delete_sprite((uint16_t) arg0);

        case 9:
            return change_sprite_palette((uint16_t) arg0, (uint8_t) arg1);

        case 10: //load background palette
            return load_background_palette((uint32_t*)arg0, (uint8_t) arg1);

        case 11: //load background data pixel mode
            return load_background_data_pixel((uint8_t*)arg0, (uint8_t) arg1);

        case 12: //Load background
            return load_background(*((background_t*)arg0));

        case 13:
            return delete_background((uint8_t)arg0);

                /* Threading Syscalls */
        case 14:
            return threadCreate((TThreadEntry) arg0, (void*)arg1);

        case 15:
            return threadYield();

        case 16:
            threadExit();
            return 0;

        case 17:
            return lockAcquire((Lock*)arg0);

        case 18:
            return lockRelease((Lock*)arg0);

        case 19:
            return (uint32_t)lockCreate();
    
        case 20:
            if(controller_status){
                if(controller_status & 0x1){ //left
                    return a;
                }
                if(controller_status & 0x2){ //up
                    return w;
                }
                if(controller_status & 0x4){ //down
                    return x;
                }
                if(controller_status & 0x8){ //right
                    return d;
                }
                if(controller_status & 0x10){ //left
                    return u;
                }
                if(controller_status & 0x20){ //up
                    return i;
                }
                if(controller_status & 0x40){ //down
                    return j;
                }
                if(controller_status & 0x80){ //right
                    return k;
                }
	        }
            return NONE;
        case 30: //malloc sys?
            return malloc((size_t)arg0);
        case 35: //create_square
            return create_square(arg0);
        default:
            return -1;
    }
}
