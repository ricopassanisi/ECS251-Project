#include <stdint.h>
#include <sprite.h>
#include <stdlib.h>
#include <background.h>
#include <threading/threads.h>
#include <controller.h>
#include <util.h>

//fill data of buffer with spaceship data
void load_spaceship_data(uint8_t *med_buffer) {
    /* spaceship_palette[0] = 0x00000000; //transparent black
    spaceship_palette[1] = 0xFF303030; //Dark Grey
    spaceship_palette[2] = 0xFF545454; //Med grey
    spaceship_palette[3] = 0xFF787878; //light grey
    spaceship_palette[4] = 0xFFFF0000; //red
    spaceship_palette[5] = 0xFFFF8400; //orange
    spaceship_palette[6] = 0xFFFFFF00; //yellow
    spaceship_palette[7] = 0xFF00BBFF; //light blue */
    int y_off_permanent = 2*32; //kinda screwed up the pixel drawing so need this
    med_buffer[y_off_permanent + (1*32) + 9] = 6;
    med_buffer[y_off_permanent + (1*32) + 10] = 5;
    med_buffer[y_off_permanent + (1*32) + 11] = 4;
    med_buffer[y_off_permanent + (1*32) + 12] = 1;
    med_buffer[y_off_permanent + (1*32) + 13] = 1;
    med_buffer[y_off_permanent + (1*32) + 14] = 1;
    med_buffer[y_off_permanent + (1*32) + 15] = 1;

    med_buffer[y_off_permanent + (2*32) + 10] = 6;
    med_buffer[y_off_permanent + (2*32) + 11] = 4;
    med_buffer[y_off_permanent + (2*32) + 12] = 2;
    med_buffer[y_off_permanent + (2*32) + 13] = 1;
    med_buffer[y_off_permanent + (2*32) + 14] =1;

    med_buffer[y_off_permanent + (3*32) + 12] = 2;
    med_buffer[y_off_permanent + (3*32) + 12] = 1;

    med_buffer[y_off_permanent + (4*32) + 12] = 2;
    med_buffer[y_off_permanent + (5*32) + 12] = 2;

    for(int y = 6; y <= 9; ++y) {
        med_buffer[y_off_permanent + (y*32) + 12] = 3;
        med_buffer[y_off_permanent + (y*32) + 13] = 2;
    }

    
    med_buffer[y_off_permanent + (10*32) + 8] = 2;
    med_buffer[y_off_permanent + (10*32) + 9] = 2;
    med_buffer[y_off_permanent + (10*32) + 12] = 2; 
    med_buffer[y_off_permanent + (10*32) + 13] = 3; 
    med_buffer[y_off_permanent + (10*32) + 14] = 2; 



}


