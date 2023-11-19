#include <stdint.h>

volatile uint8_t* BACKGROUND_DATA = (volatile uint8_t*) 0x50000000;
volatile uint32_t* BACKGROUND_CONTROLS = (volatile uint32_t*) 0x500F5A00;
volatile uint32_t* BACKGROUND_PALETTE = (volatile uint32_t*) 0x500F0000;

//BACKGROUND ID:
/* 7   |  6       | 5 .. 0  
* type | Reserved | index
*/
// Most significant bit defines the type (0 = pixel, 1 = tile)

typedef enum BACKGROUND_TYPE {
    PIXEL,
    TILE
} BACKGROUND_TYPE;

typedef struct background_t {
    BACKGROUND_TYPE type;
    int16_t x, y, z;
    uint8_t palette, data_index;
} background_t;


int8_t load_background_palette(uint32_t* data, uint8_t index);
int8_t load_background_data_pixel(uint8_t* data, uint8_t index);
int8_t load_background_data_tile(uint8_t* data, uint8_t index);
uint8_t load_background(background_t background);
uint8_t delete_background(uint8_t background_id);
