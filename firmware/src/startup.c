#include <stdint.h>
#include <sprite.c>

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
extern volatile uint32_t *MEDIUM_PALETTE;

void c_interrupt_handler(uint32_t cause){
    uint64_t NewCompare = (((uint64_t)MTIMECMP_HIGH)<<32) | MTIMECMP_LOW;
    NewCompare += 100;
    MTIMECMP_HIGH = NewCompare>>32;
    MTIMECMP_LOW = NewCompare;
    global++;
    controller_status = CONTROLLER;
    if((INTERRUPT_PENDING) & 0x4) { //Cmd interrupt?
        cmd_interrupt++;
        INTERRUPT_PENDING = INTERRUPT_PENDING | 0x4;
    } else if((INTERRUPT_PENDING) & 0x2) { //Video interrupt?
        if(global % 60 == 0) { //swap colors every 60 frames
            MEDIUM_PALETTE[1] = MEDIUM_PALETTE[1] ^ 0x06B5; 
        }
        INTERRUPT_PENDING = INTERRUPT_PENDING | 0x2;
    }
}

uint32_t c_system_call(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t call){
    if(1 == call){
        return global;
    }
    else if(2 == call){
        return controller_status;
    }
    else if(3 == call) {
        return cmd_interrupt;
    }
    else if(4 == call) {
        //load_sprite_sys
        sprite_t *sprite = (sprite_t*) arg0;
        int16_t retVal = load_sprite(*sprite);
        return retVal;
    }
    else if(5 == call) {
        //load_sprite_data_sys
        SPRITE_TYPE type = (SPRITE_TYPE) arg0;
        uint8_t * data = (uint8_t*) arg1;
        uint8_t index = (uint8_t) arg2;
        return load_sprite_data(type, data, index);
    }
    else if(6 == call) {
        //load_sprite_palette_sys
        SPRITE_TYPE type = (SPRITE_TYPE) arg0;
        uint32_t * palette = (uint32_t*) arg1;
        uint8_t index = (uint8_t) arg2;
        return load_palette(type, palette, index);
    }
    else if(7 == call) {
        //display_sprite_sys
        //display_sprite(uint16_t sprite_id, uint16_t x_off, uint16_t y_off, uint8_t z_off)
        uint16_t sprite_id = (uint16_t) arg0;
        uint16_t x_off = (uint16_t) arg1;
        uint16_t y_off = (uint16_t) arg2;
        uint8_t z_off = (uint8_t) arg3;
        return display_sprite(sprite_id, x_off, y_off, z_off);
    }
    else if(8 == call) {
        //delete_sprite_sys
        uint16_t sprite_id = (uint16_t) arg0;
        return delete_sprite(sprite_id);
    }
    else if(9 == call) {
        //change_sprite_palette
        uint16_t sprite_id = (uint16_t) arg0;
        uint8_t palette_index = (uint8_t) arg1;
        return change_sprite_palette(sprite_id, palette_index);
    }
    return -1;

}
