#include <stdint.h>


typedef enum BACKGROUND_TYPE {
    PIXEL,
    TILE
} BACKGROUND_TYPE;

typedef struct background_t {
    BACKGROUND_TYPE type;
    int16_t x, y, z;
    uint8_t palette, data_index;
} background_t;


uint32_t load_background_palette_sys(uint32_t data_ptr, uint32_t index);
uint32_t load_background_data_pixel_sys(uint32_t data_ptr, uint32_t index);
uint32_t load_background_sys(uint32_t background_ptr);
uint32_t delete_background_sys(uint32_t background_id);


int8_t load_background_palette(uint32_t* data, uint8_t index) {
    return load_background_palette_sys((uint32_t) data, (uint32_t) index);
}

int8_t load_background_data_pixel(uint8_t* data, uint8_t index) {
    return load_background_data_pixel_sys((uint32_t) data, (uint32_t) index);
}

int8_t load_background_data_tile(uint32_t* data, uint8_t index);

uint8_t load_background(background_t background) {
    return load_background_sys((uint32_t)&background);
}

uint8_t delete_background(uint8_t background_id) {
    return delete_background_sys((uint32_t)background_id);
}
