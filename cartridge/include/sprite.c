#include <sprite.h>

//Need some kind of storage for sprite IDs, like a map between sprite ids and memory locations




//integer IDs for the keys map to the control memory address they relate to

// 0 - 255: Small sprites
// 256 - 511: Medium Sprites
// 512 - 767: Large sprites
//Sprite ID description
/*bit | 31 .. 24 | 25 .. 24 | 23 .. 16 | 15 .. 8 | 7 .. 0    |
* ------------------------------------------------------------
*Desc | Reserved |  control | Large ID | Med ID  | Small ID  |
*/

/* bit | 16 .. 10 | 9 .. 2 | 1 .. 0 |
* -----------------------------------
* Desc | Reserved | ID val | control |
*/

uint8_t small_sprites[256];
uint8_t medium_sprites[256];
uint8_t large_sprites[256];

//Have load sprite data, load pallette (which both include the type of sprite), then 



uint32_t SmallControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index) {
    return (((uint32_t)index)<<24) | (((uint32_t)z)<<21) | (((uint32_t)y+16)<<12) | (((uint32_t)x+16)<<2) | (palette & 0x3);
}

uint32_t MediumControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index) {
    return (((uint32_t)index)<<24) | (((uint32_t)z)<<21) | (((uint32_t)y+32)<<12) | (((uint32_t)x+32)<<2) | (palette & 0x3);
}

uint32_t LargeControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index) {
    return (((uint32_t)index)<<24) | (((uint32_t)z)<<21) | (((uint32_t)y+64)<<12) | (((uint32_t)x+64)<<2) | (palette & 0x3);
}

int16_t display_sprite(uint16_t sprite_id, uint16_t x_off, uint16_t y_off, uint8_t z_off) {
    switch(sprite_id & 0b11) {
        case 0b00: //small
            SMALL_CONTROL[(sprite_id >> 2)] = ((uint32_t)(SMALL_CONTROL[(sprite_id >> 2)] & 0xFF000003)) | (((uint32_t)z_off)<<21) | (((uint32_t)y_off+16)<<12) | (((uint32_t)x_off+16)<<2);
            break;
        case 0b01: //med
            MEDIUM_CONTROL[(sprite_id >> 2)] = ((uint32_t)(MEDIUM_CONTROL[(sprite_id >> 2)] & 0xFF000003)) | (((uint32_t)z_off)<<21) | (((uint32_t)y_off+32)<<12) | (((uint32_t)x_off+32)<<2);
            break;
        case 0b10: //large
            LARGE_CONTROL[(sprite_id >> 2)] = ((uint32_t)(LARGE_CONTROL[(sprite_id >> 2)] & 0xFF000003)) | (((uint32_t)z_off)<<21) | (((uint32_t)y_off+32)<<12) | (((uint32_t)x_off+32)<<2);
            break;
        default:
            return -1; //something went very wrong
    }
    return 0;
}

int delete_sprite(int16_t sprite_id) {
    switch(sprite_id & 0b11) {
        case 0b00: //small
            SMALL_CONTROL[(sprite_id >> 2)] = 0;
            break;
        case 0b01: //med
            MEDIUM_CONTROL[(sprite_id >> 2)] = 0;
            break;
        case 0b10: //large
            LARGE_CONTROL[(sprite_id >> 2)] = 0;
            break;
        default:
            return -1; //something went very wrong
    }
    return 0;
}

int change_sprite_palette(int16_t sprite_id, uint8_t palette_index) {
    switch(sprite_id & 0b11) {
        case 0b00: //small
            SMALL_CONTROL[(sprite_id >> 2)] = 0;
            break;
        case 0b01: //med
            MEDIUM_CONTROL[(sprite_id >> 2)] = 0;
            break;
        case 0b10: //large
            LARGE_CONTROL[(sprite_id >> 2)] = 0;
            break;
        default:
            return -1; //something went very wrong
    }
}

int8_t load_sprite_data(SPRITE_TYPE type, uint8_t * data, uint8_t index) {
    uint8_t * data_loc;
    uint16_t data_size;
    switch(type) {
        case SMALL:
            data_size = 256;
            for(int i = 0; i < data_size; ++i) {
                SMALL_DATA[(data_size*index)+i] = data[i];
            }
            break;
        case MEDIUM:
            data_size = 1024;
            if(index > 63) return -1; //Cannot go out of med size data section
            for(int i = 0; i < data_size; ++i) {
                MEDIUM_DATA[(data_size*index)+i] = data[i];
            }
            break;
        case LARGE:
            data_size = 4096;
            if(index > 63) return -1; //Cannot go out of large size data section
            for(int i = 0; i < data_size; ++i) {
                LARGE_DATA[(data_size*index)+i] = data[i];
            }
            break;
        default:
            return -1; //something went very wrong
    }
    //Copy over data into video memory
    
    return 0;
}

int8_t load_palette(SPRITE_TYPE type, uint32_t * palette, uint8_t index) {
    
    switch(type) {
        case SMALL:
            break;
        case MEDIUM:
            break;
        case LARGE:
            break;
    }
}


uint16_t load_sprite(sprite_t sprite) {
    uint8_t sprite_id = 0;
    switch(sprite.type) {
        case SMALL:
            for(int i = 0; i < 256; ++i) {
                if(!SMALL_CONTROL[i]) { //unfilled section
                    SMALL_CONTROL[i] = SmallControl(sprite.palette, sprite.x, sprite.y, sprite.z, sprite.data_index);
                    return (i << 2);
                }
            }
            break;
        case MEDIUM:
            for(int i = 0; i < 256; ++i) {
                if(!MEDIUM_CONTROL[i]) { //unfilled
                    MEDIUM_CONTROL[i] = MediumControl(sprite.palette, sprite.x, sprite.y, sprite.z, sprite.data_index);
                    return (i << 2) | 1;
                }
            }
            break;
        case LARGE:
            for(int i = 0; i < 256; ++i) {
                if(!LARGE_CONTROL[i]) { //unfilled
                    LARGE_CONTROL[i] = LargeControl(sprite.palette, sprite.x, sprite.y, sprite.z, sprite.data_index);
                    return (i << 2) | 2;
                }
            }
            break;
    }
    return -1;
}