.section .text, "ax"
.global GetTicks, GetController, GetCmd


GetTicks:
    li a5, 1
    ecall
GetController:
    li a5, 2
    ecall
GetCmd:
    li a5, 3
    ecall