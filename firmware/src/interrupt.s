.section .text, "ax"
.global _interrupt_handler, _system_call, InitThread, SwitchThread, StartThread
.global _setGP
_interrupt_handler:
    csrw    mscratch,ra
    csrr    ra,mcause
    addi    ra,ra,-11
    beqz    ra, _system_call
    csrr    ra,mscratch
    addi	sp,sp,-44
    sw	    gp,40(sp)
    sw	    ra,36(sp)
    sw	    t0,32(sp)
    sw	    t1,28(sp)
    sw	    t2,24(sp)
    sw	    a0,20(sp)
    sw	    a1,16(sp)
    sw	    a2,12(sp)
    sw	    a3,8(sp)
    sw	    a4,4(sp)
    sw	    a5,0(sp)
    csrr    a0,mcause
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    call    c_interrupt_handler
    lw	    gp,40(sp)
    lw	    ra,36(sp)
    lw	    t0,32(sp)
    lw	    t1,28(sp)
    lw	    t2,24(sp)
    lw	    a0,20(sp)
    lw	    a1,16(sp)
    lw	    a2,12(sp)
    lw	    a3,8(sp)
    lw	    a4,4(sp)
    lw	    a5,0(sp)
    addi    sp,sp,44
    mret



_system_call:
    csrr    ra,mscratch
    csrw    mepc,ra
    csrw    mscratch,gp
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    call    c_system_call
    csrr    gp,mscratch
    mret

InitThread:
    addi    a0,a0,-52
    sw	    a1,48(a0)
    sw	    zero,44(a0)
    sw	    zero,40(a0)
    sw	    zero,36(a0)
    sw	    zero,32(a0)
    sw	    zero,28(a0)
    sw	    zero,24(a0)
    sw	    a2,20(a0)
    sw	    a3,16(a0) # Changed here for threadwrapper
    sw	    zero,12(a0)
    sw	    zero,8(a0)
    sw	    zero,4(a0)
    sw	    zero,0(a0)
    ret
    
SwitchThread:
    # move arg0 stack pointer to here
    # c_system_call overwrites some things
    # Setting stack pointer to exactly what it was when syscall invoked
    mv      sp, a2

    addi	sp,sp,-52
    
    #sw	    ra,48(sp)
    # Storing mepc as ra
    csrr    a2, mepc
    sw      a2, 48(sp)
    
    sw	    tp,44(sp)
    sw	    t0,40(sp)
    sw	    t1,36(sp)
    sw	    t2,32(sp)
    sw	    s0,28(sp)
    sw	    s1,24(sp)
    sw	    a0,20(sp)
    sw	    a1,16(sp)
    sw	    a2,12(sp)
    sw	    a3,8(sp)
    sw	    a4,4(sp)
    sw	    a5,0(sp)

    sw      sp,0(a0)
    mv      sp,a1

    mv      gp, a3      # Set global pointer back to cartridge

    lw	    ra,48(sp)
    lw	    tp,44(sp)
    lw	    t0,40(sp)
    lw	    t1,36(sp)
    lw	    t2,32(sp)
    lw	    s0,28(sp)
    lw	    s1,24(sp)
    lw	    a0,20(sp)
    lw	    a1,16(sp)
    lw	    a2,12(sp)
    lw	    a3,8(sp)
    lw	    a4,4(sp)
    lw	    a5,0(sp)
    addi	sp,sp,52

    csrsi mstatus, 0x8  # Enable Interrupts
    ret

StartThread:            # Starts a thread without switching context
                        # Ex, if a thread has completed execution
    mv      sp,a0

    mv      gp, a1      # Set global pointer back to cartridge

    lw	    ra,48(sp)
    lw	    tp,44(sp)
    lw	    t0,40(sp)
    lw	    t1,36(sp)
    lw	    t2,32(sp)
    lw	    s0,28(sp)
    lw	    s1,24(sp)
    lw	    a0,20(sp)
    lw	    a1,16(sp)
    lw	    a2,12(sp)
    lw	    a3,8(sp)
    lw	    a4,4(sp)
    lw	    a5,0(sp)
    addi	sp,sp,52

    csrsi mstatus, 0x8
    ret


#
# Loads Firmware Global Pointer
#
_setGP:
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    ret