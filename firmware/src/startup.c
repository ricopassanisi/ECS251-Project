#include <stdint.h>
#include <utils/utils.h>
#include <threading/threads.h>
#include <threading/locks.h>

extern uint8_t _erodata[];
extern uint8_t _data[];
extern uint8_t _edata[];
extern uint8_t _sdata[];
extern uint8_t _esdata[];
extern uint8_t _bss[];
extern uint8_t _ebss[];


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
extern volatile uint32_t *MEDIUM_PALETTE;

void c_interrupt_handler(uint32_t cause){
    csr_disable_interrupts();
    
    uint64_t NewCompare = (((uint64_t)MTIMECMP_HIGH)<<32) | MTIMECMP_LOW;
    NewCompare += 100;
    MTIMECMP_HIGH = NewCompare>>32;
    MTIMECMP_LOW = NewCompare;
    global++;
    controller_status = CONTROLLER;

    int num2 = 0x123;
    int num3 = 123;
    int number = INTERRUPT_PENDING;

    if((INTERRUPT_PENDING) & 0x4) { //Cmd interrupt?
        cmd_interrupt++;
        INTERRUPT_PENDING = INTERRUPT_PENDING | 0x4;

    } else if((INTERRUPT_PENDING) & 0x2) { //Video interrupt?
        if(global % 60 == 0) { //swap colors every 60 frames
            MEDIUM_PALETTE[1] = MEDIUM_PALETTE[1] ^ 0x06B5; 
        }
        INTERRUPT_PENDING = INTERRUPT_PENDING | 0x2;
    } else if((INTERRUPT_PENDING) & 0xb) {
        //threadYield();
        INTERRUPT_PENDING = INTERRUPT_PENDING & 0xb;
    }

    csr_enable_interrupts();
}

uint32_t cartridgeGP = 0;

uint32_t c_system_call(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t call){


    switch (call)
    {
    case 0:
        cartridgeGP = arg0;
        return 0x0;
    case 1:
        return global;

    case 2:
        return controller_status;

    case 3:
        return cmd_interrupt;

        /* Threading Syscalls */
    case 10:
        return threadCreate((TThreadEntry) arg0, (void*)arg1);

    case 11:
        return threadYield(arg0);

    case 12:
        threadExit();
        return 0;

    case 13:
        return lockAcquire((Lock*)arg0);

    case 14:
        return lockRelease((Lock*)arg0);

    case 15:
        return (uint32_t)lockCreate();
    
    default:
        break;
    }



    return -1;

}