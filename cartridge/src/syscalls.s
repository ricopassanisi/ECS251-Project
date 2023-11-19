.section .text, "ax"
.global GetTicks, GetController, GetCmd, load_sprite_sys
.global load_sprite_data_sys, load_palette_sys, display_sprite_sys 
.global delete_sprite_sys, change_sprite_palette_sys, load_background_palette_sys, load_background_data_pixel_sys
.global load_background_sys, delete_background_sys


GetTicks:
    li a5, 1
    ecall
GetController:
    li a5, 2
    ecall
GetCmd:
    li a5, 3
    ecall
load_sprite_sys:
    li a5, 4
    ecall
load_sprite_data_sys:
    li a5, 5
    ecall
load_palette_sys:
    li a5, 6
    ecall
display_sprite_sys:
    li a5, 7
    ecall
delete_sprite_sys:
    li a5, 8
    ecall
change_sprite_palette_sys:
    li a5, 9
    ecall
load_background_palette_sys:
    li a5, 10
    ecall
load_background_data_pixel_sys:
    li a5, 11
    ecall
load_background_sys:
    li a5, 12
    ecall
delete_background_sys:
    li a5, 13
    ecall
    