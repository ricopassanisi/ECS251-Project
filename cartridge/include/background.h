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

//SYSCALL WRAPPER FUNCTIONS:

/** @brief load background palette
 * 
 * @param palette The palette data buffer of 256 values to load into the palette
 * 
 * @param index the index to load the palette into
 * 
 * @return 0 upon success, -1 upon failure.
*/
int8_t load_background_palette(uint32_t* palette, uint8_t index) {
    return load_background_palette_sys((uint32_t) palette, (uint32_t) index);
}

/** @brief Loads background data buffer in pixel mode
 * 
 * @param data the data buffer of pixel values to load in (assumes a full buffer)
 * 
 * @param index the index to load the data into
 * 
 * @return 0 upon success, -1 upon failure.
*/
int8_t load_background_data_pixel(uint8_t* data, uint8_t index) {
    return load_background_data_pixel_sys((uint32_t) data, (uint32_t) index);
}

/** @brief change sprite palette - changes the palette for the given sprite ID
 * 
 * @param sprite_id the sprite for which to change the palette
 * 
 * @param palette_index the new palette index for the sprite
 * 
 * @return 0 upon success, -1 upon failure.
*/
int8_t load_background_data_tile(uint32_t* data, uint8_t index);

/** @brief change sprite palette - changes the palette for the given sprite ID
 * 
 * @param sprite_id the sprite for which to change the palette
 * 
 * @param palette_index the new palette index for the sprite
 * 
 * @return 0 upon success, -1 upon failure.
*/
uint8_t load_background(background_t background) {
    return load_background_sys((uint32_t)&background);
}

/** @brief change sprite palette - changes the palette for the given sprite ID
 * 
 * @param sprite_id the sprite for which to change the palette
 * 
 * @param palette_index the new palette index for the sprite
 * 
 * @return 0 upon success, -1 upon failure.
*/
uint8_t delete_background(uint8_t background_id) {
    return delete_background_sys((uint32_t)background_id);
}
