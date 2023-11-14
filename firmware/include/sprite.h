/*
* 
*/
#include <stdint.h>
typedef struct sprite_t {
    SPRITE_TYPE type;
    uint8_t *data;
    palette *palette;
    //uint32_t *control;
};

typedef enum SPRITE_TYPE {
    SMALL,
    MEDIUM,
    LARGE
};

typedef uint32_t* palette;

//functions:
//sprite_t create_sprite(...) //fill this out with everything needed to make a sprite
int16_t load_sprite(sprite_t sprite);
int16_t display_sprite(int16_t sprite_id, uint8_t x_off, uint8_t y_off, uint8_t z_off);
int delete_sprite(int16_t sprite_id);
int change_sprite_palette(int16_t sprite_id, palette * palette);