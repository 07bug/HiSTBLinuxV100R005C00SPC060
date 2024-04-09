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
	.file	"vdm_hal_avs.c"
	.text
	.align	2
	.type	AVSHAL_V5R6C1_StartDec_ConfigWQMatrix.part.2, %function
AVSHAL_V5R6C1_StartDec_ConfigWQMatrix.part.2:
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
	cmp	r1, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #14592
	add	r1, r1, #1
	add	r0, r0, #32
	mov	lr, #1
.L5:
	tst	lr, #1
	add	lr, lr, #1
	add	r0, r0, #16
	ldrneb	r4, [r0, #-24]	@ zero_extendqisi2
	ldreqb	r4, [r0, #-36]	@ zero_extendqisi2
	ldrneb	r3, [r0, #-16]	@ zero_extendqisi2
	ldreqb	r3, [r0, #-28]	@ zero_extendqisi2
	movne	r4, r4, asl #16
	ldrneb	ip, [r0, #-40]	@ zero_extendqisi2
	moveq	r4, r4, asl #16
	ldrneb	r5, [r0, #-32]	@ zero_extendqisi2
	ldreqb	ip, [r0, #-52]	@ zero_extendqisi2
	orr	r3, r4, r3, asl #24
	ldreqb	r5, [r0, #-44]	@ zero_extendqisi2
	cmp	lr, r1
	orr	r3, r3, ip
	orr	r3, r3, r5, asl #8
	str	r3, [r2], #4
	bne	.L5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVSHAL_V5R6C1_StartDec_ConfigWQMatrix.part.2, .-AVSHAL_V5R6C1_StartDec_ConfigWQMatrix.part.2
	.align	2
	.global	AVSHAL_V5R6C1_StartDec_CheckParam
	.type	AVSHAL_V5R6C1_StartDec_CheckParam, %function
AVSHAL_V5R6C1_StartDec_CheckParam:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	subs	r3, r0, #0
	bgt	.L14
	ldrh	r3, [r1, #60]
	cmp	r3, #512
	bhi	.L13
	ldrh	r3, [r1, #62]
	cmp	r3, #512
	bhi	.L13
	mov	r0, #0
.L11:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L14:
	mov	r0, #0
	ldr	r2, .L15
	str	r0, [sp]
	ldr	r1, .L15+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L11
.L13:
	ldr	r3, .L15+8
	mov	r0, #0
	ldr	r2, .L15
	ldr	r1, .L15+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L11
.L16:
	.align	2
.L15:
	.word	.LANCHOR0
	.word	.LC0
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	AVSHAL_V5R6C1_StartDec_CheckParam, .-AVSHAL_V5R6C1_StartDec_CheckParam
	.align	2
	.global	AVSHAL_V5R6C1_StartDec_GetRegAddr
	.type	AVSHAL_V5R6C1_StartDec_GetRegAddr, %function
AVSHAL_V5R6C1_StartDec_GetRegAddr:
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
	cmp	r0, #0
	bne	.L23
	ldr	r5, .L24
	mov	r3, #0
	movt	r3, 63683
	str	r3, [r1]
	ldr	r4, [r5]
	cmp	r4, #0
	beq	.L20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L20:
	mov	r0, r3
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L22
	str	r3, [r5]
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L23:
	ldr	r1, .L24+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L22:
	ldr	r1, .L24+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L25:
	.align	2
.L24:
	.word	g_HwMem
	.word	.LC3
	.word	.LC4
	UNWIND(.fnend)
	.size	AVSHAL_V5R6C1_StartDec_GetRegAddr, .-AVSHAL_V5R6C1_StartDec_GetRegAddr
	.align	2
	.global	AVSHAL_V5R6C1_StartDec_GetStrmAddr
	.type	AVSHAL_V5R6C1_StartDec_GetStrmAddr, %function
AVSHAL_V5R6C1_StartDec_GetStrmAddr:
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
	add	lr, r0, #12288
	mvn	r2, #0
	str	r2, [r1]
	ldr	r3, [lr, #2148]
	cmp	r3, #0
	movgt	ip, #0
	ble	.L34
.L29:
	ldr	r3, [r0, #100]
	cmp	r3, #0
	beq	.L32
	ldr	r4, [r0, #108]
	bic	r3, r3, #15
	cmp	r4, #0
	ble	.L32
	cmp	r2, r3
	movcs	r2, r3
	str	r2, [r1]
.L32:
	ldr	r3, [r0, #104]
	cmp	r3, #0
	beq	.L30
	ldr	r4, [r0, #112]
	bic	r3, r3, #15
	cmp	r4, #0
	ble	.L30
	cmp	r2, r3
	movcs	r2, r3
	str	r2, [r1]
.L30:
	ldr	r3, [lr, #2148]
	add	ip, ip, #1
	add	r0, r0, #28
	cmp	r3, ip
	bgt	.L29
	cmn	r2, #1
	beq	.L34
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L34:
	mvn	r2, #0
	ldr	r1, .L41
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L42:
	.align	2
.L41:
	.word	.LC5
	UNWIND(.fnend)
	.size	AVSHAL_V5R6C1_StartDec_GetStrmAddr, .-AVSHAL_V5R6C1_StartDec_GetStrmAddr
	.align	2
	.global	AVSHAL_V5R6C1_StartDec_GetModuleLowlyFlag
	.type	AVSHAL_V5R6C1_StartDec_GetModuleLowlyFlag, %function
AVSHAL_V5R6C1_StartDec_GetModuleLowlyFlag:
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
	ldr	r3, .L46
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldrne	r0, [r0, #1208]
	ldmfd	sp, {fp, sp, pc}
.L47:
	.align	2
.L46:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	AVSHAL_V5R6C1_StartDec_GetModuleLowlyFlag, .-AVSHAL_V5R6C1_StartDec_GetModuleLowlyFlag
	.align	2
	.global	AVSHAL_V5R6C1_StartDec_ConfigWQMatrix
	.type	AVSHAL_V5R6C1_StartDec_ConfigWQMatrix, %function
AVSHAL_V5R6C1_StartDec_ConfigWQMatrix:
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
	ldrb	r3, [r0, #41]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSHAL_V5R6C1_StartDec_ConfigWQMatrix.part.2
	UNWIND(.fnend)
	.size	AVSHAL_V5R6C1_StartDec_ConfigWQMatrix, .-AVSHAL_V5R6C1_StartDec_ConfigWQMatrix
	.align	2
	.global	AVSHAL_V5R6C1_WirteSlicMsg
	.type	AVSHAL_V5R6C1_WirteSlicMsg, %function
AVSHAL_V5R6C1_WirteSlicMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	ip, .L79
	movw	r3, #1228
	mov	r10, r0
	add	r6, r0, #100
	str	r1, [fp, #-48]
	mla	r2, r3, r2, ip
	ldr	r7, [r2, #56]
	add	r4, r7, #320
	mov	r0, r7
	bl	MEM_Phy2Vir
	ldr	r3, [r10, #116]
	cmp	r3, #0
	add	r5, r0, #320
	beq	.L51
	ldr	r3, [r10, #100]
	add	r7, r7, #576
	ldr	r2, [fp, #-48]
	add	r3, r3, #4
	rsb	r3, r2, r3
	and	r2, r3, #15
	bic	r3, r3, #15
	mov	r2, r2, asl #3
	cmp	r2, #7
	addls	r2, r2, #120
	subhi	r2, r2, #8
	subls	r3, r3, #4
	mov	r2, r2, asl #25
	bic	r3, r3, #-16777216
	orr	r2, r2, #8
	str	r2, [r0, #320]
	str	r3, [r0, #324]
	mov	r2, #0
	str	r2, [r0, #328]
	mov	r3, #1
	str	r2, [r0, #332]
	ldr	r2, [r10, #116]
	sub	r2, r2, #1
	mov	r2, r2, asl #16
	str	r2, [r0, #336]
	str	r7, [r0, #572]
.L51:
	add	r8, r10, #12288
	ldr	r2, [r8, #2148]
	cmp	r2, #0
	ble	.L50
	mov	r0, #0
	add	r3, r4, r3, lsl #8
	mov	r7, r0
	str	r3, [fp, #-56]
	mov	r3, r0
	str	r10, [fp, #-52]
.L70:
	cmp	r7, #512
	bge	.L55
	mov	r9, r3, asl #2
	mov	r4, r3, asl #5
	cmp	r3, #0
	rsb	r1, r9, r4
	add	r1, r6, r1
	ble	.L57
	ldr	ip, [r1, #16]
	ldr	r2, [r1, #-12]
	cmp	ip, r2
	bls	.L58
.L57:
	ldr	r2, [r1]
	ldr	ip, [fp, #-48]
	ldr	r0, [r1, #8]
	add	r2, r2, #4
	ldr	lr, [r1, #4]
	rsb	r2, ip, r2
	and	ip, r2, #15
	sub	r0, r0, #4
	cmp	lr, #0
	bic	r2, r2, #15
	mov	r0, r0, asl #3
	mov	ip, ip, asl #3
	beq	.L78
	rsb	r4, r9, r4
	ldr	r9, [fp, #-52]
	add	r4, r9, r4
	ldr	r4, [r4, #112]
	cmp	r4, #0
	ble	.L74
	ldr	r4, [fp, #-48]
	cmp	r0, #0
	rsb	lr, r4, lr
	and	r4, lr, #15
	bic	r10, lr, #15
	mov	r9, r4, asl #3
	ldr	r4, [r1, #12]
	mov	r4, r4, asl #3
	beq	.L75
	bic	r4, r4, #-33554432
	bic	lr, lr, #-16777216
	orr	r4, r4, r9, asl #25
	bic	lr, lr, #15
.L59:
	cmp	ip, #7
	add	r9, r0, #8
	addls	r10, ip, #120
	subhi	r10, ip, #8
	bic	r9, r9, #-33554432
	mov	ip, r3, asl #8
	orr	r9, r9, r10, asl #25
	add	r0, ip, #4
	str	r9, [r5, r3, asl #8]
	add	r10, ip, #8
	add	r9, ip, #12
	subls	r2, r2, #4
	bic	r2, r2, #-16777216
	str	r2, [r5, r0]
	str	r4, [r5, r10]
	add	r0, r3, #1
	str	lr, [r5, r9]
	ldr	r2, [r8, #2148]
	cmp	r0, r2
	ldrge	r1, [r1, #16]
	bge	.L63
	mov	r3, r0, asl #5
	ldr	r1, [r1, #16]
	sub	r3, r3, r0, asl #2
	add	lr, r6, r3
	ldr	lr, [lr, #16]
	cmp	r1, lr
	bcc	.L63
	sub	r3, r3, #28
	add	r3, r6, r3
	b	.L64
.L66:
	ldr	lr, [r3, #44]
	cmp	lr, r1
	bhi	.L68
.L64:
	add	r0, r0, #1
	add	r3, r3, #28
	cmp	r0, r2
	bne	.L66
.L67:
	ldr	lr, [fp, #-52]
	mov	r0, r2
	ldrh	r3, [lr, #60]
	ldrh	r2, [lr, #62]
	mov	lr, #0
	mul	r3, r2, r3
	sub	r3, r3, #1
.L69:
	add	r2, ip, #16
	add	r7, r7, #1
	add	ip, ip, #252
	uxth	r1, r1
	orr	r3, r1, r3, asl #16
	str	r3, [r5, r2]
	str	lr, [r5, ip]
.L55:
	sub	r3, r0, #1
.L58:
	ldr	r2, [r8, #2148]
	add	r3, r3, #1
	cmp	r2, r3
	bgt	.L70
.L50:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L63:
	cmp	r0, r2
	beq	.L67
.L68:
	mov	r3, r0, asl #5
	ldr	r2, [fp, #-56]
	sub	r3, r3, r0, asl #2
	add	r3, r6, r3
	add	lr, r2, r0, lsl #8
	ldr	r3, [r3, #16]
	sub	r3, r3, #1
	b	.L69
.L75:
	mov	lr, #0
	mov	r2, r10
	mov	r0, r4
	mov	ip, r9
.L78:
	mov	r4, lr
	b	.L59
.L74:
	mov	lr, #0
	mov	r4, lr
	b	.L59
.L80:
	.align	2
.L79:
	.word	g_HwMem
	UNWIND(.fnend)
	.size	AVSHAL_V5R6C1_WirteSlicMsg, .-AVSHAL_V5R6C1_WirteSlicMsg
	.align	2
	.global	AVSHAL_V5R6C1_StartDec
	.type	AVSHAL_V5R6C1_StartDec, %function
AVSHAL_V5R6C1_StartDec:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r7, .L105
	mov	r4, r0
	mov	r6, r2
	mov	r0, #0
	rsb	r2, r0, r2
	ldrb	ip, [r7]	@ zero_extendqisi2
	clz	r2, r2
	mov	r5, r1
	ldr	r3, .L105+4
	cmp	ip, #1
	mov	r1, r1, asl #6
	mov	r2, r2, lsr #5
	sub	r1, r1, r5, asl #3
	add	r3, r3, r1
	moveq	r2, #0
	cmp	r2, r0
	str	r0, [fp, #-52]
	ldr	r8, [r3, #8]
	str	r0, [fp, #-48]
	bne	.L101
	mov	r1, r4
	mov	r0, r5
	bl	AVSHAL_V5R6C1_StartDec_CheckParam
	cmp	r0, #0
	bne	.L85
	sub	r1, fp, #48
	mov	r0, r5
	bl	AVSHAL_V5R6C1_StartDec_GetRegAddr
	subs	r3, r0, #0
	str	r3, [fp, #-64]
	bne	.L85
	ldr	r3, .L105+8
	sub	r1, fp, #52
	mov	r0, r4
	ldr	r3, [r3, r8, asl #2]
	cmp	r3, #0
	ldrne	r3, [r3, #1208]
	strne	r3, [fp, #-64]
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #1
	ldrneb	r3, [fp, #-64]	@ zero_extendqisi2
	strneb	r3, [r6, #1]
	bl	AVSHAL_V5R6C1_StartDec_GetStrmAddr
	subs	r10, r0, #0
	bne	.L85
	ldrh	lr, [r4, #60]
	mov	ip, r10
	ldrh	r1, [r4, #62]
	mov	r3, r6
	add	r7, r4, #12288
	mov	r2, r5
	mov	r0, #8
	mul	r1, r1, lr
	sub	r1, r1, #1
	bfi	ip, r1, #0, #20
	str	ip, [fp, #-56]
	mov	r1, ip, lsr #24
	ubfx	ip, ip, #16, #8
	orr	r1, r1, #64
	orr	ip, ip, #64
	bfi	r1, r10, #7, #1
	bfi	ip, r10, #7, #1
	strb	ip, [fp, #-54]
	uxtb	r1, r1
	orr	r1, r1, #1
	bfi	r1, r10, #1, #1
	strb	r1, [fp, #-53]
	ldr	r8, [fp, #-56]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L105+12
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r2, [r7, #2608]
	ldrb	r0, [r4, #16]	@ zero_extendqisi2
	mov	r3, #0
	mov	r1, #12288	@ movhi
	bfi	r3, r2, #4, #1
	mov	r2, #1
	bfi	r1, r2, #0, #12
	ldrh	ip, [r4, #60]
	cmp	r0, #3
	cmpne	r0, #1
	uxth	r2, r1
	bfi	r3, r10, #5, #1
	strh	r1, [fp, #-54]	@ movhi
	movls	r0, #1
	ldr	r1, [fp, #-64]
	movhi	r0, #0
	uxtb	r3, r3
	cmp	ip, #120
	mov	r2, r2, lsr #8
	orr	r3, r3, #64
	bfi	r2, r1, #4, #1
	bfi	r3, r0, #7, #1
	strb	r2, [fp, #-53]
	mov	ip, #0
	strb	r3, [fp, #-55]
	mov	r3, #6
	strb	r3, [fp, #-56]
	uxtble	r3, r2
	ldrgtb	r3, [fp, #-53]	@ zero_extendqisi2
	movle	r2, r10
	ldrgt	r2, [r7, #2604]
	mov	r0, #12
	strle	r10, [r7, #2604]
	bfi	r3, r10, #5, #1
	strb	r3, [fp, #-53]
	andgt	r2, r2, #1
	ldrb	r1, [fp, #-53]	@ zero_extendqisi2
	mov	r3, r6
	strb	ip, [r4, #48]
	movw	r8, #3075
	bfi	r1, r2, #6, #1
	mov	r2, r5
	bfi	r1, ip, #7, #1
	strb	r1, [fp, #-53]
	ldr	r9, [fp, #-56]
	movt	r8, 48
	mov	r1, r9
	bl	MFDE_ConfigReg
	mov	r2, r9
	ldr	r1, .L105+16
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r3, .L105+20
	movw	r9, #1228
	mov	r2, r5
	mov	r0, #16
	mla	r9, r9, r5, r3
	mov	r3, r6
	ldr	r1, [r9, #56]
	bic	r1, r1, #15
	str	r1, [fp, #-68]
	bl	MFDE_ConfigReg
	ldr	r2, [fp, #-68]
	ldr	r1, .L105+24
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r9, [r9, #40]
	mov	r3, r6
	mov	r2, r5
	bic	r9, r9, #15
	mov	r0, #20
	mov	r1, r9
	bl	MFDE_ConfigReg
	mov	r2, r9
	ldr	r1, .L105+28
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r9, [fp, #-52]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #24
	mov	r1, r9
	bl	MFDE_ConfigReg
	mov	r2, r9
	ldr	r1, .L105+32
	mov	r0, #3
	bl	dprint_vfmw
	ldrh	r1, [r4, #60]
	mov	r3, r6
	mov	r2, r5
	cmp	r1, #120
	mov	r0, #4
	movhi	r1, #0
	movls	r1, #1
	bl	SCD_ConfigReg
	mov	r1, r8
	mov	r3, r6
	mov	r2, r5
	mov	r0, #60
	str	r8, [fp, #-56]
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r8
	mov	r0, #64
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r8
	mov	r0, #68
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r8
	mov	r0, #72
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r8
	mov	r0, #76
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r8
	mov	r0, #80
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r8
	mov	r0, #84
	bl	MFDE_ConfigReg
	ldr	r3, [fp, #-64]
	cmp	r3, #1
	beq	.L102
.L90:
	ldr	r8, [r7, #2164]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #96
	bic	r8, r8, #15
	mvn	r9, #0
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L105+36
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r8, [r7, #2568]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #100
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L105+40
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r8, [r7, #2576]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #104
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L105+44
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r8, [r7, #2584]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #108
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L105+48
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r3, .L105+20
	movw	r8, #1228
	mov	r2, r5
	mov	r0, #144
	mla	r8, r8, r5, r3
	mov	r3, r6
	ldr	r1, [r8, #1204]
	str	r1, [fp, #-64]
	bl	MFDE_ConfigReg
	ldr	r2, [fp, #-64]
	mov	r0, #3
	ldr	r1, .L105+52
	bl	dprint_vfmw
	mov	r3, r6
	mov	r2, r5
	mov	r1, #0
	mov	r0, #148
	bl	MFDE_ConfigReg
	mov	r2, #0
	ldr	r1, .L105+56
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r6
	mov	r2, r5
	mov	r1, #0
	mov	r0, #152
	bl	MFDE_ConfigReg
	mov	r2, #0
	ldr	r1, .L105+60
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r6
	mov	r1, r9
	mov	r2, r5
	mov	r0, #32
	str	r9, [fp, #-56]
	bl	MFDE_ConfigReg
	ldr	r0, [r8, #56]
	bl	MEM_Phy2Vir
	subs	r6, r0, #0
	beq	.L103
	ldrh	r2, [r4, #62]
	mov	r0, #4
	ldrh	r3, [fp, #-54]
	mov	r9, #0
	ldrh	r1, [r4, #60]
	sub	r2, r2, #1
	bfi	r3, r2, #0, #9
	ldrh	r2, [fp, #-56]
	ldrb	ip, [r4, #40]	@ zero_extendqisi2
	sub	r1, r1, #1
	strh	r3, [fp, #-54]	@ movhi
	bfi	r2, r1, #0, #9
	mov	r3, r3, lsr #8
	ldrb	r1, [r4, #39]	@ zero_extendqisi2
	bfi	r3, ip, #1, #2
	strh	r2, [fp, #-56]	@ movhi
	bfi	r3, r1, #3, #2
	mov	r2, r2, lsr #8
	bfc	r3, #5, #3
	bfc	r2, #1, #7
	strb	r3, [fp, #-53]
	strb	r2, [fp, #-55]
	ldr	r2, [fp, #-56]
	ldr	r1, .L105+64
	str	r2, [r6]
	bl	dprint_vfmw
	ldrb	r3, [r4, #25]	@ zero_extendqisi2
	ldrb	r1, [r4, #17]	@ zero_extendqisi2
	mov	r0, #4
	and	r3, r3, #1
	ldrb	r2, [r4, #19]	@ zero_extendqisi2
	bfi	r3, r1, #1, #2
	ldrb	r1, [r4, #16]	@ zero_extendqisi2
	ldrb	ip, [r4, #18]	@ zero_extendqisi2
	and	r2, r2, #1
	bfi	r3, r1, #3, #2
	ldrb	r1, [r4, #24]	@ zero_extendqisi2
	bfi	r2, ip, #1, #1
	ldrb	ip, [r4, #21]	@ zero_extendqisi2
	bfi	r3, r1, #5, #1
	ldrb	r1, [r4, #23]	@ zero_extendqisi2
	uxtb	r2, r2
	str	r9, [fp, #-56]
	orr	r2, r2, r0
	bfi	r3, r1, #6, #1
	strb	r2, [fp, #-54]
	and	r2, ip, #63
	ldrb	r1, [r4, #22]	@ zero_extendqisi2
	ldrb	ip, [r4, #20]	@ zero_extendqisi2
	bfi	r3, r1, #7, #1
	strb	r3, [fp, #-56]
	bfi	r2, ip, #6, #1
	ldrb	r3, [r4, #31]	@ zero_extendqisi2
	ldrh	ip, [fp, #-54]
	bfi	r2, r3, #7, #1
	strb	r2, [fp, #-55]
	bfi	ip, r9, #3, #13
	strh	ip, [fp, #-54]	@ movhi
	ldr	r2, [fp, #-56]
	ldr	r1, .L105+68
	str	r2, [r6, #4]
	bl	dprint_vfmw
	ldrb	r3, [r4, #29]	@ zero_extendqisi2
	ldrb	r2, [r4, #28]	@ zero_extendqisi2
	mov	r0, #4
	ldrb	r1, [r4, #27]	@ zero_extendqisi2
	and	r3, r3, #1
	bfi	r3, r2, #1, #1
	str	r9, [fp, #-56]
	ldrb	r2, [r4, #26]	@ zero_extendqisi2
	bfi	r3, r1, #2, #5
	strb	r3, [fp, #-56]
	ldrh	r3, [fp, #-56]
	ldr	r1, .L105+72
	bfi	r3, r2, #7, #5
	strh	r3, [fp, #-56]	@ movhi
	ldr	r2, [fp, #-56]
	str	r2, [r6, #8]
	bl	dprint_vfmw
	ldrb	r3, [r4, #34]	@ zero_extendqisi2
	ldrb	r2, [r4, #35]	@ zero_extendqisi2
	mov	r0, #4
	ldrb	r1, [r4, #36]	@ zero_extendqisi2
	and	r3, r3, #1
	bfi	r3, r2, #1, #2
	ldrb	r2, [r4, #37]	@ zero_extendqisi2
	bfi	r3, r1, #3, #1
	ldrb	r1, [r4, #32]	@ zero_extendqisi2
	bfi	r3, r2, #4, #2
	str	r9, [fp, #-56]
	ldrb	r2, [r4, #33]	@ zero_extendqisi2
	bfi	r3, r1, #6, #1
	strb	r3, [fp, #-56]
	ldrh	r3, [fp, #-56]
	ldr	r1, .L105+76
	bfi	r3, r2, #7, #2
	strh	r3, [fp, #-56]	@ movhi
	ldr	r2, [fp, #-56]
	bfi	r2, r9, #9, #23
	str	r2, [fp, #-56]
	str	r2, [r6, #12]
	bl	dprint_vfmw
	ldr	r2, [r7, #2152]
	ldr	r1, .L105+80
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r6, #16]
	bl	dprint_vfmw
	ldr	r2, [r7, #2156]
	ldr	r1, .L105+84
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r6, #20]
	bl	dprint_vfmw
	ldr	r2, [r7, #2160]
	ldr	r1, .L105+88
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r6, #24]
	bl	dprint_vfmw
	ldr	r2, [r7, #2176]
	ldr	r1, .L105+92
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r6, #28]
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	ldrb	r1, [r4, #30]	@ zero_extendqisi2
	mov	r2, #0
	str	r9, [fp, #-56]
	bfi	r2, r3, #0, #1
	mov	r3, #0
	strb	r2, [fp, #-56]
	bfi	r3, r1, #0, #2
	strb	r3, [fp, #-53]
	ldr	r2, [fp, #-56]
	mov	r0, #4
	ldr	r1, .L105+96
	str	r2, [r6, #32]
	bl	dprint_vfmw
	ldr	r2, [r4, #76]
	ldr	r1, .L105+100
	mov	r0, #4
	str	r2, [r6, #36]
	bl	dprint_vfmw
	ldr	r3, [r4, #92]
	ldr	r1, [r4, #84]
	mov	r2, r9
	bfi	r2, r3, #0, #24
	mov	r3, #0
	str	r2, [fp, #-56]
	bfi	r3, r1, #0, #7
	strb	r3, [fp, #-53]
	mov	r0, #4
	ldr	r2, [fp, #-56]
	ldr	r1, .L105+104
	str	r2, [r6, #40]
	bl	dprint_vfmw
	ldr	r2, [r4, #80]
	ldr	r1, .L105+108
	mov	r0, #4
	str	r2, [r6, #44]
	bl	dprint_vfmw
	ldrb	r2, [r4, #41]	@ zero_extendqisi2
	ldrb	ip, [r4, #42]	@ zero_extendqisi2
	mov	r1, #0
	ldrb	r3, [r4, #43]	@ zero_extendqisi2
	and	r2, r2, #1
	ldrb	r0, [r4, #45]	@ zero_extendqisi2
	bfi	r2, ip, #1, #1
	ldrb	ip, [r4, #44]	@ zero_extendqisi2
	and	r3, r3, #63
	bfi	r3, r0, #6, #1
	ldrb	r0, [r4, #46]	@ zero_extendqisi2
	bfi	r2, ip, #2, #6
	ldrb	ip, [r4, #47]	@ zero_extendqisi2
	bfi	r3, r0, #7, #1
	str	r9, [fp, #-56]
	bfi	r1, ip, #0, #1
	strb	r3, [fp, #-55]
	strb	r1, [fp, #-54]
	mov	r0, #4
	strb	r2, [fp, #-56]
	ldr	r2, [fp, #-56]
	ldr	r1, .L105+112
	str	r2, [r6, #48]
	bl	dprint_vfmw
	ldr	r2, [r8, #1148]
	ldr	r1, .L105+116
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r6, #52]
	bl	dprint_vfmw
	ldr	r2, [r8, #1152]
	ldr	r1, .L105+120
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r6, #56]
	bl	dprint_vfmw
	ldr	r2, [r7, #2172]
	ldr	r1, .L105+124
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r6, #64]
	bl	dprint_vfmw
	add	r3, r4, #14464
	add	r0, r4, #14592
	add	r3, r3, #4
	add	r0, r0, #4
	add	r2, r6, #68
.L92:
	ldr	r1, [r3, #4]!
	cmp	r3, r0
	str	r1, [r2], #4
	bne	.L92
	ldr	r2, [r7, #2168]
	mov	r0, #4
	ldr	r1, .L105+128
	movw	r7, #1228
	bic	r2, r2, #15
	str	r2, [r6, #196]
	bl	dprint_vfmw
	ldr	r3, .L105+20
	ldr	r1, .L105+132
	mov	r0, #4
	mla	r7, r7, r5, r3
	ldr	r2, [r7, #1160]
	bic	r2, r2, #15
	str	r2, [r6, #200]
	bl	dprint_vfmw
	ldr	r2, [r7, #1144]
	ldr	r1, .L105+136
	mov	r0, #4
	bic	r2, r2, #15
	str	r2, [r6, #228]
	bl	dprint_vfmw
	ldr	r2, [r7, #56]
	ldr	r1, .L105+140
	mov	r0, #4
	add	r2, r2, #320
	str	r2, [r6, #252]
	str	r2, [fp, #-56]
	bl	dprint_vfmw
	ldrb	r3, [r4, #41]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L104
.L93:
	mov	r2, r5
	mov	r0, r4
	ldr	r1, [fp, #-52]
	bl	AVSHAL_V5R6C1_WirteSlicMsg
.L83:
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L85:
	mvn	r10, #0
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L104:
	add	r2, r6, #256
	mov	r1, #16
	mov	r0, r4
	bl	AVSHAL_V5R6C1_StartDec_ConfigWQMatrix.part.2
	b	.L93
.L102:
	mov	r3, r6
	mov	r2, r5
	mov	r1, #60
	mov	r0, #92
	bl	MFDE_ConfigReg
	mov	r2, #60
	ldr	r1, .L105+144
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r8, [r7, #2572]
	mov	r2, r5
	mov	r3, r6
	mov	r0, #112
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L105+148
	mov	r0, #3
	bl	dprint_vfmw
	b	.L90
.L103:
	ldr	r3, .L105+152
	mov	r10, r9
	ldr	r2, .L105+156
	ldr	r1, .L105+160
	bl	dprint_vfmw
	b	.L83
.L101:
	mov	r3, r6
	ldr	r2, .L105+156
	ldr	r1, .L105+164
	mvn	r10, #0
	bl	dprint_vfmw
	b	.L83
.L106:
	.align	2
.L105:
	.word	g_HalDisable
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LC7
	.word	.LC8
	.word	g_HwMem
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LC17
	.word	.LC18
	.word	.LC19
	.word	.LC20
	.word	.LC22
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LC29
	.word	.LC30
	.word	.LC31
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC35
	.word	.LC36
	.word	.LC37
	.word	.LC38
	.word	.LC39
	.word	.LC40
	.word	.LC41
	.word	.LC12
	.word	.LC13
	.word	.LC21
	.word	.LANCHOR0+36
	.word	.LC2
	.word	.LC6
	UNWIND(.fnend)
	.size	AVSHAL_V5R6C1_StartDec, .-AVSHAL_V5R6C1_StartDec
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14635, %object
	.size	__func__.14635, 34
__func__.14635:
	.ascii	"AVSHAL_V5R6C1_StartDec_CheckParam\000"
	.space	2
	.type	__func__.14686, %object
	.size	__func__.14686, 23
__func__.14686:
	.ascii	"AVSHAL_V5R6C1_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"%s: VdhId(%d) > %d\012\000" )
.LC1:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC2:
	ASCII(.ascii	"%s: %s\012\000" )
.LC3:
	ASCII(.ascii	"VdhId is wrong! AVSHAL_V200R003_StartDec\012\000" )
	.space	2
.LC4:
	ASCII(.ascii	"vdm register virtual address not mapped, reset fail" )
	ASCII(.ascii	"ed!\012\000" )
.LC5:
	ASCII(.ascii	"stream_base_addr = %#x\012\000" )
.LC6:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"BASIC_V5R6C1_CFG0 = 0x%x\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"BASIC_V5R6C1_CFG1 = 0x%x\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"AVM_V5R6C1_ADDR = 0x%x\012\000" )
.LC10:
	ASCII(.ascii	"VAM_V5R6C1_ADDR = 0x%x\012\000" )
.LC11:
	ASCII(.ascii	"STREAM_V5R6C1_BASE_ADDR = 0x%x\012\000" )
.LC12:
	ASCII(.ascii	"VREG_V200R003_PART_DEC_OVER_INT_LEVEL=0x%x\012\000" )
.LC13:
	ASCII(.ascii	"VREG_LINE_NUM_STADDR = 0x%x\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"YSTADDR_V5R6C1_1D = 0x%x\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"YSTRIDE_V5R6C1_1D = 0x%x\012\000" )
	.space	2
.LC16:
	ASCII(.ascii	"UVOFFSET_V5R6C1_1D = 0x%x\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"HEAD_INF_OFFSET = 0x%x\012\000" )
.LC18:
	ASCII(.ascii	"VREG_V5R6C1_DNR_MBINFO_STADDR = 0x%x\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"VREG_V200R003_REF_PIC_TYPE = 0x%x\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"VREG_V5R6C1_FF_APT_EN = 0x%x\012\000" )
	.space	2
.LC21:
	ASCII(.ascii	"can not map down msg virtual address!\000" )
	.space	2
.LC22:
	ASCII(.ascii	"D0 = 0x%x\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"D1 = 0x%x\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"D2 = 0x%x\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"D3 = 0x%x\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"D4 = 0x%x\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"D5 = 0x%x\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"D6 = 0x%x\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"D7 = 0x%x\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"D8 = 0x%x\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"D9 = 0x%x\012\000" )
	.space	1
.LC32:
	ASCII(.ascii	"D10 = 0x%x\012\000" )
.LC33:
	ASCII(.ascii	"D11 = 0x%x\012\000" )
.LC34:
	ASCII(.ascii	"D12 = 0x%x\012\000" )
.LC35:
	ASCII(.ascii	"D13 = 0x%x\012\000" )
.LC36:
	ASCII(.ascii	"D14 = 0x%x\012\000" )
.LC37:
	ASCII(.ascii	"D16 = 0x%x\012\000" )
.LC38:
	ASCII(.ascii	"D49 = 0x%x\012\000" )
.LC39:
	ASCII(.ascii	"D50 = 0x%x\012\000" )
.LC40:
	ASCII(.ascii	"D57 = 0x%x\012\000" )
.LC41:
	ASCII(.ascii	"D63 = 0x%x\012\000" )
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
