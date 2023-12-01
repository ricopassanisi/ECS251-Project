#include <stdint.h>



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

uint32_t get_controller_sys();



Button get_controller() {
    return (Button) get_controller_sys();
}

