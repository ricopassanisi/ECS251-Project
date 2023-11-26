#include <stdint.h>






uint32_t get_controller_sys();



int8_t get_controller() {
    return get_controller_sys();
}

