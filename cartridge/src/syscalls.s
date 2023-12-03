.section .text, "ax"
.global threadCreate, threadYield, threadExit
.global lockAcquire, lockRelease, lockCreate

# Threading #

threadCreate:
    li a5, 10
    ecall

threadYield:
    mv a0, sp   # Move stack pointer for yielding
    li a5, 11
    ecall

threadExit:
    li a5, 12
    ecall

# Locks #

lockAcquire:
    li a5, 13
    ecall

lockRelease:
    li a5, 14
    ecall

lockCreate:
    li a5, 15
    ecall
