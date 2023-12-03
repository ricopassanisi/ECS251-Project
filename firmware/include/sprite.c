#include <sprite.h>
#include <core/video.h>
//Sprite ID description
/* bit | 16 .. 10 | 9 .. 2 | 1 .. 0 |
* -----------------------------------
* Desc | Reserved | ID val | control |
*/

// The lowest 2 bits are used to determine the type of the sprite (small, medium, or large)
// The next 8 bits represent the index of the sprite

/*
* Control helper functions, creates the correct control structure from the given values
* For the specified type.
*/
uint32_t SmallControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index) {
    return (((uint32_t)index)<<24) | (((uint32_t)z)<<21) | (((uint32_t)y+16)<<12) | (((uint32_t)x+16)<<2) | (palette & 0x3);
}

uint32_t MediumControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index) {
    return (((uint32_t)index)<<24) | (((uint32_t)z)<<21) | (((uint32_t)y+32)<<12) | (((uint32_t)x+32)<<2) | (palette & 0x3);
}

uint32_t LargeControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index) {
    return (((uint32_t)index)<<24) | (((uint32_t)z)<<21) | (((uint32_t)y+64)<<12) | (((uint32_t)x+64)<<2) | (palette & 0x3);
}

/*
* Displays the given Sprite ID at the given coordinates. 
* Uses a similar method as the control functions but keeps the original index and palette values
*/
int16_t display_sprite(uint16_t sprite_id, uint16_t x_off, uint16_t y_off, uint8_t z_off) {
    video_buf buffer;
    buffer.num_bytes = 0;
    buffer.num_words = 1;
    uint32_t *val = malloc(sizeof(uint32_t));
    //uint32_t val[1];
    switch(sprite_id & 0b11) {
        case 0b00: //small
            if(!SMALL_CONTROL[(sprite_id >> 2)]) return -1; //Sprite id does not exist
            val[0] = ((uint32_t)(SMALL_CONTROL[(sprite_id >> 2)] & 0xFF000003)) | (((uint32_t)z_off)<<21) | (((uint32_t)y_off+16)<<12) | (((uint32_t)x_off+16)<<2);
            buffer.video_mem32 =  (SMALL_CONTROL + (sprite_id >> 2));
            //SMALL_CONTROL[(sprite_id >> 2)] = ((uint32_t)(SMALL_CONTROL[(sprite_id >> 2)] & 0xFF000003)) | (((uint32_t)z_off)<<21) | (((uint32_t)y_off+16)<<12) | (((uint32_t)x_off+16)<<2);
            break;
        case 0b01: //med
            if(!MEDIUM_CONTROL[(sprite_id >> 2)]) return -1; //Sprite id does not exist
            val[0] = ((uint32_t)(MEDIUM_CONTROL[(sprite_id >> 2)] & 0xFF000003)) | (((uint32_t)z_off)<<21) | (((uint32_t)y_off+32)<<12) | (((uint32_t)x_off+32)<<2);
            buffer.video_mem32 =  (MEDIUM_CONTROL + (sprite_id >> 2));
            //MEDIUM_CONTROL[(sprite_id >> 2)] = ((uint32_t)(MEDIUM_CONTROL[(sprite_id >> 2)] & 0xFF000003)) | (((uint32_t)z_off)<<21) | (((uint32_t)y_off+32)<<12) | (((uint32_t)x_off+32)<<2);
            break;
        case 0b10: //large
            if(!LARGE_CONTROL[(sprite_id >> 2)]) return -1; //Sprite id does not exist
            val[0] = ((uint32_t)(LARGE_CONTROL[(sprite_id >> 2)] & 0xFF000003)) | (((uint32_t)z_off)<<21) | (((uint32_t)y_off+64)<<12) | (((uint32_t)x_off+64)<<2);
            buffer.video_mem32 =  (LARGE_CONTROL + (sprite_id >> 2));
            //LARGE_CONTROL[(sprite_id >> 2)] = ((uint32_t)(LARGE_CONTROL[(sprite_id >> 2)] & 0xFF000003)) | (((uint32_t)z_off)<<21) | (((uint32_t)y_off+64)<<12) | (((uint32_t)x_off+64)<<2);
            break;
        default:
            return -1; //something went very wrong
    }
    buffer.words = val;
    add_to_video_queue(buffer);
    return 0;
}