int main()
{
    int global = GetTicks();
    int last_global = global;
    int glob_init = global;
    
    // Fill out sprite data

    // uint8_t * med_square_data = (uint8_t*) malloc(1024*sizeof(uint8_t));
    uint8_t *med_square_data = (uint8_t *) malloc(1024*sizeof(uint8_t));
    // uint8_t med_square_data[1024];
    uint8_t small_square_data[256];
    uint8_t large_square_data[4096];
    // fill medium
    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 32; x++)
        {
            med_square_data[y * 32 + x] = 1;
            // MEDIUM_DATA[(1024)+(y*32+x)] = 2;
        }
    }

    // fill small
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; ++x)
        {
            if (y < 8)
                small_square_data[y * 16 + x] = 1;
            else
                small_square_data[y * 16 + x] = 2;
        }
    }

    // fill large
    for (int y = 0; y < 64; ++y)
    {
        for (int x = 0; x < 64; ++x)
        {
            large_square_data[y * 64 + x] = 1;
        }
    }

    // create background in pixel mode:
    //uint8_t background_data[512 * 288];
    uint8_t *background_data = (uint8_t*) malloc(512*288*sizeof(uint8_t));
    for (int y = 0; y < 18; ++y)
    {
        for (int x = 0; x < 32; ++x)
        {
            int offset = (((y*512)*16)+((x*16)));
            if(!(x % 2)) {
                //background_data[offset + (2*512) + 1] = 4;
                
            } else {
                
            }

            if(!(y % 2)) {
                
            }
            else {
                //background_data[offset + (3*512) + 6] = 4;
                
            }
            background_data[offset + (6*512) + 13] = 4;
            background_data[offset + (3*512) + 9] = 4;
                //background_data[offset + (9*512) + 3] = 4;
            background_data[offset + (2*512) + 2] = 4;
                //background_data[offset + (10*512) + 8] = 4;
            background_data[offset + (12*512) + 4] = 4;
            
            
            //background_data[y * 512 + x] = 2;
        }
    }

    load_background_data_pixel(background_data, 0);
    background_t back;
    back.type = PIXEL;
    back.data_index = 0;
    back.palette = 0;
    back.x = 0;
    back.y = 0;
    back.z = 0;

    uint8_t back_id = load_background(back);
    load_sprite_data(MEDIUM, med_square_data, 0);
    load_sprite_data(SMALL, small_square_data, 0);
    load_sprite_data(LARGE, large_square_data, 0);
    // Create green triangle
    for (int y = 0; y < 32; ++y)
    {
        for (int x = 0; x < y + 1; ++x)
        {
            // MEDIUM_DATA[(1024)+(y*32+x)] = 2;
        }
    }
    // Create blue triangle
    for (int y = 0; y < 32; ++y)
    {
        for (int x = 31; x >= y; --x)
        {
            // MEDIUM_DATA[(1024*2)+(y*32+x)] = 3;
        }
    }

    uint32_t *sprite_palette = (uint32_t *)malloc(256 * sizeof(uint32_t));
    sprite_palette[1] = 0xFFFF06B5; // A R G B
    sprite_palette[2] = 0xFF00FF00; // Green
    sprite_palette[3] = 0xFF0000FF; // Blue
    sprite_palette[4] = 0xFFFFFFFF; //white

    load_palette(MEDIUM, sprite_palette, 0);
    load_palette(SMALL, sprite_palette, 0);
    load_palette(LARGE, sprite_palette, 0);
    load_background_palette(sprite_palette, 0);

    uint32_t *spaceship_palette = (uint32_t *) malloc(256*sizeof(uint32_t));
    spaceship_palette[0] = 0x00000000; //transparent black
    spaceship_palette[1] = 0xFF303030; //Dark Grey
    spaceship_palette[2] = 0xFF545454; //Med grey
    spaceship_palette[3] = 0xFF787878; //light grey
    spaceship_palette[4] = 0xFFFF0000; //red
    spaceship_palette[5] = 0xFFFF8400; //orange
    spaceship_palette[6] = 0xFFFFFF00; //yellow
    spaceship_palette[7] = 0xFF00BBFF; //light blue

    load_palette(MEDIUM, spaceship_palette, 1);

    uint8_t *spaceship_data = (uint8_t*) malloc(32*32*sizeof(uint8_t));
    load_spaceship_data(spaceship_data);

    load_sprite_data(MEDIUM, spaceship_data, 1);

    sprite_t square;
    square.type = MEDIUM;
    square.data_index = 1;
    square.palette = 1;
    square.x = 0;
    square.y = 0;
    square.z = 0;
    uint16_t id = load_sprite(square);
    square.type = SMALL;
    square.data_index = 0;
    square.palette = 0;
    uint16_t small_id = load_sprite(square);
    square.type = LARGE;
    uint16_t large_id = load_sprite(square);
    uint16_t large_x, large_y;
    large_x = 80;
    large_y = 80;
    display_sprite(small_id, 200, 50, 1);
    display_sprite(large_id, large_x, large_y, 0);



    int8_t plusMinus = 1;
    Button controller_status = get_controller();
    uint16_t square_ids[10];
    for(int i = 0; i < 10; ++i) {
        square_ids[i] = create_square(0xFF0000FF);
        display_sprite(square_ids[i], (34*i),70,1);
    }
    
    int x_pos = 0;
    int last_x_pos = x_pos;
    display_sprite(small_id, 200, 50, 1);
    free(spaceship_palette);
    free(background_data);
    while (1) {
        threadYield();
        // int c = a + b + global;
        global = GetTicks();
        uint32_t cmd = GetCmd();
        if (global != last_global) {
            controller_status = get_controller();
            
            switch (controller_status) {
            case w:
                if (x_pos >= 0x40) {
                    x_pos -= 0x40;
                }
                break;
            case a:
                if (x_pos & 0x3F){
                    x_pos--;
                }
                break;
            case x:
                if (x_pos < 0x8C0){
                    x_pos += 0x40;
                }
                break;
            case d:
                if ((x_pos & 0x3F) != 0x3F){
                    x_pos++;
                }
                break;
            case i:
                free(med_square_data);
                break;
            default:
                break;
            }
            if(x_pos != last_x_pos) {
                last_x_pos = x_pos;
                display_sprite(id, (x_pos & 0x3F) << 3, (x_pos >> 6) << 3, 0);
            }
        }
        if (cmd) { // reset position if cmd pressed
            clear_cmd();
            delete_sprite(id);
            delete_background(back_id);
        }
        if (large_x >= 448) plusMinus = -1;
        if (large_x <= 0) plusMinus = 1;
        last_global = global;
        if (glob_init + 5 <= last_global) {
            glob_init = last_global;
            large_x += plusMinus;
            display_sprite(large_id, large_x, large_y, 0);
        }
    }
    return 0;
}

