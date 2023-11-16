#include <stdint.h>
#include <stdlib.h>
#include <sprite.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;


//Video memory and medium sprite stuff:
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
volatile uint32_t *MODE_REGISTER = (volatile uint32_t *)(0x500F6780);

//Syscall setup
uint32_t GetTicks(void);
uint32_t GetController(void);
uint32_t GetCmd(void);

int main() {
    int last_global = 42;
    int x_pos = 0;
    uint32_t lastCmd = GetCmd();
    // Fill out sprite data
    

    uint8_t square_data[1024]; // = (uint8_t*) malloc(1024*sizeof(uint8_t));
    for(int y = 0; y < 32; y++){
        for(int x = 0; x < 32; x++){
            square_data[y*32+x] = 1;
           // MEDIUM_DATA[(1024)+(y*32+x)] = 2;
        }
    }

    load_sprite_data(MEDIUM, square_data, 0);

    // Create green triangle
    for(int y = 0; y < 32; ++y) {
        for(int x = 0; x < y+1; ++x) {
           // MEDIUM_DATA[(1024)+(y*32+x)] = 2;
        }
    }
    // Create blue triangle
    for(int y = 0; y < 32; ++y) {
        for(int x = 31; x >= y; --x) {
            //MEDIUM_DATA[(1024*2)+(y*32+x)] = 3;
        }
    }

    uint32_t sprite_palette[256];
    sprite_palette[1] = 0xFFFF06B5; // A R G B
    sprite_palette[2] = 0xFF00FF00; //Green
    sprite_palette[3] = 0xFF0000FF; //Blue

    load_palette(MEDIUM, sprite_palette, 0);
    sprite_t square;
    square.type = MEDIUM;
    square.data_index = 0;
    square.palette = 0;
    square.x = 0;
    square.y = 0;
    square.z = 0;
    uint16_t id = load_sprite(square);
    //MEDIUM_CONTROL[0] = MediumControl(0, 0, 0, 0, 0);
    //MEDIUM_CONTROL[1] = MediumControl(0,50,50,1,1); //pallete, x, y, z, index
    //MEDIUM_CONTROL[2] = MediumControl(0,100,100,1,2);
    *MODE_REGISTER = 1;

    while (1) {
        //int c = a + b + global;
        global = GetTicks();
        uint32_t cmd = GetCmd();
        if(global != last_global){
            controller_status = GetController();
            if(controller_status){
                VIDEO_MEMORY[x_pos] = ' ';
                if(controller_status & 0x1){
                    if(x_pos & 0x3F){
                        x_pos--;
                    }
                }
                if(controller_status & 0x2){
                    if(x_pos >= 0x40){
                        x_pos -= 0x40;
                    }
                }
                if(controller_status & 0x4){
                    if(x_pos < 0x8C0){
                        x_pos += 0x40;
                    }
                }
                if(controller_status & 0x8){
                    if((x_pos & 0x3F) != 0x3F){
                        x_pos++;
                    }
                }
                VIDEO_MEMORY[x_pos] = 'X';
                display_sprite(id, (x_pos & 0x3F)<<3, (x_pos>>6)<<3, 0);
                //MEDIUM_CONTROL[0] = MediumControl(0, (x_pos & 0x3F)<<3, (x_pos>>6)<<3, 0, 0);
                //MEDIUM_CONTROL[2] = MediumControl(0,((x_pos + 100)& 0x3F)<<3,((x_pos+100)>>6)<<3,1,2); //for moving blue triangle
            }
            if(cmd != lastCmd) { //reset position if cmd pressed
                lastCmd = cmd;
                x_pos = 40;
                VIDEO_MEMORY[x_pos] = 'X';
                //MEDIUM_CONTROL[0] = MediumControl(0, (x_pos & 0x3F)<<3, (x_pos>>6)<<3, 0, 0);
                delete_sprite(id);
            }
            last_global = global;
        }
    }
    return 0;
}
