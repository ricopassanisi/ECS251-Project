/*
* 
*/
#include <stdint.h>

typedef enum SPRITE_TYPE {
    SMALL,
    MEDIUM,
    LARGE
} SPRITE_TYPE;

/*
  Sprite_t data structure, basically simulates
  the control structure of a sprite
*/
typedef struct sprite_t {
    SPRITE_TYPE type;
    int16_t x, y, z;
    uint8_t palette, data_index;
} sprite_t;

//syscall setup:
uint32_t load_sprite_sys(uint32_t sprite_ptr);
uint32_t load_sprite_data_sys(uint32_t type, uint32_t data_ptr, uint32_t index);
uint32_t load_palette_sys(uint32_t type, uint32_t palette_ptr, uint32_t index);
uint32_t display_sprite_sys(uint32_t sprite_id, uint32_t x_off, uint32_t y_off, uint32_t z_off);
uint32_t delete_sprite_sys(uint32_t sprite_id);
uint32_t change_sprite_palette_sys(uint32_t sprite_id, uint32_t palette_index);
//functions:

//Wrappers for system calls
uint16_t load_sprite(sprite_t sprite) {
  return load_sprite_sys((uint32_t) &sprite);
}

int8_t load_sprite_data(SPRITE_TYPE type, uint8_t * data, uint8_t index) {
  return load_sprite_data_sys((uint32_t)type, (uint32_t)data, (uint32_t)index);
}

int8_t load_palette(SPRITE_TYPE type, uint32_t * palette, uint8_t index) {
  return load_palette_sys((uint32_t)type, (uint32_t) palette, (uint32_t) index);
}

int16_t display_sprite(uint16_t sprite_id, uint16_t x_off, uint16_t y_off, uint8_t z_off) {
  return display_sprite_sys((uint32_t) sprite_id, (uint32_t) x_off, (uint32_t) y_off, (uint32_t) z_off);
}

int delete_sprite(int16_t sprite_id) {
  return delete_sprite_sys((uint32_t)sprite_id);
}

int change_sprite_palette(int16_t sprite_id, uint8_t palette_index) {
  return change_sprite_palette_sys((uint32_t) sprite_id, (uint32_t) palette_index);
}

