#include <stdint.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;


uint32_t MediumControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index);

//Video memory and medium sprite stuff:
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xF4800);
volatile uint8_t *MEDIUM_DATA = (volatile uint8_t *)(0x500D0000);
volatile uint32_t *MEDIUM_PALETTE = (volatile uint32_t *)(0x500F2000);
volatile uint32_t *MEDIUM_CONTROL = (volatile uint32_t *)(0x500F5F00);
volatile uint32_t *MODE_REGISTER = (volatile uint32_t *)(0x500F6780);

//Syscall setup
uint32_t GetTicks(void);
uint32_t GetController(void);
uint32_t GetCmd(void);

int main() {
    int last_global = 42;
    int x_pos = 0;
    uint32_t lastCmd = 0;
    // Fill out sprite data
    for(int y = 0; y < 32; y++){
        for(int x = 0; x < 32; x++){
            MEDIUM_DATA[y*32+x] = 1;
           // MEDIUM_DATA[(1024)+(y*32+x)] = 2;
        }
    }
    // Create green triangle
    for(int y = 0; y < 32; ++y) {
        for(int x = 0; x < y+1; ++x) {
            MEDIUM_DATA[(1024)+(y*32+x)] = 2;
        }
    }
    // Create blue triangle
    for(int y = 0; y < 32; ++y) {
        for(int x = 31; x >= y; --x) {
            MEDIUM_DATA[(1024*2)+(y*32+x)] = 3;
        }
    }

    MEDIUM_PALETTE[1] = 0xFFFF06B5; // A R G B
    MEDIUM_PALETTE[2] = 0xFF00FF00; //Green
    MEDIUM_PALETTE[3] = 0xFF0000FF; //Blue
    MEDIUM_CONTROL[0] = MediumControl(0, 0, 0, 0, 0);
    MEDIUM_CONTROL[1] = MediumControl(0,50,50,1,1); //pallete, x, y, z, index
    MEDIUM_CONTROL[2] = MediumControl(0,100,100,1,2);
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
                MEDIUM_CONTROL[0] = MediumControl(0, (x_pos & 0x3F)<<3, (x_pos>>6)<<3, 0, 0);
                //MEDIUM_CONTROL[2] = MediumControl(0,((x_pos + 100)& 0x3F)<<3,((x_pos+100)>>6)<<3,1,2); //for moving blue triangle
            }
            if(cmd != lastCmd) { //reset position if cmd pressed
                lastCmd = cmd;
                x_pos = 40;
                VIDEO_MEMORY[x_pos] = 'X';
                MEDIUM_CONTROL[0] = MediumControl(0, (x_pos & 0x3F)<<3, (x_pos>>6)<<3, 0, 0);
            }
            last_global = global;
        }
    }
    return 0;
}

uint32_t MediumControl(uint8_t palette, int16_t x, int16_t y, uint8_t z, uint8_t index){
    return (((uint32_t)index)<<24) | (((uint32_t)z)<<21) | (((uint32_t)y+32)<<12) | (((uint32_t)x+32)<<2) | (palette & 0x3);
}