/*
* Deletes the control memory of the given sprite id.
*/
int delete_sprite(int16_t sprite_id) {
    int index = sprite_id >> 2;
    video_buf buffer;
    buffer.num_bytes = 0;
    buffer.num_words = 1;
    uint32_t *val = malloc(sizeof(uint32_t)); //yes this causes a memory leak, idk how to fix it yet
    val[0] = 0;
    buffer.words = val;
    switch(sprite_id & 0b11) {
        case 0b00: //small
            buffer.video_mem32 = SMALL_CONTROL + index;
            //SMALL_CONTROL[index] = 0;
            break;
        case 0b01: //med
            buffer.video_mem32 = MEDIUM_CONTROL + index;
            //MEDIUM_CONTROL[index] = 0;
            break;
        case 0b10: //large
            buffer.video_mem32 = LARGE_CONTROL + index;
            //LARGE_CONTROL[index] = 0;
            break;
        default:
            return -1; //something went very wrong
    }
    add_to_video_queue(buffer);
    return 0;
}

/*
* Changes the given sprite's palette.
*/
int change_sprite_palette(int16_t sprite_id, uint8_t palette_index) {
    int index = sprite_id >> 2;
    switch(sprite_id & 0b11) {
        case 0b00: //small
            if(!SMALL_CONTROL[(sprite_id >> 2)]) return -1; //Sprite id does not exist
            SMALL_CONTROL[index] = (SMALL_CONTROL[index] & 0b00) | (palette_index & 0b11);
            break;
        case 0b01: //med
            if(!MEDIUM_CONTROL[(sprite_id >> 2)]) return -1; //Sprite id does not exist
            MEDIUM_CONTROL[index] = (MEDIUM_CONTROL[index] & 0b00) | (palette_index & 0b11);
            break;
        case 0b10: //large
            if(!LARGE_CONTROL[(sprite_id >> 2)]) return -1; //Sprite id does not exist
            LARGE_CONTROL[index] = (LARGE_CONTROL[index] & 0b00) | (palette_index & 0b11);
            break;
        default:
            return -1; //something went very wrong
    }
}

/*
* Loads the data in the given buffer to the specified index (from type and index)
*/
int8_t load_sprite_data(SPRITE_TYPE type, uint8_t * data, uint8_t index) {
    uint16_t data_size;
    video_buf buffer;
    buffer.num_words = 0;
    buffer.words = NULL;
    switch(type) {
        case SMALL:
            data_size = 256;
            buffer.num_bytes = data_size;
            buffer.bytes = data;
            buffer.video_mem8 = SMALL_DATA + (data_size*index);
            /*for(int i = 0; i < data_size; ++i) {
                SMALL_DATA[(data_size*index)+i] = data[i];
            } */
            break;
        case MEDIUM:
            data_size = 1024;
            if(index > 63) return -1; //Cannot go out of med size data section
            buffer.num_bytes = data_size;
            buffer.bytes = data;
            buffer.video_mem8 = MEDIUM_DATA + (data_size*index);
            //for(int i = 0; i < data_size; ++i) {
            //    MEDIUM_DATA[(data_size*index)+i] = data[i];
            //}
            break;
        case LARGE:
            data_size = 4096;
            if(index > 63) return -1; //Cannot go out of large size data section
            buffer.num_bytes = data_size;
            buffer.bytes = data;
            buffer.video_mem8 = LARGE_DATA + (data_size*index);
            //for(int i = 0; i < data_size; ++i) {
            //    LARGE_DATA[(data_size*index)+i] = data[i];
            //}
            break;
        default:
            return -1; //something went very wrong
    }

    add_to_video_queue(buffer);
    return 0;
}

/*
* Loads the given palette into the given index.
*/
int8_t load_palette(SPRITE_TYPE type, uint32_t * palette, uint8_t index) {
    int numColors = 256;
    video_buf buffer;
    buffer.num_bytes = 0;
    buffer.bytes = NULL;
    buffer.num_words = numColors;
    buffer.words = palette;
    switch(type) {
        //copy palette data from palette into specified palette.
        case SMALL:
            buffer.video_mem32 = SMALL_PALETTE + (numColors*index);
            /*for(int i = 0; i < numColors; ++i) {
                SMALL_PALETTE[(numColors*index) + i] = palette[i];
            }*/
            break;
        case MEDIUM:
            buffer.video_mem32 = MEDIUM_PALETTE + (numColors*index);
            //for(int i = 0; i < numColors; ++i) {
            //    MEDIUM_PALETTE[(numColors*index) + i] = palette[i];
            //}
            break;
        case LARGE:
            buffer.video_mem32 = LARGE_PALETTE + (numColors*index);
            //for(int i = 0; i < numColors; ++i) {
             //   LARGE_PALETTE[(numColors*index) + i] = palette[i];
            //}
            break;
        default:
            return -1; //something went very wrong
    }
    add_to_video_queue(buffer);
    return 0;
}

