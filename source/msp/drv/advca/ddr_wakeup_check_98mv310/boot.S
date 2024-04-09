.globl _start
_start:
    b       reset
    ldr     pc, _undefined_instruction
    ldr     pc, _software_interrupt
    ldr     pc, _prefetch_abort
    ldr     pc, _data_abort
    ldr     pc, _not_used
    ldr     pc, _irq
    ldr     pc, _fiq
      
_undefined_instruction: .word undefined_instruction
_software_interrupt:    .word software_interrupt
_prefetch_abort:        .word prefetch_abort
_data_abort:            .word data_abort
_not_used:              .word not_used
_irq:                   .word irq
_fiq:                   .word fiq
_pad:                   .word 0x12345678 /* now 16*4=64 */

.balignl 16,0xdeadbeef


/*
 * the actual reset code
 */
reset:
    //b .
    /* set the cpu to SVC32 mode, disable I/F */
    mrs     r0,cpsr
    bic     r0,r0,#0x1f
    orr     r0,r0,#0xd3
    msr     cpsr,r0

    /*
    * disable MMU stuff and caches
    * bit 13 is used to set the address of interrupt vector, 1 means 0xffff0000, 0 means 0x00000000 
    */
    mrc     p15, 0, r1, c1, c0, 0      /* get control register (c1)*/
    bic     r1, r1, #0x00001800        /* -IZ- */
    bic     r1, r1, #0x00000007        /* -CAM */
    bic     r1, r1, #0x00002000        /* clear bit 13 (--V-)      */
    mcr     p15, 0, r1, c1, c0, 0

    /*
    * Initialize the Registers first to avoid X status
    */
    mov  r1, #0
    mov  r2, #0
    mov  r3, #0
    mov  r4, #0
    mov  r5, #0
    mov  r6, #0
    mov  r7, #0
    mov  r8, #0
    mov  r9, #0
    mov  r10, #0
    mov  r11, #0
    mov  r12, #0

    /* set stack to ram */
    ldr     r0, =STACK_ADDR
    mov     sp, r0

    /* main function */
    bl      main
    
    
.balign 4

/*
 *************************************************************************
 *
 * Interrupt handling
 *
 *************************************************************************
 */
undefined_instruction:
software_interrupt:
prefetch_abort:
data_abort:
not_used:
irq:
fiq:

    b       .