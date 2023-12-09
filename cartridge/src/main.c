#include <stdint.h>
#include <sprite.h>
#include <stdlib.h>
#include <background.h>
#include <threading/threads.h>
#include <controller.h>
#include <util.h>

void display_game_over(void);

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
    med_buffer[y_off_permanent + (2*32) + 14] = 1;

    med_buffer[y_off_permanent + (3*32) + 12] = 2;
    med_buffer[y_off_permanent + (3*32) + 12] = 1;

    med_buffer[y_off_permanent + (4*32) + 12] = 2;
    med_buffer[y_off_permanent + (5*32) + 12] = 2;

    for(int y = 6; y <= 9; ++y) {
        med_buffer[y_off_permanent + (y*32) + 12] = 3;
        med_buffer[y_off_permanent + (y*32) + 13] = 2;

        med_buffer[y_off_permanent + ((y+11)*32) + 12] = 3;
        med_buffer[y_off_permanent + ((y+11)*32) + 13] = 2;
    }

    
    med_buffer[y_off_permanent + (10*32) + 8] = 2;
    med_buffer[y_off_permanent + (10*32) + 9] = 2;
    med_buffer[y_off_permanent + (10*32) + 12] = 2; 
    med_buffer[y_off_permanent + (10*32) + 13] = 3; 
    med_buffer[y_off_permanent + (10*32) + 14] = 2; 

    med_buffer[y_off_permanent + (11*32) + 7] = 3;
    med_buffer[y_off_permanent + (11*32) + 8] = 3;
    med_buffer[y_off_permanent + (11*32) + 9] = 2;
    med_buffer[y_off_permanent + (11*32) + 10] = 2;
    med_buffer[y_off_permanent + (11*32) + 11] = 1;
    med_buffer[y_off_permanent + (11*32) + 12] = 2;
    med_buffer[y_off_permanent + (11*32) + 13] = 2;
    med_buffer[y_off_permanent + (11*32) + 14] = 3;
    med_buffer[y_off_permanent + (11*32) + 15] = 3;
    med_buffer[y_off_permanent + (11*32) + 16] = 3;
    med_buffer[y_off_permanent + (11*32) + 17] = 3;

    med_buffer[y_off_permanent + (13*32) + 4] = 6;
    med_buffer[y_off_permanent + (13*32) + 25] = 3;
    med_buffer[y_off_permanent + (13*32) + 26] = 3;
    int topbotval = 6;
    int midval = 5;
    for(int x = 5; x < 25; ++x) {
        if(x == 6) {
            topbotval = 5;
            midval = 4;
        } else if(x == 7) {
            topbotval = topbotval = 4;
            midval = 3;
        }else if(x == 10) {
            topbotval = 2;
        } else if(x == 12) {
            topbotval = 1;
            midval = 2;
        } else if(x == 15) {
            midval = 7;
        } else if(x == 17) {
            topbotval = 3;
        } else if(x == 24) {
            midval = 3;
        }
        med_buffer[y_off_permanent + (12*32) + x] = topbotval;
        med_buffer[y_off_permanent + (13*32) + x] = midval;
        med_buffer[y_off_permanent + (14*32) + x] = topbotval;
    }

    med_buffer[y_off_permanent + (15*32) + 7] = 3;
    med_buffer[y_off_permanent + (15*32) + 8] = 3;
    med_buffer[y_off_permanent + (15*32) + 9] = 2;
    med_buffer[y_off_permanent + (15*32) + 10] = 2;
    med_buffer[y_off_permanent + (15*32) + 11] = 1;
    med_buffer[y_off_permanent + (15*32) + 12] = 2;
    med_buffer[y_off_permanent + (15*32) + 13] = 2;
    med_buffer[y_off_permanent + (15*32) + 14] = 3;
    med_buffer[y_off_permanent + (15*32) + 15] = 3;
    med_buffer[y_off_permanent + (15*32) + 16] = 3;
    med_buffer[y_off_permanent + (15*32) + 17] = 3;

    med_buffer[y_off_permanent + (16*32) + 8] = 2;
    med_buffer[y_off_permanent + (16*32) + 9] = 2;
    med_buffer[y_off_permanent + (16*32) + 12] = 2; 
    med_buffer[y_off_permanent + (16*32) + 13] = 3; 
    med_buffer[y_off_permanent + (16*32) + 14] = 2; 

    med_buffer[y_off_permanent + (21*32) + 12] = 2;
    med_buffer[y_off_permanent + (22*32) + 12] = 2;

    med_buffer[y_off_permanent + (23*32) + 12] = 2;
    med_buffer[y_off_permanent + (23*32) + 12] = 1;

    med_buffer[y_off_permanent + (24*32) + 10] = 6;
    med_buffer[y_off_permanent + (24*32) + 11] = 4;
    med_buffer[y_off_permanent + (24*32) + 12] = 2;
    med_buffer[y_off_permanent + (24*32) + 13] = 1;
    med_buffer[y_off_permanent + (24*32) + 14] = 1;

    med_buffer[y_off_permanent + (25*32) + 9] = 6;
    med_buffer[y_off_permanent + (25*32) + 10] = 5;
    med_buffer[y_off_permanent + (25*32) + 11] = 4;
    med_buffer[y_off_permanent + (25*32) + 12] = 1;
    med_buffer[y_off_permanent + (25*32) + 13] = 1;
    med_buffer[y_off_permanent + (25*32) + 14] = 1;
    med_buffer[y_off_permanent + (25*32) + 15] = 1;
}


