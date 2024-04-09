#include "hi_asm_define.h"
	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"bitplane.c"
	.text
	.align	2
	.global	BPD_CfgReg
	.type	BPD_CfgReg, %function
BPD_CfgReg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	mov	r4, r0
	ldr	r0, [r3, #8]
	mov	r5, r1
	mov	r1, #0
	str	r1, [fp, #-40]
	cmp	r0, r1
	beq	.L31
.L2:
	ldr	ip, .L36
	mvn	r0, #0
	mvn	r1, #1
	ldr	r3, [ip, #8]
	str	r0, [r3, #68]
	ldr	r3, [ip, #8]
	str	r1, [r3, #68]
	ldr	r0, [r5, #24]
	ldr	r3, [r5, #20]
	adds	r1, r0, #31
	ldr	lr, [r5]
	addmi	r1, r0, #62
	cmp	r0, #0
	bic	r1, r1, #31
	add	r5, r0, #7
	add	r1, r1, r3
	movge	r5, r0
	rsb	r1, r0, r1
	ldrb	r6, [r4, #3096]	@ zero_extendqisi2
	mov	r5, r5, asr #3
	mov	r3, r1, asr #31
	mov	r3, r3, lsr #27
	add	r1, r1, r3
	and	r1, r1, #31
	rsb	r3, r3, r1
	cmp	r3, #0
	add	r1, r3, #7
	movlt	r3, r1
	cmp	r6, #0
	add	r3, r5, r3, asr #3
	add	lr, lr, r3
	beq	.L5
	ldrb	r3, [r2, #362]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L6
	movw	r3, #362
	ldrh	r3, [r2, r3]
	cmp	r3, #4
	beq	.L6
	ldrb	r3, [r2, #197]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L32
.L8:
	ldrb	r3, [r2, #349]	@ zero_extendqisi2
	ldr	r5, [r2, #392]
	cmp	r3, #4
	ldrb	r6, [r2, #16]	@ zero_extendqisi2
	andne	r1, r3, #3
	ldrb	r3, [fp, #-38]	@ zero_extendqisi2
	moveq	r1, #3
	cmp	r5, #3
	bfi	r3, r5, #0, #2
	ldrb	r5, [fp, #-39]	@ zero_extendqisi2
	bfi	r3, r6, #2, #2
	strb	r3, [fp, #-38]
	bfi	r5, r1, #6, #2
	strb	r5, [fp, #-39]
	beq	.L33
.L11:
	add	r1, r4, #20480
	movw	r6, #21846
	movt	r6, 21845
	ldrb	r8, [fp, #-39]	@ zero_extendqisi2
	ldr	r3, [r1, #2756]
	smull	r6, r7, r3, r6
	sub	r5, r7, r3, asr #31
	add	r5, r5, r5, lsl #1
	rsb	r3, r5, r3
	bfi	r8, r3, #2, #2
	strb	r8, [fp, #-39]
.L15:
	ldr	r8, [r1, #2752]
	movw	r6, #21846
	movt	r6, 21845
	add	r5, r4, #32768
	and	r0, r0, #7
	smull	r6, r7, r8, r6
	ldr	r9, [r5, #2844]
	ldr	r3, [r5, #2856]
	rsb	r6, r9, lr
	sub	r7, r7, r8, asr #31
	add	r3, r6, r3
	ldrb	r6, [fp, #-39]	@ zero_extendqisi2
	and	r3, r3, #15
	add	r7, r7, r7, lsl #1
	rsb	r8, r7, r8
	add	r0, r0, r3, lsl #3
	bfi	r6, r8, #0, #2
	strb	r0, [fp, #-40]
	strb	r6, [fp, #-39]
	ldr	r3, [ip, #8]
	ldr	r0, [fp, #-40]
	str	r0, [r3, #4]
	ldr	r3, [r5, #2844]
	ldr	r6, [r5, #2856]
	ldr	r0, [ip, #8]
	rsb	lr, r3, lr
	add	lr, lr, r6
	bic	lr, lr, #15
	str	lr, [r0, #8]
	ldrb	r3, [r4, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L16
	ldr	r3, [r2, #392]
	cmp	r3, #3
	beq	.L34
.L16:
	ldr	r3, [r1, #2756]
	sub	r3, r3, #1
	strh	r3, [fp, #-38]	@ movhi
.L17:
	ldr	r3, [r1, #2752]
	mov	lr, #3
	ldr	r0, [ip, #8]
	mov	r2, #0
	sub	r3, r3, #1
	strh	r3, [fp, #-40]	@ movhi
	ldr	r3, [fp, #-40]
	mov	r4, #0
	str	r2, [fp, #-40]
	bfi	r4, lr, #4, #4
	str	r3, [r0, #12]
	mov	r0, r2
	ldr	r1, [r1, #2752]
	adds	r3, r1, #127
	addmi	r3, r1, #254
	ldr	r1, [ip, #8]
	mov	r3, r3, lsr lr
	and	r3, r3, #4080
	strh	r3, [fp, #-40]	@ movhi
	ldr	r3, [fp, #-40]
	str	r3, [r1, #16]
	ldr	r3, [ip, #8]
	ldr	r1, [r5, #2928]
	str	r1, [r3, #20]
	ldr	r3, [ip, #8]
	ldr	r1, [r5, #2932]
	str	r1, [r3, #24]
	ldr	r3, [ip, #8]
	ldr	r1, [r5, #2936]
	str	r1, [r3, #28]
	ldr	r3, [ip, #8]
	ldr	r1, [r5, #2940]
	str	r1, [r3, #32]
	ldr	r3, [ip, #8]
	ldr	r1, [r5, #2944]
	str	r1, [r3, #36]
	ldr	r3, [ip, #8]
	ldr	r1, [r5, #2948]
	str	r1, [r3, #40]
	ldr	r3, [ip, #8]
	ldr	r1, [r5, #2952]
	str	r1, [r3, #44]
	str	r2, [fp, #-40]
	strb	r4, [fp, #-40]
	strb	lr, [fp, #-39]
	ldr	r3, [ip, #8]
	ldr	r2, [fp, #-40]
	str	r2, [r3, #48]
.L4:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L5:
	ldrb	r3, [r2, #259]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L12
	cmp	r3, #4
	beq	.L35
.L13:
	ldrb	r3, [r2, #251]	@ zero_extendqisi2
	ldrb	r5, [fp, #-39]	@ zero_extendqisi2
	cmp	r3, #4
	ldrb	r6, [r2]	@ zero_extendqisi2
	andne	r1, r3, #3
	ldrb	r3, [fp, #-38]	@ zero_extendqisi2
	moveq	r1, #3
	bfi	r5, r1, #6, #2
	and	r3, r3, #252
	strb	r5, [fp, #-39]
	bfi	r3, r6, #2, #2
	strb	r3, [fp, #-38]
	b	.L11
.L6:
	ldrb	r3, [fp, #-39]	@ zero_extendqisi2
	orr	r3, r3, #16
	strb	r3, [fp, #-39]
	ldrb	r3, [r2, #197]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L8
.L32:
	ldr	r3, [r2, #464]
	cmp	r3, #8
	ldrleb	r3, [fp, #-39]	@ zero_extendqisi2
	orrle	r3, r3, #32
	strleb	r3, [fp, #-39]
	b	.L8
.L35:
	ldrb	r3, [r2, #260]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L13
.L12:
	ldrb	r3, [fp, #-39]	@ zero_extendqisi2
	orr	r3, r3, #16
	strb	r3, [fp, #-39]
	b	.L13
.L34:
	ldr	r3, [r1, #2756]
	add	r3, r3, #1
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	sub	r3, r3, #1
	strh	r3, [fp, #-38]	@ movhi
	b	.L17
.L33:
	add	r1, r4, #20480
	movw	r6, #21846
	movt	r6, 21845
	ldrb	r5, [fp, #-39]	@ zero_extendqisi2
	ldr	r3, [r1, #2756]
	add	r3, r3, #1
	add	r3, r3, r3, lsr #31
	mov	r8, r3, asr #1
	smull	r6, r7, r8, r6
	sub	r3, r7, r3, asr #31
	add	r3, r3, r3, lsl #1
	rsb	r3, r3, r8
	bfi	r5, r3, #2, #2
	strb	r5, [fp, #-39]
	b	.L15
.L31:
	mov	r0, r1
	str	r3, [fp, #-52]
	movt	r0, 63686
	str	r2, [fp, #-48]
	bl	MEM_Phy2Vir
	subs	r1, r0, #0
	ldrne	r3, [fp, #-52]
	ldrne	r2, [fp, #-48]
	strne	r1, [r3, #8]
	bne	.L2
.L3:
	ldr	r3, .L36+4
	ldr	r1, .L36+8
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L4
.L37:
	.align	2
.L36:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	UNWIND(.fnend)
	.size	BPD_CfgReg, .-BPD_CfgReg
	.align	2
	.global	BPD_Reset
	.type	BPD_Reset, %function
BPD_Reset:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r0, #0
	movt	r0, 63686
	bl	MEM_Phy2Vir
	subs	r2, r0, #0
	beq	.L53
	ldr	r7, .L56
	mov	r0, #22
	ldr	r6, .L56+4
	ldr	r1, .L56+8
	ldr	r3, [r7, #68]
	ldr	r5, .L56+12
	blx	r3
	ldr	ip, [r6]
	ldr	r1, [r5, #8]
	ldr	r4, [ip, #136]
	add	r2, r1, #64
	orr	r4, r4, #16
	str	r4, [ip, #136]
	ldr	r3, [r1, #64]
	tst	r3, #65536
	beq	.L40
	movw	r0, #9999
	b	.L41
.L55:
	subs	r0, r0, #1
	beq	.L54
.L41:
	ldr	r3, [r2]
	tst	r3, #65536
	bne	.L55
.L40:
	bfc	r4, #4, #1
	mvn	r3, #1
	str	r4, [ip, #136]
	str	r3, [r1, #52]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L54:
	ldr	r1, .L56+16
	ldr	r3, [r7, #68]
	blx	r3
	ldr	ip, [r6]
	ldr	r1, [r5, #8]
	b	.L40
.L53:
	ldr	r3, .L56
	ldr	r1, .L56+20
	ldr	r3, [r3, #68]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L57:
	.align	2
.L56:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_pstRegCrg
	.word	.LC2
	.word	g_HwMem
	.word	.LC3
	.word	.LC1
	UNWIND(.fnend)
	.size	BPD_Reset, .-BPD_Reset
	.align	2
	.global	BPD_Start
	.type	BPD_Start, %function
BPD_Start:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L59
	mov	r2, #0
	mov	r0, #1
	ldr	r1, [r3, #8]
	str	r2, [r1]
	ldr	r1, [r3, #8]
	str	r0, [r1]
	ldr	r3, [r3, #8]
	str	r2, [r3]
	ldmfd	sp, {fp, sp, pc}
.L60:
	.align	2
.L59:
	.word	g_HwMem
	UNWIND(.fnend)
	.size	BPD_Start, .-BPD_Start
	.align	2
	.global	IsBpd_Ready
	.type	IsBpd_Ready, %function
IsBpd_Ready:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L65
	ldr	r0, [r3, #8]
	cmp	r0, #0
	beq	.L64
	ldr	r0, [r0, #64]
	and	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L64:
	ldr	r1, .L65+4
	ldr	r3, .L65+8
	ldr	r2, .L65+12
	ldr	r4, [r1, #68]
	ldr	r1, .L65+16
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L66:
	.align	2
.L65:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LANCHOR0
	.word	.LC5
	UNWIND(.fnend)
	.size	IsBpd_Ready, .-IsBpd_Ready
	.align	2
	.global	BPDDRV_WaitBpdReadyIfNoIsr
	.type	BPDDRV_WaitBpdReadyIfNoIsr, %function
BPDDRV_WaitBpdReadyIfNoIsr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r6, .L75
	mov	r4, #0
	ldr	r3, [r6]
	blx	r3
	mov	r5, r0
	b	.L70
.L74:
	ldr	r3, [r6]
	blx	r3
	cmp	r0, r5
	movcc	r5, #0
	rsb	r4, r5, r0
	cmp	r4, #4000
	bcs	.L72
.L70:
	bl	IsBpd_Ready
	cmp	r0, #0
	beq	.L74
	cmp	r4, #4000
	bcs	.L72
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L72:
	ldr	r3, [r6, #68]
	mov	r0, #0
	ldr	r1, .L75+4
	blx	r3
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L76:
	.align	2
.L75:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	UNWIND(.fnend)
	.size	BPDDRV_WaitBpdReadyIfNoIsr, .-BPDDRV_WaitBpdReadyIfNoIsr
	.align	2
	.global	BPD_GetParam
	.type	BPD_GetParam, %function
BPD_GetParam:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, .L84
	ldr	r4, [r2, #16]
	ldr	r3, [r2, #24]
	ldr	ip, [ip, #8]
	rsb	r5, r3, r4, lsl #3
	ldr	lr, [ip, #80]
	ldr	ip, [ip, #84]
	cmp	lr, r5
	bcs	.L82
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L83
	and	r0, ip, #15
	ubfx	r3, ip, #8, #4
	str	r0, [r1, #328]
	ubfx	ip, ip, #4, #4
	str	r3, [r1, #332]
	str	ip, [r1, #336]
.L81:
	mov	r1, lr
	mov	r0, r2
	bl	BsLongSkip
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L83:
	ubfx	r3, ip, #0, #4
	ubfx	r0, ip, #12, #4
	strb	r3, [r1, #382]
	ubfx	r3, ip, #16, #4
	strb	r0, [r1, #385]
	ubfx	r0, ip, #20, #4
	strb	r3, [r1, #386]
	ubfx	r3, ip, #8, #4
	strb	r0, [r1, #387]
	ubfx	r0, ip, #24, #4
	strb	r3, [r1, #383]
	ubfx	r3, ip, #4, #4
	strb	r0, [r1, #388]
	ubfx	ip, ip, #28, #2
	strb	r3, [r1, #384]
	strb	ip, [r1, #378]
	b	.L81
.L82:
	ldr	ip, .L84+4
	rsb	r3, r3, r4
	mov	r2, lr
	ldr	r1, .L84+8
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L85:
	.align	2
.L84:
	.word	g_HwMem
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC7
	UNWIND(.fnend)
	.size	BPD_GetParam, .-BPD_GetParam
	.align	2
	.global	BPD_Drv
	.type	BPD_Drv, %function
BPD_Drv:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r1
	add	r1, r1, #20480
	mov	r6, r2
	mov	r7, r0
	ldr	r3, [r1, #2756]
	ldr	r2, [r1, #2752]
	cmp	r3, #2
	ble	.L88
	cmp	r3, #128
	sub	r4, r2, #3
	movle	r1, #0
	movgt	r1, #1
	cmp	r4, #125
	movls	r4, r1
	orrhi	r4, r1, #1
	cmp	r4, #0
	beq	.L89
.L88:
	ldr	ip, .L94
	mov	r3, r3, asl #4
	mov	r2, r2, asl #4
	ldr	r1, .L94+4
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
.L90:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L89:
	ldr	r9, .L94
	mov	r0, #22
	ldr	r8, .L94+8
	ldr	r1, .L94+12
	ldr	r3, [r9, #68]
	blx	r3
	bl	BPD_Reset
	mov	r3, r8
	mov	r2, r6
	mov	r1, r7
	mov	r0, r5
	bl	BPD_CfgReg
	cmn	r0, #1
	beq	.L93
	ldr	r3, [r8, #8]
	mov	r2, #1
	str	r4, [r3]
	ldr	r3, [r8, #8]
	str	r2, [r3]
	ldr	r3, [r8, #8]
	str	r4, [r3]
	bl	BPDDRV_WaitBpdReadyIfNoIsr
	cmp	r0, #0
	bne	.L90
	mov	r2, r7
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	BPD_GetParam
.L93:
	ldr	r3, [r9, #68]
	mov	r0, r4
	ldr	r1, .L94+16
	blx	r3
	b	.L90
.L95:
	.align	2
.L94:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	.word	g_HwMem
	.word	.LC9
	.word	.LC10
	UNWIND(.fnend)
	.size	BPD_Drv, .-BPD_Drv
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.26204, %object
	.size	__func__.26204, 12
__func__.26204:
	.ascii	"IsBpd_Ready\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"BPD register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC1:
	ASCII(.ascii	"VDMHAL_ResetBPD: map BPD register fail, vir(reg) = " )
	ASCII(.ascii	"(%p)\012\000" )
	.space	3
.LC2:
	ASCII(.ascii	"*****************reset BPD!!!!******************\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC3:
	ASCII(.ascii	"Reset BPD Err______________________________________" )
	ASCII(.ascii	"_-\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"BPD register not mapped yet!\000" )
	.space	3
.LC5:
	ASCII(.ascii	"%s: %s\012\000" )
.LC6:
	ASCII(.ascii	"======>>>>> BPD TimeOut!!!\012\000" )
.LC7:
	ASCII(.ascii	" BPD ERROR: EAT TOO MUCH BS %#x, but available bs n" )
	ASCII(.ascii	"um %#x!!!\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"NOT SUPPORT SIZE %d*%d\012\000" )
.LC9:
	ASCII(.ascii	"----------------BPD_V200_DRV\012\000" )
	.space	2
.LC10:
	ASCII(.ascii	"BPD error: no map reg!\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
