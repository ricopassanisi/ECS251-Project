.section .text, "ax"
.global threadCreate, threadYield, threadExit


# Threading #

threadCreate:
    li a5, 10
    ecall

threadYield:
    li a5, 11
    ecall

threadExit:
    li a5, 12
    ecall
