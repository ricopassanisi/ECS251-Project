#include <stdint.h>
#include <sprite.h>
#include <stdlib.h>
#include <background.h>
#include <threading/threads.h>
#include <controller.h>
#include <mem.h>

volatile uint32_t controller_status = 0;

// Video memory and medium sprite stuff:
// volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
volatile uint32_t *MODE_REGISTER = (volatile uint32_t *)(0x500F6780);

// Syscall setup
uint32_t GetTicks(void);
uint32_t GetCmd(void);


int main()
{
    *MODE_REGISTER = 1;
    int global = GetTicks();
    int last_global = global;
    int glob_init = global;
    
    uint32_t lastCmd = GetCmd();
    // Fill out sprite data

    // uint8_t * med_square_data = (uint8_t*) malloc(1024*sizeof(uint8_t));
    uint8_t *med_square_data = (uint8_t *) mem_alloc(1024);
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
    uint8_t background_data[512 * 288];
    for (int y = 0; y < 288; ++y)
    {
        for (int x = 0; x < 512; ++x)
        {
            background_data[y * 512 + x] = 2;
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

    uint32_t *sprite_palette = (uint32_t *)malloc_sys(256 * sizeof(uint32_t));
    sprite_palette[1] = 0xFFFF06B5; // A R G B
    sprite_palette[2] = 0xFF00FF00; // Green
    sprite_palette[3] = 0xFF0000FF; // Blue


    load_palette(MEDIUM, sprite_palette, 0);
    load_palette(SMALL, sprite_palette, 0);
    load_palette(LARGE, sprite_palette, 0);
    load_background_palette(sprite_palette, 0);

    sprite_t square;
    square.type = MEDIUM;
    square.data_index = 0;
    square.palette = 0;
    square.x = 0;
    square.y = 0;
    square.z = 0;
    uint16_t id = load_sprite(square);
    square.type = SMALL;
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
            default:
                break;
            }
            if(x_pos != last_x_pos) {
                last_x_pos = x_pos;
                display_sprite(id, (x_pos & 0x3F) << 3, (x_pos >> 6) << 3, 0);
            }
        }
        if (cmd != lastCmd) { // reset position if cmd pressed
            lastCmd = cmd;
            // x_pos = 40;
            // VIDEO_MEMORY[x_pos] = 'X';
            // MEDIUM_CONTROL[0] = MediumControl(0, (x_pos & 0x3F)<<3, (x_pos>>6)<<3, 0, 0);
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

