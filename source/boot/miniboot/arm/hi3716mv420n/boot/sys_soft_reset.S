#include <config.h>

#ifdef CONFIG_SYS_SRST_SUPPORT
.align  4
.globl _sys_srst_startup
.globl _sys_srst_end

_sys_srst_startup:
_sys_srst:
1:
	/* Set CPU freq to 24M */
	movw    r0, #0x2048
	movt    r0, #0xF8A2     /* CRG_CPU_LP */
	ldr     r1, [r0]
	bic     r1, #0x7		/* cpu_freq_sel */
	orr     r1, #0x4		/* cpu_freq_24m */
	orr     r1, #0x200		/* cpu_begin_cfg_bypass */
	bic     r1, #0x400		/* cpu_sw_begin_cfg */
	str     r1, [r0]
	orr     r1, #0x400		/* cpu_sw_begin_cfg */
	str     r1, [r0]
	dsb
	mov     r2, #0x0
wait0:
	add     r2, #1
	cmp     r2, #0x100
	blt     wait0

	/* Set DDR freq to 24M */
	movw    r0, #0x2128
	movt    r0, #0xF8A2     /* CRG_DDR_LP */
	ldr     r1, [r0]
	bic     r1, #0x7		/* ddr_freq_sel */
	orr     r1, #0x4		/* ddr_freq_24m */
	orr     r1, #0x200		/* ddr_begin_cfg_bypass */
	bic     r1, #0x400		/* ddr_sw_begin_cfg */
	str     r1, [r0]
	orr     r1, #0x400		/* ddr_sw_begin_cfg */
	str     r1, [r0]
	dsb
	mov     r2, #0x0
wait1:
	add     r2, #1
	cmp     r2, #0x100
	blt     wait1

	mov     r4, #0
	movt    r4, #0xF800                 /* r4: REG_SC_BASE */
	mov     r0, #1
	str     r0, [r4, #4]                /* Set SC_SYSRES to 1 */
	dsb
.rept 10
	b       1b
.endr

.rept 10
	b	_sys_srst
.endr

	dsb
	dsb
	dsb
_sys_srst_end:
#endif
