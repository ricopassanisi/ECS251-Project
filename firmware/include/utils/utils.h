/**
 * @file utils.h
 * 
 * Various helper functions
*/

#pragma once

#include <stdint.h>

extern uint32_t cartridgeGP;

/* Sets Firmware Global Pointer*/
void _setGP(void);

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


