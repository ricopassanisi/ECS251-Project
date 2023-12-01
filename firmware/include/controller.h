#pragma once
#include <stdint.h>

//volatile uint32_t controller_status=0;
typedef enum Button {
    w,
    a,
    x,
    d,
    u,
    i,
    j,
    k,
    NONE
} Button;
uint32_t get_controller_status(volatile uint32_t controller_status);
