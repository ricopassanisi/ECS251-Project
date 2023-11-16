.section .text, "ax"
.global GetTicks, GetController, GetCmd, load_sprite_sys, load_sprite_data_sys, load_palette_sys, display_sprite_sys, delete_sprite_sys, change_sprite_palette_sys


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