#include <background.h>

// (uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index)
// return (((uint32_t)index)<<24) | (((uint32_t)z)<<21) | (((uint32_t)y+16)<<12) | (((uint32_t)x+16)<<2) | (palette & 0x3);
uint32_t BackgroundControl_Pixel(uint8_t palette, uint8_t z, uint16_t y, uint16_t x, uint8_t index) {
    return   (((uint32_t)index)<<29) | (((uint32_t)z)<<22) | ((((uint32_t)y+288))<<12) | ((((uint32_t)x+512))<<2) | (palette & 0x3);
}

int8_t load_background_palette(uint32_t* palette, uint8_t index) {
    int numColors = 256;
    if(index > 3 || index < 0) return -1; //out of bounds

    for(int i = 0; i < numColors; ++i) {
        BACKGROUND_PALETTE[(numColors*index) + i] = palette[i];
    }
    return 0;
}

int8_t load_background_data_pixel(uint8_t* data, uint8_t index) {
    if(index > 3 || index < 0) return -1; //out of bounds for pixel mode
    int numBytes = 147456; //number of bytes per data section in pixel mode
    for(int i = 0; i < numBytes; ++i) {
        BACKGROUND_DATA[(index*numBytes) + i] = data[i];
    }
    return 0;
}

int8_t load_background_data_tile(uint8_t* data, uint8_t index) {
    return -1; //TODO unimplemented function
}

uint8_t load_background(background_t background) {
    for(int i = 0; i < 64; ++i) {
        if(!BACKGROUND_CONTROLS[i]) { //unfilled section
            if(background.type == PIXEL) {
                BACKGROUND_CONTROLS[i] = BackgroundControl_Pixel(background.palette, background.z, background.y, background.x, background.data_index);
                return i;
            } else {
                return -1; //unimplemented
                //?
            }
        }
    }
    return -1; //no unfilled section
}

uint8_t delete_background(uint8_t background_id) {
    uint8_t index = background_id & 0x3F;
    BACKGROUND_CONTROLS[index] = 0;
    return 0;
}