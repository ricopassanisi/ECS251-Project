#include <stdint.h>






uint32_t get_controller_sys();



uint32_t get_controller() {
    return get_controller_sys();
}