int main()
{
    int global = GetTicks();
    int last_global = global;
    int glob_init = global;
    
    // Fill out sprite data

    // uint8_t * med_square_data = (uint8_t*) malloc(1024*sizeof(uint8_t));
    uint8_t *med_square_data = (uint8_t *) malloc(1024*sizeof(uint8_t));



    // create background in pixel mode:
    //uint8_t background_data[512 * 288];
    uint8_t *background_data = (uint8_t*) malloc(512*288*sizeof(uint8_t));
    for (int y = 0; y < 18; ++y)
    {
        for (int x = 0; x < 32; ++x)
        {
            int offset = (((y*512)*16)+((x*16)));
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
    //load_sprite_data(SMALL, small_square_data, 0);
    //load_sprite_data(LARGE, large_square_data, 0);
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


    

    //fill obstacle datas

    uint32_t *sprite_palette = (uint32_t *)malloc(256 * sizeof(uint32_t));
    sprite_palette[1] = 0xFFFF06B5; // A R G B
    sprite_palette[2] = 0xFF00FF00; // Green
    sprite_palette[3] = 0xFF0000FF; // Blue
    sprite_palette[4] = 0xFFFFFFFF; //white
    sprite_palette[5] = 0xFF9C5A3c; //brown

    load_palette(MEDIUM, sprite_palette, 0);
    load_palette(SMALL, sprite_palette, 0);
    load_palette(LARGE, sprite_palette, 0);
    load_background_palette(sprite_palette, 0);


    uint8_t * small_obstacle_data = (uint8_t*) malloc(16*16*sizeof(uint8_t));
    uint8_t * medium_obstacle_data = (uint8_t*) malloc(32*32*sizeof(uint8_t));
    uint8_t * large_obstacle_data = (uint8_t*) malloc(64*64*sizeof(uint8_t));

    for(int i = 0; i < 64*64; ++i) {
        //small range:
        if(i < 16*16) small_obstacle_data[i] = 5;
        //med range
        if(i < 32*32) medium_obstacle_data[i] = 5;
        //large range
        if(i < 64*64) large_obstacle_data[i] = 5;

    }

    load_sprite_data(SMALL, small_obstacle_data, 5);
    load_sprite_data(MEDIUM, medium_obstacle_data, 5);
    load_sprite_data(LARGE, large_obstacle_data, 5);


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
    uint16_t spaceship_id = load_sprite(square);
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
    //initial sprite locations:
    uint16_t sprite_init_y[8];
    sprite_init_y[0] = 32;
    sprite_init_y[1] = 64;
    sprite_init_y[2] = 96;
    sprite_init_y[3] = 128;
    sprite_init_y[4] = 160;
    sprite_init_y[5] = 192;
    sprite_init_y[6] = 224;
    sprite_init_y[7] = 256;

    //do % 8 on timer to "randomly" get new index?

    uint8_t num_small_obstacles, num_medium_obstacles, num_large_obstacles;
    num_small_obstacles = 8;
    num_medium_obstacles = 5;
    num_large_obstacles = 2;


    sprite_t small_sprites[8];
    sprite_t medium_sprites[8];
    sprite_t large_sprites[8];
    for(int i = 0; i < 8; ++i) {
        small_sprites[i].type = SMALL;
        small_sprites[i].x = 512;
        small_sprites[i].y = sprite_init_y[i];
        small_sprites[i].z = 1;
        small_sprites[i].palette = 0;
        small_sprites[i].data_index = 5;
        
        medium_sprites[i].type = MEDIUM;
        medium_sprites[i].x = 512;
        medium_sprites[i].y = sprite_init_y[i];
        medium_sprites[i].z = 1;
        medium_sprites[i].palette = 0;
        medium_sprites[i].data_index = 5;

        large_sprites[i].type = LARGE;
        large_sprites[i].x = 512;
        large_sprites[i].y = sprite_init_y[i];
        large_sprites[i].z = 1;
        large_sprites[i].palette = 0;
        large_sprites[i].data_index = 5;
    }


    uint16_t small_obstacle_ids[8];
    uint16_t medium_obstacle_ids[8];
    uint16_t large_obstacle_ids[8];

    for(int i = 0; i < 8; ++i) {
        small_obstacle_ids[i] = 0;
        medium_obstacle_ids[i] = 0;
        large_obstacle_ids[i] = 0;
    }

    small_obstacle_ids[3] = load_sprite(small_sprites[3]);
    medium_obstacle_ids[5] = load_sprite(medium_sprites[5]); 

    int8_t small_speed = -5;
    int8_t medium_speed = -2;
    int8_t large_speed = -1;

    int8_t plusMinus = 1;
    Button controller_status = get_controller();
    
    int x_pos = 0;
    uint16_t spaceship_x = 20;
    uint16_t spaceship_y = 128;
    int last_y_pos = spaceship_y;
    //display_sprite(small_id, 200, 50, 1);
    free(spaceship_palette);
    free(background_data);

    uint16_t num_deleted_obstacles = 0;
    uint16_t last_num_deleted_obstacles = 0;
    uint16_t num_active_obstacles = 2;

    while (1) {
        threadYield();
        // int c = a + b + global;
        global = GetTicks();
        uint32_t cmd = GetCmd();
        if (global != last_global) {
            controller_status = get_controller();
            
            switch (controller_status) {
            case w:
                if (spaceship_y >= 0) {
                    spaceship_y -= 1;
                }
                break;
            case x:
                if (spaceship_y < 256){
                    spaceship_y += 1;
                }
                break;
            case i:
                display_game_over();
                break;
            default:
                break;
            }
            if(spaceship_y != last_y_pos) {
                last_y_pos = spaceship_y;
                display_sprite(spaceship_id, spaceship_x, spaceship_y, 0);
            }
        }
        if (cmd) { // reset position if cmd pressed
            clear_cmd();
            delete_sprite(spaceship_id);
            delete_background(back_id);
        }
        if (large_x >= 448) plusMinus = -1;
        if (large_x <= 0) plusMinus = 1;
        last_global = global;
        //Sprite Movement
        if (glob_init + 5 <= last_global) {
            for(int i = 0; i < 8; ++i) {

                if(small_obstacle_ids[i]) {
                    small_sprites[i].x += small_speed;
                    if(small_sprites[i].x <= -16) {
                        delete_sprite(small_obstacle_ids[i]);
                        num_deleted_obstacles++;
                        small_sprites[i].x = 512;
                        small_obstacle_ids[i] = 0;

                        //upon deletion, create new one
                        uint8_t idx = (global + num_deleted_obstacles + i) % 8;
                        uint8_t temp = 1;
                        while(small_obstacle_ids[idx]) {
                            idx = (global + num_deleted_obstacles + i+temp) % 8; //TOODO may cause inf loop
                            temp++;
                        }
                        small_obstacle_ids[idx] = load_sprite(small_sprites[idx]);
                    } else {
                        display_sprite(small_obstacle_ids[i],small_sprites[i].x,small_sprites[i].y,1);
                    }
                    //small_obstacle_x[i] += small_speed;
                }

                if(medium_obstacle_ids[i]) {
                    medium_sprites[i].x += medium_speed;
                    if(medium_sprites[i].x <= -32) {
                        delete_sprite(medium_obstacle_ids[i]);
                        num_deleted_obstacles++;
                        medium_sprites[i].x = 512;
                        medium_obstacle_ids[i] = 0;

                        uint8_t idx = (global + num_deleted_obstacles + i) % 8;
                        //while(medium_obstacle_ids[idx]) idx = (global + num_deleted_obstacles + i+1) % 8; //TOODO may cause inf loop
                        uint8_t temp = 1;
                        while(medium_obstacle_ids[idx]) {
                            idx = (global + num_deleted_obstacles + i+temp) % 8;
                            temp++;
                        }
                        medium_obstacle_ids[idx] = load_sprite(medium_sprites[idx]);
                    } else {
                        display_sprite(medium_obstacle_ids[i],medium_sprites[i].x,medium_sprites[i].y,1);
                    }
                }

                if(large_obstacle_ids[i]) {
                    large_sprites[i].x += large_speed;
                    if(large_sprites[i].x <= -64) {
                        delete_sprite(large_obstacle_ids[i]);
                        num_deleted_obstacles++;
                        large_sprites[i].x = 512;
                        large_obstacle_ids[i] = 0;
                        uint8_t temp = 1;
                        uint8_t idx = (global + num_deleted_obstacles + i) % 8;
                        while(large_obstacle_ids[idx]) {
                            idx = (global + num_deleted_obstacles + i+temp) % 8; //TOODO may cause inf loop
                            temp++;
                        }
                        large_obstacle_ids[idx] = load_sprite(large_sprites[idx]);
                    } else {
                        display_sprite(large_obstacle_ids[i],large_sprites[i].x,large_sprites[i].y,1);
                    }
                }
            }
            glob_init = last_global;
            //large_x += plusMinus;
            //display_sprite(large_id, large_x, large_y, 0);
            //update #active obstacles
            if(num_active_obstacles < 9 && (num_deleted_obstacles > (5 + last_num_deleted_obstacles))) {
                last_num_deleted_obstacles = num_deleted_obstacles;
                num_active_obstacles++;
                int idx = (global + num_deleted_obstacles) % 8;
                uint8_t temp = 0;
                switch(num_active_obstacles) {
                    case 3:
                        while(small_obstacle_ids[idx]) {
                            idx = (global + num_deleted_obstacles + temp) % 8;
                            temp++;
                        }
                        small_obstacle_ids[idx] = load_sprite(small_sprites[idx]);
                        break;
                    case 4:
                        //create new small
                        while(small_obstacle_ids[idx]) {
                            idx = (global + num_deleted_obstacles + temp) % 8;
                            temp++;
                        }
                        small_obstacle_ids[idx] = load_sprite(small_sprites[idx]);
                        break;
                    case 5:
                        //create new medium
                        while(medium_obstacle_ids[idx]) {
                            idx = (global + num_deleted_obstacles + temp) % 8;
                            temp++;
                        }
                        medium_obstacle_ids[idx] = load_sprite(medium_sprites[idx]);
                        break;
                    case 6:
                        while(large_obstacle_ids[idx]) {
                            idx = (global + num_deleted_obstacles + temp) % 8;
                            temp++;
                        }
                        large_obstacle_ids[idx] = load_sprite(large_sprites[idx]);
                        break;
                    case 7:
                        while(medium_obstacle_ids[idx]) {
                            idx = (global + num_deleted_obstacles + temp) % 8;
                            temp++;
                        }
                        medium_obstacle_ids[idx] = load_sprite(medium_sprites[idx]);
                        break;
                    case 8:
                        while(small_obstacle_ids[idx]) {
                            idx = (global + num_deleted_obstacles + temp) % 8;
                            temp++;
                        }
                        small_obstacle_ids[idx] = load_sprite(small_sprites[idx]);
                        break;
                    case 9:
                        while(large_obstacle_ids[idx]) {
                            idx = (global + num_deleted_obstacles + temp) % 8;
                            temp++;
                        }
                        large_obstacle_ids[idx] = load_sprite(large_sprites[idx]);
                        break;
                    default:
                        break;
                }
            }

            //check collisions
            for(int i = 0; i < 8; ++i) {    
                if(small_obstacle_ids[i]) { //Id exists
                    if((small_sprites[i].x >= spaceship_x && small_sprites[i].x < spaceship_x + 32) 
                        || (small_sprites[i].x + 16 >= spaceship_x && small_sprites[i].x + 16 < spaceship_x + 32)) { //correct X coordinate
                        if((small_sprites[i].y >= spaceship_y && small_sprites[i].y < spaceship_y + 32) 
                            || (small_sprites[i].y + 16 >= spaceship_y && small_sprites[i].y + 16 < spaceship_y + 32)) { //correct Y coordinate
                                display_game_over();
                        } 
                    }
                }
                
                if(medium_obstacle_ids[i]) {
                    if((medium_sprites[i].x >= spaceship_x && medium_sprites[i].x < spaceship_x + 32) 
                    || (medium_sprites[i].x + 32 >= spaceship_x && medium_sprites[i].x + 32 < spaceship_x + 32)) { //correct X
                        if((medium_sprites[i].y >= spaceship_y && medium_sprites[i].y < spaceship_y + 32) 
                        || (medium_sprites[i].y + 32 >= spaceship_y && medium_sprites[i].y + 32 < spaceship_y + 32)) { //correct Y
                            display_game_over();
                        }
                    }
                }

                if(large_obstacle_ids[i]) {
                    if((large_sprites[i].x >= spaceship_x && large_sprites[i].x < spaceship_x + 32) 
                    || (large_sprites[i].x + 64 >= spaceship_x && large_sprites[i].x + 64 < spaceship_x + 32)) {
                        if((large_sprites[i].y >= spaceship_y && large_sprites[i].y < spaceship_y + 32) 
                        || (large_sprites[i].y + 64 >= spaceship_y && large_sprites[i].y + 64 < spaceship_y + 32)) {
                            display_game_over();
                        }
                    }
                }

            }

        }
    }
    return 0;
}



void display_game_over(void) {
    //create completely black background:
    background_t end_back;
    end_back.type = PIXEL;
    end_back.x = 0;
    end_back.y = 0;
    end_back.z = 3;
    end_back.data_index = 0;
    end_back.palette = 0;
    uint32_t* back_palette = (uint32_t*) malloc(256*sizeof(uint32_t));
    back_palette[0] = 0xFF000000;
    back_palette[1] = 0xFFFF0000;

    uint8_t* back_buf = (uint8_t*) malloc(288*512*sizeof(uint8_t));
    uint8_t* sprite_data = (uint8_t*) malloc(16*16*sizeof(uint8_t));
    for(int i = 0; i < 288*512; ++i) {
        back_buf[i] = 0;
    }
    for(int i = 0; i < 16*16; ++i) {
        sprite_data[i] = 1;
    }
    load_background_palette(back_palette,0);
    load_palette(SMALL, back_palette, 3);
    load_background_data_pixel(back_buf, 0);
    load_sprite_data(SMALL, sprite_data, 125);
    load_background(end_back);

    uint16_t temp_id;
    sprite_t draw_sprite;
    draw_sprite.type = SMALL;
    draw_sprite.data_index = 125;
    draw_sprite.palette = 3;
    draw_sprite.z = 3;

    draw_sprite.x = 123;
    draw_sprite.y = 46;
    temp_id = load_sprite(draw_sprite);
    display_sprite(temp_id, draw_sprite.x, draw_sprite.y, 3);

    draw_sprite.x = 76;
    draw_sprite.y = 40;
    temp_id = load_sprite(draw_sprite);
    display_sprite(temp_id, draw_sprite.x, draw_sprite.y, 3);

    draw_sprite.x = 92;
    draw_sprite.y = 40;
    temp_id = load_sprite(draw_sprite);
    //display_sprite(temp_id, draw_sprite.x, draw_sprite.y, 3);

    draw_sprite.x = 108;
    draw_sprite.y = 40;
    temp_id = load_sprite(draw_sprite);
    //display_sprite(temp_id, draw_sprite.x, draw_sprite.y, 3);

    draw_sprite.x = 60;
    draw_sprite.y = 64;
    temp_id = load_sprite(draw_sprite);
    //display_sprite(temp_id, draw_sprite.x, draw_sprite.y, 3);

    draw_sprite.y = 80;
    load_sprite(draw_sprite);

    draw_sprite.x = 76;
    draw_sprite.y = 96;
    load_sprite(draw_sprite);

    draw_sprite.x = 93;
    draw_sprite.y = 96;
    load_sprite(draw_sprite);

    draw_sprite.x = 109;
    draw_sprite.y = 96;
    load_sprite(draw_sprite);

    draw_sprite.y = 93;
    load_sprite(draw_sprite);

    for(int i = 0; i < 10000000; ++i) {
        //wait for a bit to display
    }

    free(back_buf);
    free(back_palette);

}