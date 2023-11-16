/*
* 
*/
#include <stdint.h>

volatile uint8_t *SMALL_DATA = (volatile uint8_t *)(0x500E0000);
volatile uint32_t *SMALL_PALETTE = (volatile uint32_t *)(0x500F3000);
volatile uint32_t *SMALL_CONTROL = (volatile uint32_t *)(0x500F6300);

volatile uint8_t *MEDIUM_DATA = (volatile uint8_t *)(0x500D0000);
volatile uint32_t *MEDIUM_PALETTE = (volatile uint32_t *)(0x500F2000);
volatile uint32_t *MEDIUM_CONTROL = (volatile uint32_t *)(0x500F5F00);

volatile uint8_t *LARGE_DATA = (volatile uint8_t *)(0x50090000);
volatile uint32_t *LARGE_PALETTE = (volatile uint32_t *)(0x500F1000);
volatile uint32_t *LARGE_CONTROL = (volatile uint32_t *)(0x500F5B00);

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


//functions:
//sprite_t create_sprite(...) //fill this out with everything needed to make a sprite
uint16_t load_sprite(sprite_t sprite);
int8_t load_sprite_data(SPRITE_TYPE type, uint8_t * data, uint8_t index);
int8_t load_palette(SPRITE_TYPE type, uint32_t * palette, uint8_t index);
int16_t display_sprite(uint16_t sprite_id, uint16_t x_off, uint16_t y_off, uint8_t z_off);
int delete_sprite(int16_t sprite_id);
int change_sprite_palette(int16_t sprite_id, uint8_t palette_index);