/*
* Loads the given sprite into memory and returns the sprite id value related to it.
*/
uint16_t load_sprite(sprite_t sprite) {
    uint8_t sprite_id = 0;
    video_buf buffer;
    uint32_t ctrl;
    buffer.num_bytes = 0;
    buffer.num_words = 1;
    uint32_t *val = malloc(sizeof(uint32_t));
    buffer.bytes = NULL;
    switch(sprite.type) {
        //Find an unfilled section in the control and load it using the control helper functions
        case SMALL:
            for(int i = 0; i < 256; ++i) {
                if(!SMALL_CONTROL[i]) { //unfilled section
                    val[0] = SmallControl(sprite.palette, sprite.x, sprite.y, sprite.z, sprite.data_index);
                    buffer.words = val;
                    buffer.video_mem32 = SMALL_CONTROL + i;
                    add_to_video_queue(buffer);
                    //SMALL_CONTROL[i] = SmallControl(sprite.palette, sprite.x, sprite.y, sprite.z, sprite.data_index);
                    return (i << 2);
                }
            }
            break;
        case MEDIUM:
            for(int i = 0; i < 256; ++i) {
                if(!MEDIUM_CONTROL[i]) { //unfilled
                    val[0] = MediumControl(sprite.palette, sprite.x, sprite.y, sprite.z, sprite.data_index);
                    buffer.words = val;
                    buffer.video_mem32 = MEDIUM_CONTROL + i;
                    add_to_video_queue(buffer);
                    //MEDIUM_CONTROL[i] = MediumControl(sprite.palette, sprite.x, sprite.y, sprite.z, sprite.data_index);
                    return (i << 2) | 1;
                }
            }
            break;
        case LARGE:
            for(int i = 0; i < 256; ++i) {
                if(!LARGE_CONTROL[i]) { //unfilled
                    val[0] = LargeControl(sprite.palette, sprite.x, sprite.y, sprite.z, sprite.data_index);
                    buffer.words = val;
                    buffer.video_mem32 = LARGE_CONTROL + i;
                    add_to_video_queue(buffer);
                    //LARGE_CONTROL[i] = LargeControl(sprite.palette, sprite.x, sprite.y, sprite.z, sprite.data_index);
                    return (i << 2) | 2;
                }
            }
            break;
        default:
            return -1; //Something went wrong
    }
    return -1; //Out of space in the given control
}


//RESERVED SPRITE STUFF:
// Medium Sprite data 54-63 (10 data sections)
// Medium Sprite Controls 225-255 (30 control structures)

//Last medium palette reserved for colors, any new color gets filled into most recent open spot
//Create medium square of given color (base easy to use function), returns the sprite ID

uint16_t create_square(uint32_t color) {
    volatile uint32_t * palette = (volatile uint32_t *) 0x500F2C00;
    //PALETTE
    //determine place to put new color
    //loop over palette:
    int color_index;
    for(int i = 1; i < 256; ++i) {
        if(palette[i] == color) {
            color_index = i;
            break;
        }
        if(!palette[i]) { //empty palette space
            color_index = i;
            palette[i] = color;
        }
    }

    //DATA
    int data_size = 1024;
    int data_index;
    for(int i = 54; i < 64; ++i) {
        if(!MEDIUM_DATA[(data_size*i)]) { //empty medium data
            for(int j = 0; j < data_size; ++j) {
                data_index = i;
                MEDIUM_DATA[(data_size*i) + j] = color_index;
            }
            break;
        }
    }

    //CONTROL
    for(int i = 225; i < 256; ++i) {
        if(!MEDIUM_CONTROL[i]) { //empty control structure
            MEDIUM_CONTROL[i] = MediumControl(3,0,0,0,data_index);
            return (i << 2) | 1;
        }
    }
}