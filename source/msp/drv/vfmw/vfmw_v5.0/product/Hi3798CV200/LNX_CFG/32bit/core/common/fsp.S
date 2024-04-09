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
	.file	"fsp.c"
	.text
	.align	2
	.type	FSP_ClearContext, %function
FSP_ClearContext:
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
	subs	r5, r0, #0
	beq	.L5
	ldr	r6, .L6
	mov	r4, #0
	mov	r0, #8
	ldr	r3, [r6, #12]
	blx	r3
	strb	r4, [r5, #2]
	strb	r4, [r5, #4]
	mov	r1, r4
	strb	r4, [r5, #5]
	mov	r2, #20
	strb	r4, [r5, #3]
	add	r0, r5, #36
	str	r4, [r5, #12]
	str	r4, [r5, #8]
	str	r4, [r5, #16]
	str	r4, [r5, #20]
	str	r4, [r5, #24]
	str	r4, [r5, #32]
	ldr	r3, [r6, #48]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r1, r4
	mov	r2, #88
	add	r0, r5, #56
	blx	r3
	add	r0, r5, #21760
	ldr	r3, [r6, #48]
	mov	r1, r4
	mov	r2, #2816
	add	r0, r0, #144
	blx	r3
	add	r0, r5, #24576
	ldr	r3, [r6, #48]
	mov	r1, r4
	mov	r2, #2816
	add	r0, r0, #144
	blx	r3
	add	r0, r5, #27392
	ldr	r3, [r6, #48]
	mov	r1, r4
	mov	r2, #256
	add	r0, r0, #144
	blx	r3
	ldr	r3, [r6, #16]
	mov	r0, #8
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5:
	ldr	r3, .L6+4
	mov	r2, #132
	ldr	r1, .L6+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L7:
	.align	2
.L6:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_ClearContext, .-FSP_ClearContext
	.align	2
	.global	FSP_Init
	.type	FSP_Init, %function
FSP_Init:
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
	ldr	r3, .L9
	mov	r2, #128
	mov	r1, #0
	ldr	r0, .L9+4
	ldr	r3, [r3, #48]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L10:
	.align	2
.L9:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_Init, .-FSP_Init
	.align	2
	.global	FSP_ConfigAttribute
	.type	FSP_ConfigAttribute, %function
FSP_ConfigAttribute:
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
	cmp	r0, #31
	bhi	.L15
	ldr	r3, .L17
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #28]
	cmp	r2, #1
	bne	.L16
	ldrb	r2, [r1]	@ zero_extendqisi2
	mov	r0, #0
	strb	r2, [r3, #1]
	ldmfd	sp, {fp, sp, pc}
.L16:
	ldr	r3, .L17+4
	movw	r2, #349
	ldr	r1, .L17+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L15:
	ldr	r3, .L17+12
	mov	r2, #348
	ldr	r1, .L17+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L18:
	.align	2
.L17:
	.word	.LANCHOR0
	.word	.LC3
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	FSP_ConfigAttribute, .-FSP_ConfigAttribute
	.align	2
	.global	FSP_ClearContextAll
	.type	FSP_ClearContextAll, %function
FSP_ClearContextAll:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L23
	ldr	r3, .L25
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L24
	ldr	r3, .L25+4
	movw	r2, #27792
	ldrb	r7, [r4, #3]	@ zero_extendqisi2
	mov	r1, #0
	ldrb	r6, [r4, #5]	@ zero_extendqisi2
	mov	r0, r4
	ldrb	r10, [r4]	@ zero_extendqisi2
	ldrb	r9, [r4, #1]	@ zero_extendqisi2
	ldr	r8, [r4, #28]
	ldr	r5, [r4, #32]
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, #0
	strb	r10, [r4]
	strb	r9, [r4, #1]
	str	r8, [r4, #28]
	strb	r7, [r4, #3]
	strb	r6, [r4, #5]
	str	r5, [r4, #32]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L23:
	ldr	r3, .L25+8
	movw	r2, #369
	ldr	r1, .L25+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L24:
	mov	r0, r4
	ldr	r3, .L25+16
	movw	r2, #370
	ldr	r1, .L25+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L26:
	.align	2
.L25:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_ClearContextAll, .-FSP_ClearContextAll
	.align	2
	.global	FSP_EnableInstance
	.type	FSP_EnableInstance, %function
FSP_EnableInstance:
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
	cmp	r0, #31
	mov	r5, r0
	mov	r4, r1
	bhi	.L31
	ldr	r7, .L33
	ldr	r6, [r7, r0, asl #2]
	cmp	r6, #0
	bne	.L32
	ldr	r3, .L33+4
	movw	r2, #27792
	mov	r1, r6
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
	strb	r5, [r4]
	mov	r3, #1
	str	r6, [r4, #32]
	str	r3, [r4, #28]
	mov	r0, r6
	str	r4, [r7, r5, asl #2]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L32:
	ldr	r3, .L33+8
	mov	r2, #396
	ldr	r1, .L33+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L31:
	ldr	r3, .L33+16
	movw	r2, #395
	ldr	r1, .L33+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L34:
	.align	2
.L33:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	FSP_EnableInstance, .-FSP_EnableInstance
	.align	2
	.global	FSP_DisableInstance
	.type	FSP_DisableInstance, %function
FSP_DisableInstance:
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
	cmp	r0, #31
	bhi	.L39
	ldr	r2, .L41
	ldr	r3, [r2, r0, asl #2]
	cmp	r3, #0
	beq	.L40
	ldr	r1, [r3, #28]
	cmp	r1, #1
	moveq	r1, #0
	streq	r1, [r3, #28]
	mov	r3, #0
	str	r3, [r2, r0, asl #2]
	ldmfd	sp, {fp, sp, pc}
.L39:
	ldr	r3, .L41+4
	mov	r2, #412
	ldr	r1, .L41+8
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L40:
	mov	r0, r3
	movw	r2, #413
	ldr	r3, .L41+12
	ldr	r1, .L41+8
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L42:
	.align	2
.L41:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_DisableInstance, .-FSP_DisableInstance
	.align	2
	.global	FSP_Exit
	.type	FSP_Exit, %function
FSP_Exit:
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
	ldr	r5, .L54
	mov	r4, #0
	b	.L45
.L44:
	add	r4, r4, #1
	cmp	r4, #32
	beq	.L53
.L45:
	ldr	r3, [r5, #4]!
	cmp	r3, #0
	beq	.L44
	ldr	r3, [r3, #28]
	cmp	r3, #0
	beq	.L44
	mov	r0, r4
	add	r4, r4, #1
	bl	FSP_DisableInstance
	cmp	r4, #32
	bne	.L45
.L53:
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L55:
	.align	2
.L54:
	.word	.LANCHOR0-4
	UNWIND(.fnend)
	.size	FSP_Exit, .-FSP_Exit
	.align	2
	.global	FSP_ResetInstance
	.type	FSP_ResetInstance, %function
FSP_ResetInstance:
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
	cmp	r0, #31
	bhi	.L60
	ldr	r3, .L62
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L61
	bl	FSP_ClearContext
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L60:
	ldr	r3, .L62+4
	movw	r2, #431
	ldr	r1, .L62+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L61:
	ldr	r3, .L62+12
	mov	r2, #432
	ldr	r1, .L62+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L63:
	.align	2
.L62:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_ResetInstance, .-FSP_ResetInstance
	.align	2
	.global	FSP_ConfigInstance
	.type	FSP_ConfigInstance, %function
FSP_ConfigInstance:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #31
	bhi	.L74
	cmp	r1, #0
	beq	.L75
	ldr	r3, .L77
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L68
	ldr	r3, [r4, #28]
	cmp	r3, #1
	bne	.L68
	ldr	r3, .L77+4
	ldr	r3, [r3, r0, asl #2]
	add	r3, r3, #290816
	ldr	r3, [r3, #1104]
	cmp	r3, #0
	beq	.L76
.L70:
	ldr	r3, .L77+8
	add	r0, r4, #36
	mov	r2, #20
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
.L66:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L76:
	mov	r0, r4
	str	r1, [fp, #-24]
	bl	FSP_ClearContext
	ldr	r1, [fp, #-24]
	b	.L70
.L68:
	ldr	r3, .L77+12
	movw	r2, #570
	ldr	r1, .L77+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L66
.L74:
	ldr	r3, .L77+20
	movw	r2, #567
	ldr	r1, .L77+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L66
.L75:
	mov	r0, r1
	ldr	r3, .L77+24
	mov	r2, #568
	ldr	r1, .L77+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L66
.L78:
	.align	2
.L77:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC7
	.word	.LC1
	.word	.LC2
	.word	.LC6
	UNWIND(.fnend)
	.size	FSP_ConfigInstance, .-FSP_ConfigInstance
	.align	2
	.global	FSP_ConfigFrameBuf
	.type	FSP_ConfigFrameBuf, %function
FSP_ConfigFrameBuf:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #60)
	sub	sp, sp, #60
	str	r2, [fp, #-48]
	ldr	r2, .L127
	mov	r10, r0
	ldr	r4, .L127+4
	mov	r9, r1
	mov	r1, #0
	str	r3, [fp, #-76]
	ldr	r5, [r2, #48]
	add	r0, r4, #128
	mov	r2, #1232
	blx	r5
	cmp	r10, #31
	bhi	.L120
	ldr	r5, [r4, r10, asl #2]
	cmp	r5, #0
	beq	.L121
	ldr	r3, .L127+8
	ldr	r0, [r5, #40]
	ldr	ip, [r5, #44]
	ldr	r1, [r3, r10, asl #2]
	mul	r6, ip, r0
	ldr	r2, [r1, #148]
	ldr	r3, [r1, #152]
	mul	lr, r3, r2
	cmp	r6, lr
	bgt	.L122
	ldr	r3, [r1, #1448]
	ldrsb	r7, [r5, #37]
	cmp	r3, #1
	beq	.L123
.L84:
	add	r1, r1, #290816
	ldr	r2, .L127+12
	ldr	r3, [r1, #1112]
	ldr	r8, [r2, #64]
	cmp	r7, r3
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r1, #1128]
	cmp	r8, #0
	ldrsb	r3, [r5, #37]
	str	r3, [r1, #1112]
	beq	.L88
	ldr	r6, .L127+4
	mov	r0, r9
	ldr	r3, [r5, #44]
	mov	lr, #32
	ldr	r2, [r5, #40]
	add	r9, r6, #128
	str	r10, [sp, #12]
	str	r9, [sp, #16]
	ldrsb	ip, [r5, #36]
	str	lr, [sp, #4]
	ldr	r1, [fp, #-48]
	str	ip, [sp, #8]
	ldrsb	ip, [r5, #39]
	str	ip, [sp]
	blx	r8
	ldr	r3, .L127+8
	ldr	r2, .L127+8
	ldr	r3, [r3, r10, asl #2]
	add	r3, r3, #290816
	ldr	r3, [r3, #3496]
	cmp	r3, #32
	movge	r3, #32
	strb	r3, [r5, #5]
	cmp	r0, #2
	mov	r8, r0
	beq	.L124
	cmp	r0, #0
	bne	.L91
	ldr	r3, [r6, #176]
	mov	r0, #31
	ldr	r1, .L127+16
	strb	r3, [r5, #2]
	ldr	r3, [r2, r10, asl #2]
	str	r8, [r3, #1496]
	strb	r8, [r3, #1520]
	bl	dprint_vfmw
	ldr	r3, [r6, #176]
	cmp	r7, r3
	bgt	.L125
	strb	r8, [r5, #4]
	mov	r0, #8
	ldr	r3, [r6, #176]
	cmp	r3, #32
	movge	r3, #32
	strb	r3, [r5, #3]
	ldr	r3, .L127
	ldr	r3, [r3, #12]
	blx	r3
	ldr	r3, [r6, #188]
	cmp	r3, #0
	beq	.L126
	ldr	r3, [r6, #132]
	mov	r2, r8
	ldr	r1, [r5, #16]
	mov	r8, #88
	str	r3, [fp, #-64]
	add	r3, r6, #204
	str	r3, [fp, #-52]
	ldr	r3, [r6, #136]
	str	r3, [fp, #-68]
	ldr	r3, [r6, #140]
	str	r3, [fp, #-72]
	ldr	r3, [r5, #40]
	str	r3, [fp, #-56]
	ldr	r3, [r5, #44]
	str	r3, [fp, #-60]
.L99:
	mla	r3, r8, r1, r5
	ldr	r0, .L127+8
	ldr	lr, [fp, #-52]
	ldr	ip, [r0, r10, asl #2]
	add	r0, r3, #21760
	mov	r3, #0
	str	r1, [r0, #148]
	ldr	r6, [r9, #464]
	str	ip, [fp, #-48]
	str	r6, [r0, #152]
	ldr	ip, [r9, #468]
	ldr	r6, [r4, #164]
	str	ip, [r0, #156]
	ldr	ip, [lr, #4]!
	str	r6, [r0, #204]
	str	ip, [r0, #164]
	ldr	ip, [fp, #-64]
	str	lr, [fp, #-52]
	str	ip, [r0, #168]
	ldr	ip, [fp, #-68]
	str	ip, [r0, #172]
	ldr	ip, [r4, #148]
	str	ip, [r0, #176]
	ldr	ip, [r4, #156]
	str	ip, [r0, #180]
	ldr	ip, [fp, #-72]
	str	ip, [r0, #188]
	ldr	ip, [r4, #160]
	str	ip, [r0, #184]
	ldr	ip, [fp, #-48]
	add	r7, ip, #294912
	ldr	ip, [fp, #-56]
	str	ip, [r0, #196]
	ldr	ip, [r4, #144]
	str	ip, [r0, #192]
	ldr	ip, [fp, #-60]
	str	ip, [r0, #200]
	ldr	lr, [r4, #172]
	ldr	ip, [r4, #168]
	strb	r3, [r0, #145]
	str	lr, [r0, #212]
	str	ip, [r0, #208]
	strb	r3, [r0, #146]
	ldr	r3, [r7, #1156]
	ldr	r0, [r4, r10, asl #2]
	cmp	r3, #0
	bne	.L96
	ldr	lr, [r7, #1152]
	cmp	lr, #0
	beq	.L96
	ldr	r1, [r0, #16]
	ldr	ip, [fp, #-48]
	mla	r0, r8, r1, r0
	add	r1, r0, #21760
	add	r0, r1, #144
	ldr	lr, [r1, #152]
.L98:
	mov	r1, r3, asl #4
	add	r3, r3, #1
	add	r1, r1, #294912
	add	r1, r1, #628
	ldr	r1, [ip, r1]
	cmp	lr, r1
	moveq	r1, #4
	streqb	r1, [r0, #2]
	ldr	r1, [r7, #1152]
	cmp	r3, r1
	bcc	.L98
	ldr	r3, [r5, #40]
	ldr	r1, [r5, #16]
	str	r3, [fp, #-56]
	ldr	r3, [r5, #44]
	str	r3, [fp, #-60]
.L96:
	mla	r3, r8, r1, r5
	mov	r0, #1
	add	r1, r1, #1
	add	r2, r2, #1
	add	r9, r9, #12
	add	r3, r3, #21760
	str	r0, [r3, #228]
	str	r1, [r5, #16]
	ldr	r3, [r4, #188]
	cmp	r3, r2
	bhi	.L99
.L95:
	ldr	r3, [r4, #196]
	cmp	r3, #0
	beq	.L104
	ldr	r1, [r5, #24]
	mov	r0, #88
	ldr	r2, .L127+20
	mov	r3, #0
	add	ip, r1, #1
	mla	r1, r0, r1, r5
	add	r1, r1, #21760
	add	r1, r1, #160
.L103:
	ldr	lr, [r2, #848]
	add	r0, ip, r3
	add	r3, r3, #1
	add	r2, r2, #12
	str	lr, [r1], #88
	str	r0, [r5, #24]
	ldr	r0, [r4, #196]
	cmp	r0, r3
	bhi	.L103
.L104:
	ldr	r3, [r4, #184]
	cmp	r3, #32
	movge	r3, #32
	strb	r3, [r5, #5]
	ldr	r3, [r4, #192]
	cmp	r3, #0
	beq	.L102
	ldr	lr, [r5, #20]
	mov	r1, #0
	ldr	r0, .L127+20
	mov	r7, r1
	add	r2, lr, #3440
	add	lr, lr, #1
	add	r2, r2, #2
	mov	r6, #1
	add	r2, r5, r2, lsl #3
.L105:
	ldr	r3, [r0, #208]
	add	ip, lr, r1
	add	r1, r1, #1
	add	r0, r0, #8
	add	r2, r2, #8
	str	r3, [r2, #-8]
	ldr	r3, [r5, #20]
	add	r3, r3, #3440
	add	r3, r3, #2
	add	r3, r5, r3, lsl #3
	strb	r7, [r3, #5]
	strb	r6, [r2, #-4]
	str	ip, [r5, #20]
	ldr	r3, [r4, #192]
	cmp	r3, r1
	bhi	.L105
.L102:
	ldr	r2, [r4, #180]
	add	r3, r5, #20480
	mov	r8, #0
	str	r8, [r5, #60]
	str	r2, [r5, #8]
	mov	r2, #1
	ldr	r3, [r3, #1432]
	ldr	ip, [r4, #136]
	ldr	r0, [r4, #148]
	str	r3, [r5, #64]
	ldr	r3, [fp, #-56]
	ldr	r1, [r4, #156]
	str	ip, [r5, #84]
	str	r3, [r5, #108]
	ldr	r3, [fp, #-60]
	ldr	lr, [r4, #164]
	str	r0, [r5, #88]
	str	r3, [r5, #112]
	ldr	r3, [r4, #160]
	ldr	r0, [r4, #168]
	str	r1, [r5, #92]
	ldr	ip, [r4, #172]
	str	r3, [r5, #96]
	ldr	r1, [r4, #132]
	ldr	r3, [r4, #128]
	str	r2, [r5, #140]
	ldr	r2, [fp, #-76]
	str	r0, [r5, #120]
	mov	r0, #8
	strb	r8, [r5, #57]
	strb	r8, [r5, #58]
	str	lr, [r5, #116]
	str	ip, [r5, #124]
	str	r1, [r5, #80]
	str	r3, [r2]
	ldr	r3, .L127
	ldr	r3, [r3, #16]
	blx	r3
	mov	r0, r8
.L115:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L122:
	stmia	sp, {r0, ip}
	mov	r0, #0
	ldr	r1, .L127+24
	bl	dprint_vfmw
	ldr	r3, .L127+28
	ldr	r4, [r3]
	cmp	r4, #0
	mvneq	r0, #0
	beq	.L115
	mov	r3, #0
	mov	r0, r10
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L124:
	ldr	r3, [r6, #176]
	mov	r1, #1
	strb	r3, [r5, #2]
	ldr	r3, [r2, r10, asl #2]
	str	r1, [r3, #1496]
	strb	r1, [r3, #1520]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L88:
	ldr	r3, [r1, #3496]
	mvn	r8, #0
	cmp	r3, #32
	movge	r3, #32
	strb	r3, [r5, #5]
.L91:
	ldr	r2, .L127+8
	mov	r3, #0
	strb	r3, [r5, #2]
	mov	r0, r3
	ldr	r1, .L127+32
	ldr	ip, [r2, r10, asl #2]
	mov	r2, r8
	str	r3, [ip, #1496]
	strb	r3, [ip, #1520]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L115
.L123:
	add	r3, r1, #262144
	ldr	r3, [r3, #2016]
	bics	r2, r3, #2
	beq	.L84
	cmp	r3, #1
	moveq	r0, #0
	beq	.L115
	mov	r3, #0
	strb	r3, [r5, #2]
	ldr	r3, .L127+8
	mov	r0, #31
	ldr	r1, .L127+36
	ldr	r3, [r3, r10, asl #2]
	add	r3, r3, #262144
	ldr	r2, [r3, #2016]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L115
.L126:
	ldr	r3, [r5, #40]
	str	r3, [fp, #-56]
	ldr	r3, [r5, #44]
	str	r3, [fp, #-60]
	b	.L95
.L120:
	ldr	r3, .L127+40
	movw	r2, #599
	ldr	r1, .L127+44
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L115
.L125:
	str	r3, [sp]
	mov	r2, r8
	mov	r3, r7
	mov	r0, r8
	ldr	r1, .L127+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L115
.L121:
	mov	r0, r5
	ldr	r3, .L127+52
	mov	r2, #600
	ldr	r1, .L127+44
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L115
.L128:
	.align	2
.L127:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	g_vdm_hal_fun_ptr
	.word	.LC10
	.word	.LANCHOR0+128
	.word	.LC8
	.word	g_event_report
	.word	.LC11
	.word	.LC9
	.word	.LC2
	.word	.LC1
	.word	.LC12
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_ConfigFrameBuf, .-FSP_ConfigFrameBuf
	.align	2
	.global	FSP_GetOccupiedNum
	.type	FSP_GetOccupiedNum, %function
FSP_GetOccupiedNum:
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
	cmp	r2, #31
	bhi	.L135
	cmp	r0, #1088
	bgt	.L133
	ldr	r3, .L136
	ldr	r3, [r3, r2, asl #2]
	add	r3, r3, #294912
	ldr	r3, [r3, #1212]
	cmp	r3, #0
	movne	r0, #1
	moveq	r0, #4
	ldmfd	sp, {fp, sp, pc}
.L133:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L135:
	ldr	r3, .L136+4
	movw	r2, #765
	ldr	r1, .L136+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L137:
	.align	2
.L136:
	.word	s_pstVfmwChan
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_GetOccupiedNum, .-FSP_GetOccupiedNum
	.align	2
	.global	FSP_IsPmvAvailable
	.type	FSP_IsPmvAvailable, %function
FSP_IsPmvAvailable:
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
	ldrh	r0, [r0, #4]
	sub	r0, r0, #1
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	FSP_IsPmvAvailable, .-FSP_IsPmvAvailable
	.align	2
	.global	FSP_GetPhyFsNum
	.type	FSP_GetPhyFsNum, %function
FSP_GetPhyFsNum:
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
	cmp	r0, #31
	mov	r6, r0
	mov	r4, r1
	bhi	.L149
	ldr	r7, .L152
	ldr	r0, [r7, r0, asl #2]
	cmp	r0, #0
	beq	.L150
	ldr	r8, .L152+4
	mov	r0, #3
	mov	r5, #0
	ldr	r3, [r8, #12]
	blx	r3
	ldr	ip, [r7, r6, asl #2]
	add	r3, ip, #21760
	add	ip, ip, #24576
	add	r3, r3, #228
	add	ip, ip, #228
	b	.L144
.L143:
	add	r3, r3, #88
	cmp	r3, ip
	beq	.L151
.L144:
	ldr	r2, [r3]
	cmp	r2, #1
	bne	.L143
	ldr	r2, [r3, #-72]
	add	r3, r3, #88
	cmp	r4, #0
	cmpne	r2, r4
	addeq	r5, r5, #1
	cmp	r3, ip
	bne	.L144
.L151:
	ldr	r3, [r8, #16]
	mov	r0, #3
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L149:
	ldr	r3, .L152+8
	movw	r2, #1042
	ldr	r1, .L152+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L150:
	ldr	r3, .L152+16
	movw	r2, #1043
	ldr	r1, .L152+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L153:
	.align	2
.L152:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetPhyFsNum, .-FSP_GetPhyFsNum
	.align	2
	.global	FSP_RelsePhyFs
	.type	FSP_RelsePhyFs, %function
FSP_RelsePhyFs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	cmp	r0, #31
	mov	r5, r0
	mov	r7, r1
	bhi	.L190
	ldr	r8, .L192
	ldr	r0, [r8, r0, asl #2]
	cmp	r0, #0
	beq	.L191
	ldr	r6, .L192+4
	mov	r0, #3
	mov	r4, #0
	ldr	r3, [r6, #12]
	blx	r3
	ldr	r0, [r8, r5, asl #2]
	add	r3, r0, #21760
	add	r3, r3, #228
	b	.L161
.L158:
	add	r4, r4, #1
	add	r3, r3, #88
	cmp	r4, #32
	beq	.L186
.L161:
	ldr	r2, [r3]
	cmp	r2, #1
	bne	.L158
	ldrsb	r2, [r3, #-83]
	cmp	r2, #0
	bne	.L158
	ldrsb	r1, [r3, #-82]
	cmp	r1, #0
	bne	.L158
	ldr	r2, [r3, #-72]
	cmp	r2, r7
	beq	.L158
	mov	r3, #88
	movw	r2, #21912
	mla	r10, r3, r4, r0
	str	r1, [fp, #-72]
	add	r8, r10, #21760
	add	r8, r8, #152
	ldr	r9, [r10, r2]
	mov	r0, r9
	bl	MEM_Phy2Vir
	cmp	r4, #31
	ldr	r8, [r8, #4]
	ldr	r1, [fp, #-72]
	mov	r7, r0
	bgt	.L186
	add	r3, r10, #21760
	ldr	r10, .L192+8
	mov	r2, r8
	str	r1, [r3, #228]
	mov	r1, r0
	mov	r0, r9
	bl	MEM_DelMemRecord
	ldr	r3, [r10, r5, asl #2]
	mov	r1, r4, asl #6
	movw	r2, #29816
	add	r4, r1, r4, lsl #3
	movt	r2, 4
	add	r3, r3, r4
	ldr	r2, [r3, r2]
	cmp	r2, #255
	beq	.L163
	add	r3, r3, #290816
	ldr	r3, [r3, #1200]
	mov	r0, r3
	str	r3, [fp, #-72]
	bl	MEM_Phy2Vir
	ldr	r2, [r10, r5, asl #2]
	ldr	r3, [fp, #-72]
	add	r4, r2, r4
	add	r2, r4, #290816
	ldr	r2, [r2, #1156]
	mov	r1, r0
	mov	r0, r3
	bl	MEM_DelMemRecord
.L163:
	ldr	r3, [r6, #16]
	mov	r0, #3
	blx	r3
	ldr	r3, [r6, #12]
	mov	r0, #8
	blx	r3
	ldr	r0, [r10, r5, asl #2]
	movw	r3, #32584
	mov	r2, #0
	movt	r3, 4
	add	r3, r0, r3
	b	.L166
.L164:
	add	r2, r2, #1
	add	r3, r3, #12
	cmp	r2, #32
	beq	.L189
.L166:
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L164
	ldr	r1, [r3, #-8]
	cmp	r9, r1
	bne	.L164
	cmp	r2, #31
	bgt	.L189
	mov	r1, r2, asl #4
	add	r3, r0, #290816
	sub	r2, r1, r2, asl #2
	mov	r1, #0
	add	r2, r3, r2
	strb	r1, [r2, #3912]
.L167:
	add	r3, r3, #1136
	mov	r4, #0
	b	.L170
.L168:
	add	r4, r4, #1
	add	r3, r3, #72
	cmp	r4, #32
	beq	.L171
.L170:
	ldr	r2, [r3]
	cmp	r2, #255
	beq	.L168
	ldr	r2, [r3, #32]
	cmp	r9, r2
	bne	.L168
	cmp	r4, #31
	bgt	.L171
	ldr	r1, .L192+12
	mov	r3, r4, asl #6
	add	r3, r3, r4, lsl #3
	mov	r2, #255
	add	r3, r0, r3
	ldr	r10, [r1]
	add	r3, r3, #290816
	cmp	r10, #0
	str	r2, [r3, #1136]
	beq	.L171
	mov	ip, #0
	str	r9, [fp, #-68]
	mov	r0, r5
	str	r7, [fp, #-60]
	str	r8, [fp, #-52]
	mov	r3, #24
	str	ip, [fp, #-64]
	sub	r2, fp, #68
	str	ip, [fp, #-56]
	mov	r1, #123
	str	ip, [fp, #-48]
	blx	r10
.L171:
	ldr	r3, [r6, #16]
	mov	r0, #8
	blx	r3
	cmp	r4, #31
	movle	r0, #0
	mvngt	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L186:
	ldr	r3, [r6, #16]
	mov	r0, #3
	blx	r3
	mvn	r0, #0
.L185:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L189:
	add	r3, r0, #290816
	b	.L167
.L190:
	ldr	r3, .L192+16
	movw	r2, #1069
	ldr	r1, .L192+20
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L185
.L191:
	ldr	r3, .L192+24
	movw	r2, #1070
	ldr	r1, .L192+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L185
.L193:
	.align	2
.L192:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	.word	g_event_report
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_RelsePhyFs, .-FSP_RelsePhyFs
	.align	2
	.global	FSP_RemovePmv
	.type	FSP_RemovePmv, %function
FSP_RemovePmv:
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
	cmp	r0, #31
	ldrhi	r3, .L203
	movhi	r2, #1152
	bhi	.L200
	cmp	r1, #31
	bhi	.L201
	ldr	r3, .L203+4
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L202
	mov	r3, #680
	mla	r3, r3, r1, r0
	ldr	r2, [r3, #168]
	cmp	r2, #2
	ldmnefd	sp, {fp, sp, pc}
	ldrb	r3, [r3, #148]	@ zero_extendqisi2
	cmp	r3, #31
	bhi	.L199
	sxtb	r3, r3
	mov	r2, #0
	add	r3, r3, #3440
	add	r3, r3, #2
	add	r3, r0, r3, lsl #3
	strb	r2, [r3, #5]
.L199:
	mov	r2, #680
	mov	r3, #0
	mla	r1, r2, r1, r0
	str	r3, [r1, #168]
	ldmfd	sp, {fp, sp, pc}
.L201:
	ldr	r3, .L203+8
	movw	r2, #1153
.L200:
	ldr	r1, .L203+12
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L202:
	ldr	r3, .L203+16
	movw	r2, #1154
	ldr	r1, .L203+12
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L204:
	.align	2
.L203:
	.word	.LC2
	.word	.LANCHOR0
	.word	.LC13
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_RemovePmv, .-FSP_RemovePmv
	.align	2
	.global	FSP_SetRef
	.type	FSP_SetRef, %function
FSP_SetRef:
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
	cmp	r0, #31
	mov	r6, r2
	mov	r4, r1
	ldrhi	r3, .L239
	movwhi	r2, #1177
	bhi	.L231
	cmp	r1, #31
	bhi	.L232
	ldr	r3, .L239+4
	ldr	r5, [r3, r0, asl #2]
	cmp	r5, #0
	beq	.L233
	mov	r3, #680
	uxtb	r2, r6
	mla	r3, r3, r1, r5
	ldrsb	r1, [r3, #146]
	strb	r2, [r3, #144]
	cmp	r1, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r3, #172]
	cmp	r1, #0
	beq	.L211
	ldr	r3, [r3, #164]
	ldr	r0, [r1, #72]
	cmp	r0, r3
	streqb	r2, [r1, #1]
.L211:
	mov	r2, #680
	mla	r2, r2, r4, r5
	ldrb	r3, [r2, #148]	@ zero_extendqisi2
	cmp	r3, #31
	bhi	.L212
	cmp	r6, #1
	beq	.L234
	cmp	r6, #0
	bne	.L215
	ldr	r1, [r2, #168]
	cmp	r1, #2
	beq	.L235
.L222:
	mov	r3, #680
	mla	r3, r3, r4, r5
	ldr	r3, [r3, #176]
	cmp	r3, #0
	beq	.L225
	ldrsb	r2, [r3, #2]
	cmp	r2, #1
	moveq	r2, #0
	streqb	r2, [r3, #2]
.L225:
	mov	r3, #680
	mla	r4, r3, r4, r5
	str	r6, [r4, #172]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L232:
	ldr	r3, .L239+8
	movw	r2, #1178
.L231:
	ldr	r1, .L239+12
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L234:
	ldr	r1, [r2, #168]
	cmp	r1, #1
	beq	.L236
.L214:
	mov	r3, #680
	mla	r3, r3, r4, r5
	ldr	r2, [r3, #176]
	cmp	r2, #0
	beq	.L237
.L221:
	mov	r3, #680
	ldr	r0, [r2, #72]
	mla	r3, r3, r4, r5
	ldr	r1, [r3, #164]
	cmp	r6, #1
	cmpeq	r0, r1
	beq	.L238
.L218:
	cmp	r6, #0
	beq	.L225
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L212:
	sxtb	r3, r3
	movw	r2, #1226
	ldr	r1, .L239+16
	mov	r0, #0
	bl	dprint_vfmw
	cmp	r6, #0
	beq	.L222
	b	.L214
.L236:
	sxtb	r3, r3
	mov	r1, #2
	add	r3, r3, #3440
	add	r3, r3, r1
	add	r3, r5, r3, lsl #3
	strb	r6, [r3, #5]
	str	r1, [r2, #168]
.L215:
	mov	r3, #680
	mla	r3, r3, r4, r5
	ldr	r2, [r3, #176]
	cmp	r2, #0
	bne	.L221
	b	.L218
.L235:
	sxtb	r3, r3
	add	r3, r3, #3440
	add	r3, r3, #2
	add	r3, r5, r3, lsl #3
	strb	r6, [r3, #5]
	str	r6, [r2, #152]
	str	r6, [r2, #168]
	b	.L222
.L233:
	mov	r0, r5
	ldr	r3, .L239+20
	movw	r2, #1179
	ldr	r1, .L239+12
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L238:
	ldrsb	r1, [r2, #2]
	cmp	r1, #1
	moveq	r1, #2
	streqb	r1, [r2, #2]
	streqb	r1, [r3, #145]
	b	.L218
.L237:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L240:
	.align	2
.L239:
	.word	.LC2
	.word	.LANCHOR0
	.word	.LC13
	.word	.LC1
	.word	.LC14
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_SetRef, .-FSP_SetRef
	.align	2
	.global	FSP_GetRef
	.type	FSP_GetRef, %function
FSP_GetRef:
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
	cmp	r0, #31
	bhi	.L246
	cmp	r1, #31
	bhi	.L247
	ldr	r3, .L249
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L248
	mov	r0, #680
	mla	r1, r0, r1, r3
	ldrsb	r0, [r1, #144]
	ldmfd	sp, {fp, sp, pc}
.L246:
	ldr	r3, .L249+4
	movw	r2, #1258
	ldr	r1, .L249+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L247:
	ldr	r3, .L249+12
	movw	r2, #1259
	ldr	r1, .L249+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L248:
	mov	r0, r3
	movw	r2, #1260
	ldr	r3, .L249+16
	ldr	r1, .L249+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L250:
	.align	2
.L249:
	.word	.LANCHOR0
	.word	.LC15
	.word	.LC1
	.word	.LC16
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetRef, .-FSP_GetRef
	.align	2
	.global	FSP_SetDisplay
	.type	FSP_SetDisplay, %function
FSP_SetDisplay:
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
	cmp	r0, #31
	mov	r7, r2
	mov	r4, r0
	mov	r6, r1
	ldrhi	r3, .L284
	movwhi	r2, #1273
	bhi	.L278
	cmp	r1, #31
	bhi	.L279
	ldr	r5, .L284+4
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L280
	ldr	r8, .L284+8
	mov	r0, #3
	ldr	r3, [r8, #12]
	blx	r3
	ldr	r9, [r5, r4, asl #2]
	mov	r5, #680
	cmp	r7, #0
	mla	r5, r5, r6, r9
	moveq	r3, #0
	movne	r3, #3
	add	ip, r5, #144
	ldrsb	r0, [ip, #2]
	strb	r3, [ip, #1]
	cmp	r0, #0
	bne	.L264
	ldr	r3, [r5, #176]
	cmp	r3, #0
	beq	.L264
	ldr	r3, [r3, #72]
	ldr	r2, [r5, #164]
	cmp	r3, r2
	bne	.L281
	cmp	r7, #0
	bne	.L259
	strb	r7, [ip, #1]
	mov	r0, r4
	ldr	r3, [r5, #176]
	strb	r7, [r3, #2]
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L282
.L261:
	mov	r1, #680
	mov	r3, #0
	mla	r6, r1, r6, r9
	str	r3, [r6, #176]
.L264:
	ldr	r3, [r8, #16]
	mov	r0, #3
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L279:
	ldr	r3, .L284+12
	movw	r2, #1274
.L278:
	ldr	r1, .L284+16
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L259:
	mov	r0, r4
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L283
.L263:
	mov	r1, #680
	mov	r3, #3
	mla	r6, r1, r6, r9
	ldr	r2, [r6, #176]
	strb	r3, [r6, #145]
	strb	r3, [r2, #2]
	b	.L264
.L281:
	ldr	r1, .L284+20
	bl	dprint_vfmw
	b	.L264
.L280:
	ldr	r3, .L284+24
	movw	r2, #1275
	ldr	r1, .L284+16
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L283:
	ldr	r3, [r5, #176]
	cmp	r3, #0
	ldrne	r2, [r3, #80]
	addne	r2, r2, #1
	strne	r2, [r3, #80]
	b	.L263
.L282:
	ldr	r3, [r5, #176]
	cmp	r3, #0
	beq	.L261
	ldr	r2, [r3, #80]
	cmp	r2, #0
	beq	.L261
	sub	r2, r2, #1
	str	r2, [r3, #80]
	ldr	r3, [r5, #176]
	ldr	r2, [r3, #80]
	cmp	r2, #0
	movne	r2, #3
	strneb	r2, [r3, #2]
	b	.L261
.L285:
	.align	2
.L284:
	.word	.LC2
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	.LC1
	.word	.LC17
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_SetDisplay, .-FSP_SetDisplay
	.align	2
	.global	FSP_ClearNotInVoQueue
	.type	FSP_ClearNotInVoQueue, %function
FSP_ClearNotInVoQueue:
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
	cmp	r0, #31
	mov	r5, r0
	mov	r7, r1
	bhi	.L297
	cmp	r1, #0
	beq	.L298
	ldr	r3, .L301
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r6, r0, #21760
	addne	r4, r0, #184
	addne	r6, r6, #184
	bne	.L292
	b	.L299
.L291:
	add	r4, r4, #680
	cmp	r4, r6
	beq	.L300
.L292:
	mov	r2, #0
	ldr	r1, [r4, #148]
	mov	r0, r5
	bl	FSP_SetRef
	mov	r1, r4
	mov	r0, r7
	bl	IsImageInVoQueue
	cmp	r0, #0
	beq	.L291
	ldr	r1, [r4, #148]
	mov	r2, #0
	mov	r0, r5
	add	r4, r4, #680
	bl	FSP_SetDisplay
	cmp	r4, r6
	bne	.L292
.L300:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L297:
	ldr	r3, .L301+4
	movw	r2, #501
	ldr	r1, .L301+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L299:
	ldr	r3, .L301+12
	movw	r2, #503
	ldr	r1, .L301+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L298:
	mov	r0, r1
	ldr	r3, .L301+16
	movw	r2, #502
	ldr	r1, .L301+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L302:
	.align	2
.L301:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	.word	.LC18
	UNWIND(.fnend)
	.size	FSP_ClearNotInVoQueue, .-FSP_ClearNotInVoQueue
	.align	2
	.global	FSP_GetDisplay
	.type	FSP_GetDisplay, %function
FSP_GetDisplay:
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
	cmp	r0, #31
	bhi	.L308
	ldr	r3, .L311
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L309
	cmp	r1, #31
	bhi	.L310
	mov	r0, #680
	mla	r1, r0, r1, r3
	ldrsb	r0, [r1, #145]
	ldmfd	sp, {fp, sp, pc}
.L308:
	ldr	r3, .L311+4
	movw	r2, #1348
	ldr	r1, .L311+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L310:
	ldr	r3, .L311+12
	movw	r2, #1350
	ldr	r1, .L311+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L309:
	mov	r0, r3
	movw	r2, #1349
	ldr	r3, .L311+16
	ldr	r1, .L311+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L312:
	.align	2
.L311:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC13
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetDisplay, .-FSP_GetDisplay
	.align	2
	.global	FSP_SetStoreType
	.type	FSP_SetStoreType, %function
FSP_SetStoreType:
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
	cmp	r0, #31
	bhi	.L322
	ldr	ip, .L326
	ldr	ip, [ip, r0, asl #2]
	cmp	ip, #0
	beq	.L323
	cmp	r2, #31
	bhi	.L324
	cmp	r1, #0
	bne	.L318
	ldrsb	r0, [ip, #3]
	cmp	r2, r0
	bge	.L321
	mov	lr, #88
	mov	r0, r1
	mla	r2, lr, r2, ip
	add	r2, r2, #21760
	str	r3, [r2, #220]
	ldmfd	sp, {fp, sp, pc}
.L318:
	cmp	r1, #1
	beq	.L325
.L321:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L325:
	ldrsb	r1, [ip, #4]
	cmp	r2, r1
	bge	.L321
	mov	r1, #88
	mov	r0, #0
	mla	r2, r1, r2, ip
	add	r2, r2, #24576
	str	r3, [r2, #220]
	ldmfd	sp, {fp, sp, pc}
.L322:
	ldr	r3, .L326+4
	movw	r2, #1363
	ldr	r1, .L326+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L324:
	ldr	r3, .L326+12
	movw	r2, #1365
	ldr	r1, .L326+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L323:
	mov	r0, ip
	ldr	r3, .L326+16
	movw	r2, #1364
	ldr	r1, .L326+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L327:
	.align	2
.L326:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC19
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_SetStoreType, .-FSP_SetStoreType
	.align	2
	.global	FSP_GetStoreType
	.type	FSP_GetStoreType, %function
FSP_GetStoreType:
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
	cmp	r0, #31
	bhi	.L337
	ldr	r3, .L341
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L338
	cmp	r2, #31
	bhi	.L339
	cmp	r1, #0
	bne	.L333
	ldrsb	r3, [r0, #3]
	cmp	r2, r3
	bge	.L336
	mov	r3, #88
	mla	r2, r3, r2, r0
	add	r2, r2, #21760
	ldr	r0, [r2, #220]
	ldmfd	sp, {fp, sp, pc}
.L337:
	ldr	r3, .L341+4
	movw	r2, #1394
	ldr	r1, .L341+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L339:
	ldr	r3, .L341+12
	movw	r2, #1396
	ldr	r1, .L341+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L333:
	cmp	r1, #1
	beq	.L340
.L336:
	mov	r0, #2
	ldmfd	sp, {fp, sp, pc}
.L338:
	ldr	r3, .L341+16
	movw	r2, #1395
	ldr	r1, .L341+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L340:
	ldrsb	r3, [r0, #4]
	cmp	r2, r3
	bge	.L336
	mov	r3, #88
	mla	r2, r3, r2, r0
	add	r2, r2, #24576
	ldr	r0, [r2, #220]
	ldmfd	sp, {fp, sp, pc}
.L342:
	.align	2
.L341:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC19
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetStoreType, .-FSP_GetStoreType
	.align	2
	.global	FSP_ClearLogicFs
	.type	FSP_ClearLogicFs, %function
FSP_ClearLogicFs:
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
	cmp	r0, #31
	cmpls	r1, #31
	mov	r4, r0
	mov	r5, r1
	ldmhifd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r6, .L353
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r2, #0
	bl	FSP_SetRef
	ldr	r2, [r6, r4, asl #2]
	mov	r3, #680
	mla	r3, r3, r5, r2
	ldrsb	r3, [r3, #145]
	cmp	r3, #3
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r5
	mov	r0, r4
	mov	r2, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	FSP_SetDisplay
.L354:
	.align	2
.L353:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_ClearLogicFs, .-FSP_ClearLogicFs
	.align	2
	.global	FSP_GetLogicFs
	.type	FSP_GetLogicFs, %function
FSP_GetLogicFs:
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
	cmp	r0, #31
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L357
	ldr	r3, .L359
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, #680
	mlane	r1, r3, r1, r0
	addne	r0, r1, #144
	ldmfd	sp, {fp, sp, pc}
.L357:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L360:
	.align	2
.L359:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetLogicFs, .-FSP_GetLogicFs
	.align	2
	.global	FSP_GetFsImagePtr
	.type	FSP_GetFsImagePtr, %function
FSP_GetFsImagePtr:
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
	cmp	r0, #31
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L363
	ldr	r3, .L365
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, #680
	mlane	r1, r3, r1, r0
	addne	r0, r1, #184
	ldmfd	sp, {fp, sp, pc}
.L363:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L366:
	.align	2
.L365:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetFsImagePtr, .-FSP_GetFsImagePtr
	.align	2
	.global	FSP_GetDecPhyFs
	.type	FSP_GetDecPhyFs, %function
FSP_GetDecPhyFs:
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
	cmp	r0, #31
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L369
	ldr	r3, .L371
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, #680
	mlane	r0, r3, r1, r0
	ldrne	r0, [r0, #172]
	ldmfd	sp, {fp, sp, pc}
.L369:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L372:
	.align	2
.L371:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetDecPhyFs, .-FSP_GetDecPhyFs
	.align	2
	.global	FSP_GetDispPhyFs
	.type	FSP_GetDispPhyFs, %function
FSP_GetDispPhyFs:
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
	cmp	r0, #31
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L375
	ldr	r3, .L377
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, #680
	mlane	r0, r3, r1, r0
	ldrne	r0, [r0, #176]
	ldmfd	sp, {fp, sp, pc}
.L375:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L378:
	.align	2
.L377:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetDispPhyFs, .-FSP_GetDispPhyFs
	.align	2
	.global	FSP_GetPmvAddr
	.type	FSP_GetPmvAddr, %function
FSP_GetPmvAddr:
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
	cmp	r0, #31
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L381
	ldr	r3, .L383
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, #680
	mlane	r0, r3, r1, r0
	ldrne	r0, [r0, #152]
	ldmfd	sp, {fp, sp, pc}
.L381:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L384:
	.align	2
.L383:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetPmvAddr, .-FSP_GetPmvAddr
	.align	2
	.global	FSP_GetDecFsAddrTab
	.type	FSP_GetDecFsAddrTab, %function
FSP_GetDecFsAddrTab:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L396
	ldr	lr, .L398
	ldr	ip, [lr, r0, asl #2]
	cmp	ip, #0
	moveq	r0, ip
	ldreq	r3, .L398+4
	movweq	r2, #1514
	beq	.L395
	cmp	r2, #0
	moveq	r0, r2
	ldreq	r3, .L398+8
	movweq	r2, #1515
	beq	.L395
	cmp	r1, #0
	beq	.L397
	ldrsb	ip, [ip, #3]
	cmp	ip, #0
	str	ip, [r1]
	ldr	ip, [lr, r0, asl #2]
	add	ip, ip, #21760
	add	ip, ip, #144
	ldmlefd	sp, {r4, fp, sp, pc}
	sub	r2, r2, #4
	sub	r3, r3, #4
	mov	lr, #0
.L392:
	ldr	r0, [ip, #8]
	add	lr, lr, #1
	add	ip, ip, #88
	str	r0, [r2, #4]!
	ldr	r4, [ip, #-68]
	str	r4, [r3, #4]!
	ldr	r4, [r1]
	cmp	r4, lr
	bgt	.L392
	ldmfd	sp, {r4, fp, sp, pc}
.L396:
	ldr	r3, .L398+12
	movw	r2, #1513
	ldr	r1, .L398+16
	mov	r0, #0
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	dprint_vfmw
.L397:
	ldr	r3, .L398+20
	mov	r0, r1
	movw	r2, #1516
.L395:
	ldr	r1, .L398+16
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	dprint_vfmw
.L399:
	.align	2
.L398:
	.word	.LANCHOR0
	.word	.LC4
	.word	.LC20
	.word	.LC2
	.word	.LC1
	.word	.LC21
	UNWIND(.fnend)
	.size	FSP_GetDecFsAddrTab, .-FSP_GetDecFsAddrTab
	.align	2
	.global	FSP_GetPmvAddrTab
	.type	FSP_GetPmvAddrTab, %function
FSP_GetPmvAddrTab:
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
	cmp	r0, #31
	bhi	.L411
	ldr	r3, .L413
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldreq	r3, .L413+4
	movweq	r2, #1538
	beq	.L410
	cmp	r2, #0
	moveq	r0, r2
	ldreq	r3, .L413+8
	movweq	r2, #1539
	beq	.L410
	cmp	r1, #0
	beq	.L412
	ldrsb	r3, [r0, #5]
	str	r3, [r1]
	ldrsb	r3, [r0, #5]
	cmp	r3, #0
	ldmlefd	sp, {fp, sp, pc}
	sub	r2, r2, #4
	mov	r1, #0
.L407:
	mov	r3, r1, asl #3
	add	r1, r1, #1
	add	r3, r3, #27392
	add	r3, r3, #144
	ldr	r3, [r0, r3]
	str	r3, [r2, #4]!
	ldrsb	r3, [r0, #5]
	cmp	r3, r1
	bgt	.L407
	ldmfd	sp, {fp, sp, pc}
.L411:
	ldr	r3, .L413+12
	movw	r2, #1537
	ldr	r1, .L413+16
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L412:
	ldr	r3, .L413+20
	mov	r0, r1
	movw	r2, #1540
.L410:
	ldr	r1, .L413+16
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L414:
	.align	2
.L413:
	.word	.LANCHOR0
	.word	.LC4
	.word	.LC22
	.word	.LC2
	.word	.LC1
	.word	.LC23
	UNWIND(.fnend)
	.size	FSP_GetPmvAddrTab, .-FSP_GetPmvAddrTab
	.align	2
	.global	FSP_GetInstInfo
	.type	FSP_GetInstInfo, %function
FSP_GetInstInfo:
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
	cmp	r0, #31
	mov	ip, r1
	bhi	.L418
	ldr	r3, .L420
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L419
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	add	r4, r3, #20480
	ldr	r5, .L420+4
	add	r1, r3, #21760
	add	r1, r1, #144
	add	r0, ip, #8
	strb	r2, [ip, #2]
	mov	r2, #2816
	ldr	lr, [r4, #1520]
	ldr	r4, [r4, #1432]
	rsb	lr, r4, lr
	str	lr, [ip, #4]
	ldrb	lr, [r3, #4]	@ zero_extendqisi2
	strb	lr, [ip, #3]
	ldrb	lr, [r3]	@ zero_extendqisi2
	strb	lr, [ip]
	ldrb	r3, [r3, #5]	@ zero_extendqisi2
	strb	r3, [ip, #1]
	ldr	r3, [r5, #52]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L418:
	ldr	r3, .L420+8
	movw	r2, #1557
	ldr	r1, .L420+12
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L419:
	mov	r0, r3
	movw	r2, #1558
	ldr	r3, .L420+16
	ldr	r1, .L420+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L421:
	.align	2
.L420:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetInstInfo, .-FSP_GetInstInfo
	.align	2
	.global	FSP_GetLogicIdByPhyAddr
	.type	FSP_GetLogicIdByPhyAddr, %function
FSP_GetLogicIdByPhyAddr:
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
	cmp	r0, #31
	bhi	.L433
	ldr	r3, .L435
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, r0
	movne	r0, #0
	beq	.L434
.L427:
	ldr	r2, [r3, #172]
	add	r3, r3, #680
	cmp	r2, #0
	beq	.L426
	ldr	r2, [r2, #8]
	cmp	r2, r1
	ldmeqfd	sp, {fp, sp, pc}
.L426:
	add	r0, r0, #1
	cmp	r0, #32
	bne	.L427
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L433:
	ldr	r3, .L435+4
	movw	r2, #1579
	ldr	r1, .L435+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L434:
	ldr	r3, .L435+12
	movw	r2, #1580
	ldr	r1, .L435+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L436:
	.align	2
.L435:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetLogicIdByPhyAddr, .-FSP_GetLogicIdByPhyAddr
	.align	2
	.global	FSP_GetNullLogicFs
	.type	FSP_GetNullLogicFs, %function
FSP_GetNullLogicFs:
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
	cmp	r0, #31
	bhi	.L450
	ldr	r3, .L453
	ldr	ip, [r3, r0, asl #2]
	cmp	ip, #0
	beq	.L440
	add	r3, ip, #20992
	ldrsb	r3, [r3, #233]
	cmp	r3, #0
	addne	r2, ip, #20480
	movne	r3, #30
	addne	r2, r2, #65
	bne	.L445
	b	.L451
.L443:
	subs	r3, r3, #1
	bcc	.L452
.L445:
	ldrsb	r1, [r2]
	sub	r2, r2, #680
	cmp	r1, #0
	bne	.L443
.L444:
	mov	r2, #680
	mov	r0, r3
	mla	r3, r2, r3, ip
	mov	r2, #0
	str	r2, [r3, #172]
	str	r2, [r3, #176]
	ldmfd	sp, {fp, sp, pc}
.L452:
	mov	r3, #0
	b	.L444
.L451:
	mov	r3, #31
	b	.L444
.L450:
	ldr	r3, .L453+4
	movw	r2, #1606
	ldr	r1, .L453+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L440:
	mov	r0, ip
	ldr	r3, .L453+12
	movw	r2, #1607
	ldr	r1, .L453+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L454:
	.align	2
.L453:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetNullLogicFs, .-FSP_GetNullLogicFs
	.align	2
	.global	FSP_GetFspType
	.type	FSP_GetFspType, %function
FSP_GetFspType:
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
	cmp	r0, #31
	bhi	.L459
	ldr	r3, .L461
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L460
	ldr	r0, [r0, #28]
	subs	r0, r0, #1
	mvnne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L459:
	ldr	r3, .L461+4
	movw	r2, #1628
	ldr	r1, .L461+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L460:
	ldr	r3, .L461+12
	movw	r2, #1629
	ldr	r1, .L461+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L462:
	.align	2
.L461:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetFspType, .-FSP_GetFspType
	.align	2
	.global	FSP_GetTotalValidFsNum
	.type	FSP_GetTotalValidFsNum, %function
FSP_GetTotalValidFsNum:
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
	cmp	r0, #31
	bhi	.L467
	ldr	r3, .L469
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L468
	ldrsb	r0, [r0, #2]
	ldmfd	sp, {fp, sp, pc}
.L467:
	ldr	r3, .L469+4
	movw	r2, #1643
	ldr	r1, .L469+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L468:
	ldr	r3, .L469+12
	movw	r2, #1644
	ldr	r1, .L469+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L470:
	.align	2
.L469:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetTotalValidFsNum, .-FSP_GetTotalValidFsNum
	.align	2
	.global	FSP_IsSpecialFrm
	.type	FSP_IsSpecialFrm, %function
FSP_IsSpecialFrm:
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
	cmp	r0, #31
	bhi	.L482
	ldr	r3, .L483
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	r3, r1, #1
	cmn	r3, #3
	bhi	.L477
	add	r3, r0, #294912
	ldr	ip, [r3, #1152]
	cmp	ip, #0
	beq	.L477
	ldr	r3, [r3, #628]
	cmp	r3, r1
	beq	.L480
	mov	r2, #0
	b	.L474
.L475:
	add	r3, r3, #628
	ldr	r3, [r0, r3]
	cmp	r3, r1
	beq	.L480
.L474:
	add	r2, r2, #1
	cmp	r2, ip
	mov	r3, r2, asl #4
	add	r3, r3, #294912
	bne	.L475
.L477:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L480:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L482:
	ldr	r3, .L483+4
	movw	r2, #1654
	ldr	r1, .L483+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L484:
	.align	2
.L483:
	.word	s_pstVfmwChan
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_IsSpecialFrm, .-FSP_IsSpecialFrm
	.align	2
	.global	FSP_EmptyInstance
	.type	FSP_EmptyInstance, %function
FSP_EmptyInstance:
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
	cmp	r0, #31
	mov	r7, r0
	bhi	.L505
	ldr	r3, .L507
	ldr	r6, [r3, r0, asl #2]
	cmp	r6, #0
	beq	.L506
	ldr	r3, .L507+4
	mov	r2, #21760
	mov	r1, #0
	add	r0, r6, #144
	ldr	r3, [r3, #48]
	blx	r3
	ldrsb	r3, [r6, #3]
	cmp	r3, #0
	ble	.L495
	add	r4, r6, #21760
	mov	r9, #0
	add	r4, r4, #152
	mov	r5, r9
	mov	r8, #4
.L494:
	ldr	r1, [r4]
	mov	r0, r7
	bl	FSP_IsSpecialFrm
	strb	r5, [r4, #-7]
	strb	r5, [r4, #-8]
	add	r9, r9, #1
	str	r5, [r4, #64]
	add	r4, r4, #88
	cmp	r0, #1
	movne	r3, r5
	moveq	r3, r8
	strb	r3, [r4, #-94]
	ldrsb	r3, [r6, #3]
	cmp	r3, r9
	bgt	.L494
.L495:
	ldrsb	r3, [r6, #4]
	cmp	r3, #0
	ble	.L491
	add	r4, r6, #24576
	mov	r9, #0
	add	r4, r4, #152
	mov	r5, r9
	mov	r8, #4
.L500:
	ldr	r1, [r4]
	mov	r0, r7
	bl	FSP_IsSpecialFrm
	strb	r5, [r4, #-7]
	strb	r5, [r4, #-8]
	add	r9, r9, #1
	str	r5, [r4, #64]
	add	r4, r4, #88
	cmp	r0, #1
	movne	r3, r5
	moveq	r3, r8
	strb	r3, [r4, #-94]
	ldrsb	r3, [r6, #4]
	cmp	r3, r9
	bgt	.L500
.L491:
	ldrsb	r1, [r6, #5]
	cmp	r1, #0
	ble	.L497
	add	r3, r6, #27392
	mov	r2, #0
	add	r3, r3, #148
	mov	ip, r2
	mov	r0, #1
.L501:
	add	r2, r2, #1
	strb	r0, [r3]
	cmp	r2, r1
	strb	ip, [r3, #1]
	add	r3, r3, #8
	bne	.L501
.L497:
	mov	r0, #0
	str	r0, [r6, #12]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L505:
	ldr	r3, .L507+8
	movw	r2, #446
	ldr	r1, .L507+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L506:
	mov	r0, r6
	ldr	r3, .L507+16
	movw	r2, #447
	ldr	r1, .L507+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L508:
	.align	2
.L507:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_EmptyInstance, .-FSP_EmptyInstance
	.align	2
	.global	FSP_IsDecFsAvailable
	.type	FSP_IsDecFsAvailable, %function
FSP_IsDecFsAvailable:
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
	cmp	r0, #31
	bhi	.L514
	ldr	r3, [r1, #84]
	cmp	r3, #1
	beq	.L515
.L513:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L515:
	ldr	r3, [r1]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #0
	bne	.L513
	ldr	r1, [r1, #8]
	bl	FSP_IsSpecialFrm
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L514:
	ldr	r3, .L516
	movw	r2, #781
	ldr	r1, .L516+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #255
	ldmfd	sp, {fp, sp, pc}
.L517:
	.align	2
.L516:
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_IsDecFsAvailable, .-FSP_IsDecFsAvailable
	.align	2
	.global	FSP_IfCanGetDecFs
	.type	FSP_IfCanGetDecFs, %function
FSP_IfCanGetDecFs:
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
	cmp	r0, #31
	mov	r5, r0
	bhi	.L537
	cmp	r1, #0
	beq	.L538
	ldr	r3, .L544
	ldr	r6, [r3, r0, asl #2]
	cmp	r6, #0
	addne	r4, r6, #21760
	addne	r7, r6, #24576
	addne	r4, r4, #144
	addne	r7, r7, #144
	bne	.L523
	b	.L539
.L541:
	cmp	r4, r7
	beq	.L540
.L523:
	mov	r1, r4
	mov	r0, r5
	bl	FSP_IsDecFsAvailable
	add	r4, r4, #88
	cmp	r0, #1
	bne	.L541
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L540:
	add	r2, r6, #21760
	mov	r0, #0
	add	r2, r2, #228
	mov	r3, r0
	mov	ip, #88
	b	.L525
.L524:
	add	r3, r3, #1
	cmp	r3, #32
	beq	.L542
.L525:
	ldr	r1, [r2]
	add	r2, r2, #88
	cmp	r1, #1
	bne	.L524
	mla	r1, ip, r3, r6
	add	r3, r3, #1
	add	r1, r1, #21760
	add	r1, r1, #144
	ldr	r1, [r1]
	bic	r1, r1, #-16777216
	bic	r1, r1, #255
	cmp	r1, #196608
	addeq	r0, r0, #1
	cmp	r3, #32
	bne	.L525
.L542:
	ldr	r3, [r6, #40]
	cmp	r3, #1088
	movgt	r3, #1
	ble	.L543
.L527:
	cmp	r0, r3
	movgt	r0, #0
	mvnle	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L543:
	ldr	r3, .L544+4
	ldr	r3, [r3, r5, asl #2]
	add	r3, r3, #294912
	ldr	r3, [r3, #1212]
	cmp	r3, #0
	movne	r3, #1
	moveq	r3, #4
	b	.L527
.L537:
	ldr	r3, .L544+8
	movw	r2, #529
	ldr	r1, .L544+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L539:
	mov	r0, r6
	ldr	r3, .L544+16
	movw	r2, #531
	ldr	r1, .L544+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L538:
	mov	r0, r1
	ldr	r3, .L544+20
	movw	r2, #530
	ldr	r1, .L544+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L545:
	.align	2
.L544:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	.LC2
	.word	.LC1
	.word	.LC4
	.word	.LC18
	UNWIND(.fnend)
	.size	FSP_IfCanGetDecFs, .-FSP_IfCanGetDecFs
	.align	2
	.global	FSP_IsNewFsAvalible
	.type	FSP_IsNewFsAvalible, %function
FSP_IsNewFsAvalible:
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
	cmp	r0, #31
	mov	r5, r0
	bhi	.L583
	ldr	r8, .L587
	ldr	r7, [r8, r0, asl #2]
	cmp	r7, #0
	beq	.L584
	ldrsb	r3, [r7, #3]
	cmp	r3, #0
	bne	.L550
.L557:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L550:
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L551
	ldrsb	r3, [r7, #3]
	cmp	r3, #0
	ble	.L558
	add	r4, r7, #21760
	mov	r6, #0
	add	r4, r4, #144
	b	.L554
.L585:
	add	r6, r6, #1
	cmp	r3, r6
	ble	.L558
.L554:
	mov	r1, r4
	mov	r0, r5
	bl	FSP_IsDecFsAvailable
	add	r4, r4, #88
	ldrsb	r3, [r7, #3]
	cmp	r0, #1
	bne	.L585
	cmp	r3, r6
	ble	.L558
.L562:
	mov	r0, r5
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L557
	ldrsb	r1, [r7, #5]
	cmp	r1, #0
	ble	.L563
	add	r3, r7, #27392
	ldrh	r3, [r3, #148]
	cmp	r3, #1
	beq	.L557
	mov	r2, #0
	b	.L564
.L565:
	add	r3, r7, r3, lsl #3
	ldrh	r3, [r3, #4]
	cmp	r3, #1
	beq	.L557
.L564:
	add	r2, r2, #1
	cmp	r2, r1
	add	r3, r2, #3440
	add	r3, r3, #2
	bne	.L565
.L567:
	mov	r0, r5
	bl	VCTRL_GetVidStd
	cmp	r0, #0
	beq	.L557
	mov	r0, r5
	bl	VCTRL_GetVidStd
	cmp	r0, #16
	beq	.L557
	mov	r0, r5
	bl	VCTRL_GetVidStd
	cmp	r0, #15
	beq	.L557
.L558:
	ldr	r3, [r8, r5, asl #2]
	cmp	r3, #0
	beq	.L586
.L566:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L551:
	ldr	r3, .L587+4
	add	r4, r7, #21760
	add	r4, r4, #144
	mov	r6, #0
	ldr	r3, [r3, r5, asl #2]
	add	r3, r3, #593920
	ldr	r9, [r3, #516]
	b	.L561
.L559:
	add	r6, r6, #1
	add	r4, r4, #88
	cmp	r6, #32
	beq	.L558
.L561:
	mov	r1, r4
	mov	r0, r5
	bl	FSP_IsDecFsAvailable
	cmp	r0, #1
	bne	.L559
	ldr	r3, [r4, #12]
	cmp	r3, r9
	bne	.L559
	cmp	r6, #31
	ble	.L562
	b	.L558
.L583:
	ldr	r3, .L587+8
	movw	r2, #813
	ldr	r1, .L587+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L563:
	bne	.L558
	b	.L567
.L584:
	mov	r0, r7
	ldr	r3, .L587+16
	movw	r2, #814
	ldr	r1, .L587+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L586:
	ldr	r1, .L587+20
	mov	r0, #1
	bl	dprint_vfmw
	b	.L566
.L588:
	.align	2
.L587:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	.LC2
	.word	.LC1
	.word	.LC4
	.word	.LC24
	UNWIND(.fnend)
	.size	FSP_IsNewFsAvalible, .-FSP_IsNewFsAvalible
	.align	2
	.global	FSP_NewLogicFs
	.type	FSP_NewLogicFs, %function
FSP_NewLogicFs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #31
	mov	r8, r0
	mov	r10, r1
	bhi	.L628
	ldr	r4, .L635
	ldr	r0, [r4, r0, asl #2]
	cmp	r0, #0
	beq	.L629
	ldr	r3, .L635+4
	mov	r0, #3
	mov	r7, #0
	ldr	r3, [r3, #12]
	blx	r3
	ldr	r5, [r4, r8, asl #2]
	mov	r3, r5
.L595:
	ldrsb	r2, [r3, #144]
	cmp	r2, #0
	bne	.L593
	ldrsb	r9, [r3, #145]
	cmp	r9, #0
	beq	.L630
.L593:
	add	r7, r7, #1
	add	r3, r3, #680
	cmp	r7, #32
	bne	.L595
.L596:
	ldr	r1, .L635+8
	mov	r0, #0
	bl	dprint_vfmw
.L627:
	ldr	r3, .L635+4
	mov	r0, #3
	ldr	r3, [r3, #16]
	blx	r3
	mvn	r0, #0
.L624:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L630:
	mov	r4, #680
	mul	r4, r4, r7
	add	r3, r5, r4
	add	r4, r4, #144
	add	r1, r3, #144
	adds	r4, r5, r4
	strb	r7, [r1, #3]
	strb	r9, [r1, #2]
	beq	.L596
	cmp	r10, #0
	str	r9, [r3, #172]
	str	r9, [r3, #176]
	str	r9, [r3, #152]
	bne	.L597
	add	r2, r5, #24576
	add	ip, r5, #56
	str	ip, [r3, #172]
	mov	r0, #1
	str	ip, [r3, #176]
	ldr	r2, [r2, #2960]
	str	r2, [r3, #152]
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	strb	r0, [r1, #2]
	sub	r3, r3, #1
	strb	r3, [r1, #4]
.L598:
	mov	r0, #680
	add	r3, r4, #544
	mul	r7, r0, r7
	str	r3, [fp, #-52]
	mov	lr, #1
	mov	r1, #0
	mov	r2, #640
	add	r3, r5, r7
	add	r0, r7, #184
	add	r9, r3, #144
	add	r0, r5, r0
	ldr	r8, [r3, #176]
	mov	r7, r1
	strb	lr, [r3, #145]
	strb	lr, [r8, #2]
	str	lr, [r3, #168]
	ldr	r6, [r3, #172]
	ldr	lr, [r5, #12]
	str	lr, [r3, #164]
	str	lr, [r6, #72]
	ldr	r10, [r3, #164]
	ldr	lr, [r3, #176]
	str	r10, [lr, #72]
	ldr	lr, [r5, #12]
	add	lr, lr, #1
	str	lr, [r5, #12]
	ldr	r5, [r3, #172]
	ldr	r10, [r3, #176]
	ldr	r3, .L635+4
	ldr	ip, [r3, #48]
	blx	ip
	ldrsb	r3, [r9, #3]
	str	r3, [r4, #188]
	ldr	r3, [r5, #52]
	str	r3, [r4, #108]
	ldr	r3, [r5, #56]
	str	r3, [r4, #112]
	ldr	r3, [r10, #24]
	str	r3, [r4, #152]
	ldr	r3, [r10, #28]
	str	r3, [r4, #156]
	ldr	r3, [r10, #44]
	str	r3, [r4, #176]
	ldr	r3, [r10, #48]
	str	r3, [r4, #180]
	ldr	r0, [r5, #8]
	str	r0, [r4, #76]
	bl	MEM_Phy2Vir
	ldr	r6, [fp, #-52]
	str	r0, [r4, #544]
	str	r7, [r6, #4]
	ldr	r3, [r5, #60]
	ldr	r0, [r4, #76]
	add	r0, r3, r0
	str	r0, [r4, #80]
	bl	MEM_Phy2Vir
	str	r7, [r4, #556]
	ldr	lr, [r4, #76]
	add	ip, r4, #576
	str	r0, [r4, #552]
	ldr	r1, [r10, #8]
	str	r1, [r4, #60]
	ldr	r3, [r10, #60]
	add	r3, r1, r3
	str	r3, [r4, #64]
	ldr	r2, [r10, #24]
	add	r2, r2, r1
	str	r2, [r4, #68]
	ldr	r2, [r10, #28]
	add	r3, r3, r2
	str	r3, [r4, #72]
	ldr	r3, [r5, #32]
	str	r3, [r4, #184]
	ldr	r3, [r5, #36]
	add	r3, r3, lr
	str	r3, [r4, #84]
	ldrd	r2, [r6]
	ldr	r10, [r5, #36]
	strd	r2, [fp, #-52]
	adds	r2, r2, r10
	adc	r3, r3, r10, asr #31
	strd	r2, [ip, #-8]
	ldr	r2, [r5, #40]
	ldr	r3, [r5, #36]
	add	r3, r3, r2
	add	lr, r3, lr
	str	lr, [r4, #88]
	ldr	r2, [r5, #40]
	ldr	lr, [r5, #36]
	mov	r3, r2, asr #31
	adds	r0, r2, lr
	adc	r1, r3, lr, asr #31
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #-52]
	adds	r0, r0, r2
	adc	r1, r1, r3
	mov	r2, r0
	mov	r3, r1
	strd	r2, [ip]
	ldr	r3, [r5, #20]
	str	r3, [r4, #252]
	ldr	r0, [r5, #20]
	bl	MEM_Phy2Vir
	str	r7, [r4, #564]
	str	r0, [r4, #560]
	ldr	r0, [r5, #16]
	str	r0, [r4, #464]
	bl	MEM_Phy2Vir
	ldr	r3, .L635+4
	str	r7, [r4, #476]
	ldr	r3, [r3, #16]
	str	r0, [r4, #472]
	mov	r0, #3
	blx	r3
	ldrsb	r0, [r9, #3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L597:
	mov	r0, r8
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L599
	ldrsb	r3, [r5, #3]
	cmp	r3, #0
	ble	.L601
	add	r10, r5, #21760
	add	r10, r10, #144
	b	.L603
.L631:
	ldrsb	r3, [r5, #3]
	add	r10, r10, #88
	cmp	r9, r3
	bge	.L601
.L603:
	mov	r1, r10
	mov	r0, r8
	bl	FSP_IsDecFsAvailable
	add	r9, r9, #1
	cmp	r0, #1
	bne	.L631
.L626:
	str	r10, [r4, #28]
.L601:
	mov	r9, #680
	mla	r9, r9, r7, r5
	add	r10, r9, #168
	ldr	r0, [r10, #4]
	cmp	r0, #0
	beq	.L632
	ldrsb	r3, [r5, #5]
	cmp	r3, #0
	ble	.L608
	mov	r0, r8
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L609
	ldrsb	r0, [r5, #5]
	add	ip, r5, #24576
	cmp	r0, #0
	ble	.L610
	movw	r3, #2964
	ldrh	r3, [ip, r3]
	cmp	r3, #1
	beq	.L611
	mov	r3, #0
	b	.L612
.L614:
	add	r1, r5, r2, lsl #3
	ldrh	r1, [r1, #4]
	cmp	r1, #1
	beq	.L633
.L612:
	add	r3, r3, #1
	cmp	r3, r0
	add	r2, r3, #3440
	add	r2, r2, #2
	bne	.L614
.L610:
	cmp	r0, #0
	ldr	lr, [r5, #8]
	ble	.L616
.L613:
	mov	r2, #0
	mov	r1, r2
.L615:
	mov	r3, r2, asl #3
	add	r2, r2, #1
	add	r3, r3, #27392
	cmp	r2, r0
	add	r3, r3, #149
	strb	r1, [r5, r3]
	bne	.L615
.L616:
	mov	r8, #680
	mov	r3, #0
	mla	r8, r8, r7, r5
	mov	r0, r3
	ldr	r1, .L635+12
	strb	r3, [r8, #148]
	ldr	r3, [ip, #2960]
	str	lr, [r8, #156]
	str	r3, [r8, #152]
	bl	dprint_vfmw
	ldr	r0, [r8, #172]
.L608:
	mov	r3, #680
	mla	r3, r3, r7, r5
	str	r0, [r3, #176]
	b	.L598
.L599:
	ldr	r2, .L635+16
	add	r10, r5, #21760
	add	r10, r10, #144
	add	r9, r5, #24576
	mov	r6, r4
	add	r9, r9, #144
	ldr	r2, [r2, r8, asl #2]
	mov	r4, r10
	add	r2, r2, #593920
	ldr	r3, [r2, #516]
	mov	r10, r3
	b	.L606
.L605:
	add	r4, r4, #88
	cmp	r4, r9
	beq	.L634
.L606:
	mov	r1, r4
	mov	r0, r8
	bl	FSP_IsDecFsAvailable
	cmp	r0, #1
	bne	.L605
	ldr	r2, [r4, #12]
	cmp	r10, r2
	bne	.L605
	mov	r10, r4
	mov	r4, r6
	b	.L626
.L634:
	mov	r4, r6
	b	.L601
.L633:
	mov	r1, #680
	cmp	r3, r0
	mla	r1, r1, r7, r5
	strb	r3, [r1, #148]
	ldr	r3, [r5, r2, asl #3]
	str	r3, [r1, #152]
	ldr	lr, [r5, #8]
	str	lr, [r1, #156]
	bge	.L613
.L617:
	mov	r3, #680
	mla	r3, r3, r7, r5
	ldr	r0, [r3, #172]
	b	.L608
.L609:
	add	r3, r5, #24576
	mov	r1, #0
	strb	r1, [r9, #148]
	ldr	r3, [r3, #2960]
	str	r3, [r9, #152]
	ldr	r3, [r5, #8]
	str	r3, [r9, #156]
	ldr	r0, [r10, #4]
	b	.L608
.L628:
	ldr	r3, .L635+20
	mov	r2, #908
	ldr	r1, .L635+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L624
.L629:
	ldr	r3, .L635+28
	movw	r2, #909
	ldr	r1, .L635+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L624
.L611:
	mov	r2, #0
	strb	r2, [r9, #148]
	ldr	r3, [ip, #2960]
	str	r3, [r9, #152]
	ldr	r3, [r5, #8]
	str	r3, [r9, #156]
	b	.L617
.L632:
	ldr	r2, .L635+32
	ldr	r1, .L635+36
	bl	dprint_vfmw
	b	.L627
.L636:
	.align	2
.L635:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC25
	.word	.LC27
	.word	s_pstVfmwChan
	.word	.LC2
	.word	.LC1
	.word	.LC4
	.word	.LANCHOR1
	.word	.LC26
	UNWIND(.fnend)
	.size	FSP_NewLogicFs, .-FSP_NewLogicFs
	.align	2
	.global	FSP_SetSingleFrameBuf
	.type	FSP_SetSingleFrameBuf, %function
FSP_SetSingleFrameBuf:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #31
	bhi	.L684
	ldr	r3, .L688
	ldr	r6, [r3, r0, asl #2]
	add	r2, r6, #290816
	add	r3, r6, #294912
	ldr	r5, [r2, #1116]
	ldr	lr, [r3, #576]
	cmp	r5, #32
	movge	r5, #32
	str	r5, [r2, #3488]
	ldr	r3, [r1]
	cmp	r3, #255
	beq	.L657
	ldrb	r4, [r2, #3912]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L641
	movw	r3, #32596
	mov	r4, #1
	movt	r3, 4
	add	r3, r6, r3
	b	.L642
.L686:
	add	r4, r4, #1
	cmp	r4, #32
	beq	.L685
.L642:
	ldrb	ip, [r3]	@ zero_extendqisi2
	add	r3, r3, #12
	cmp	ip, #0
	bne	.L686
.L641:
	ldr	r3, [r1, #32]
	mov	ip, r4, asl #4
	sub	ip, ip, r4, asl #2
	mov	r7, #1
	add	r3, r3, #1020
	add	ip, r2, ip
	add	r3, r3, #3
	add	r8, r2, r4, lsl #2
	bic	r3, r3, #1020
	bic	r3, r3, #3
	str	r3, [ip, #3904]
	ldr	r9, [r1, #12]
	add	r3, r3, lr
	strb	r7, [ip, #3912]
	str	r9, [ip, #3908]
	ldr	lr, [r2, #3500]
	add	lr, lr, r7
	str	lr, [r2, #3500]
	str	r3, [r8, #3520]
	ldr	r3, [r1, #4]
	cmp	r3, #255
	beq	.L640
	ldr	r8, [r1, #48]
	add	lr, ip, #4288
	movw	r3, #4296
	str	r8, [lr]
	strb	r7, [ip, r3]
	ldr	r3, [r2, #3508]
	add	r3, r3, #1
	str	r3, [r2, #3508]
.L640:
	ldr	r3, [r1, #8]
	cmp	r3, #255
	beq	.L655
	ldrb	r3, [r2, #3652]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L661
	mov	ip, #1
.L645:
	mov	lr, ip, asl #3
	movw	r3, #32324
	movt	r3, 4
	add	r3, lr, r3
	add	ip, ip, #1
	ldrb	r3, [r6, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L644
	cmp	ip, #32
	bne	.L645
.L655:
	ldr	ip, .L688+4
	mov	r3, #0
	ldr	ip, [ip, r0, asl #2]
	add	lr, ip, #20480
	strb	r5, [ip, #3]
	strb	r3, [ip, #4]
	ldrb	r6, [r2, #3496]	@ zero_extendqisi2
	strb	r6, [ip, #5]
	ldr	r7, [lr, #1508]
	cmp	r7, r3
	beq	.L659
	add	r0, ip, #22016
	mov	r3, #1
	add	r0, r0, #60
	b	.L648
.L647:
	add	r3, r3, #1
	cmp	r3, #32
	beq	.L687
.L648:
	ldr	r5, [r0]
	add	r0, r0, #88
	cmp	r5, #0
	bne	.L647
	mov	r7, r3
.L646:
	mov	r0, #88
	mov	r5, r4, asl #4
	mla	r3, r0, r3, ip
	sub	r5, r5, r4, asl #2
	ldr	r8, [ip, #16]
	sxtb	r0, r6
	add	r5, r2, r5
	str	r0, [fp, #-48]
	add	r0, r3, #21760
	add	r6, r8, #1
	str	r6, [ip, #16]
	movw	r9, #21912
	str	r7, [r0, #148]
	add	r4, r2, r4, lsl #2
	ldr	r7, [r5, #3904]
	movw	r10, #21928
	movw	r8, #21944
	str	r7, [r3, r9]
	movw	r9, #21936
	ldr	r5, [r5, #3908]
	movw	r7, #21952
	str	r5, [r0, #156]
	ldr	r4, [r4, #3520]
	str	r4, [r0, #164]
	ldr	r4, [r2, #3444]
	str	r4, [r3, r10]
	movw	r10, #21960
	ldr	r4, [r2, #3448]
	str	r4, [r0, #172]
	ldr	r4, [r2, #3460]
	str	r4, [r3, r9]
	mov	r4, r0
	ldr	r9, [r2, #3468]
	str	r9, [r0, #180]
	movw	r9, #21968
	ldr	r6, [r2, #3472]
	str	r6, [r3, r8]
	mov	r6, #0
	ldr	r8, [r2, #3452]
	str	r8, [r0, #188]
	ldr	r5, [r2, #3456]
	str	r5, [r3, r7]
	ldr	r7, [ip, #40]
	str	r7, [r0, #196]
	ldr	r8, [ip, #44]
	str	r8, [r3, r10]
	ldr	r10, [r2, #3476]
	str	r10, [r0, #204]
	ldr	r10, [r2, #3480]
	str	r10, [r3, r9]
	mov	r9, #1
	ldr	r3, [r2, #3484]
	strb	r6, [r0, #145]
	strb	r6, [r0, #146]
	str	r3, [r0, #212]
	str	r9, [r4, #228]
	ldr	r0, [fp, #-48]
	ldr	r3, [ip, #20]
	cmp	r3, r0
	bcs	.L650
	ldr	r0, [r1, #8]
	cmp	r0, #255
	beq	.L650
	add	r4, r2, r3, lsl #3
	add	r0, ip, r3, lsl #3
	add	r0, r0, #24576
	add	r3, r3, #1
	ldr	r4, [r4, #3648]
	strb	r6, [r0, #2965]
	strb	r9, [r0, #2964]
	str	r4, [r0, #2960]
	str	r3, [ip, #20]
.L650:
	ldr	r0, [ip, #24]
	ldr	r3, [r2, #3488]
	cmp	r0, r3
	bcs	.L651
	ldr	r3, [r1, #4]
	cmp	r3, #255
	beq	.L651
	ldr	r3, [r2, #3508]
	mov	r4, #88
	mla	r4, r4, r0, ip
	sub	r1, r3, #1
	movw	r5, #21920
	add	r0, r0, #1
	mov	r3, r1, asl #4
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	add	r3, r3, #4288
	ldr	r3, [r3]
	str	r3, [r4, r5]
	str	r0, [ip, #24]
.L651:
	ldr	r3, [ip, #140]
	ldr	r1, [r2, #3492]
	cmp	r3, #0
	str	r1, [ip, #8]
	movne	r0, #0
	bne	.L677
	str	r3, [ip, #60]
	mov	r0, r3
	ldr	lr, [lr, #1432]
	mov	r1, #1
	str	lr, [ip, #64]
	ldr	lr, [r2, #3444]
	str	lr, [ip, #80]
	ldr	lr, [r2, #3448]
	str	r7, [ip, #108]
	str	r8, [ip, #112]
	str	lr, [ip, #84]
	ldr	lr, [r2, #3476]
	str	lr, [ip, #116]
	ldr	lr, [r2, #3480]
	str	lr, [ip, #120]
	ldr	r2, [r2, #3484]
	strb	r3, [ip, #57]
	strb	r3, [ip, #58]
	str	r2, [ip, #124]
	str	r1, [ip, #140]
.L677:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L687:
	ldr	r2, .L688+8
	mov	r0, #1
	ldr	r1, .L688+12
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L657:
	mov	r4, #0
	b	.L640
.L685:
	ldr	r2, .L688+8
	mov	r0, #1
	ldr	r1, .L688+16
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L659:
	mov	r3, r7
	b	.L646
.L684:
	ldr	r3, .L688+20
	movw	r2, #1688
	ldr	r1, .L688+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L677
.L661:
	mov	lr, r3
.L644:
	ldr	ip, [r1, #64]
	add	lr, r6, lr
	add	lr, lr, #290816
	mov	r3, #1
	str	ip, [lr, #3648]
	strb	r3, [lr, #3652]
	ldr	r3, [r2, #3504]
	add	r3, r3, #1
	str	r3, [r2, #3504]
	b	.L655
.L689:
	.align	2
.L688:
	.word	s_pstVfmwChan
	.word	.LANCHOR0
	.word	.LANCHOR1+16
	.word	.LC29
	.word	.LC28
	.word	.LC2
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_SetSingleFrameBuf, .-FSP_SetSingleFrameBuf
	.align	2
	.global	FSP_GetInst
	.type	FSP_GetInst, %function
FSP_GetInst:
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
	cmp	r0, #31
	bhi	.L693
	ldr	r3, .L694
	ldr	r0, [r3, r0, asl #2]
	ldmfd	sp, {fp, sp, pc}
.L693:
	mov	r3, r0
	ldr	r2, .L694+4
	ldr	r1, .L694+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L695:
	.align	2
.L694:
	.word	.LANCHOR0
	.word	.LANCHOR1+40
	.word	.LC30
	UNWIND(.fnend)
	.size	FSP_GetInst, .-FSP_GetInst
	.global	s_pFspInst
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.13716, %object
	.size	__func__.13716, 15
__func__.13716:
	.ascii	"FSP_NewLogicFs\000"
	.space	1
	.type	__func__.13908, %object
	.size	__func__.13908, 22
__func__.13908:
	.ascii	"FSP_SetSingleFrameBuf\000"
	.space	2
	.type	__func__.13918, %object
	.size	__func__.13918, 12
__func__.13918:
	.ascii	"FSP_GetInst\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"pFspInst = NULL\000" )
.LC1:
	ASCII(.ascii	"fsp.c,L%d: %s\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"InstID out of range\000" )
.LC3:
	ASCII(.ascii	"fsp instance not in used\000" )
	.space	3
.LC4:
	ASCII(.ascii	"fsp is not inited\000" )
	.space	2
.LC5:
	ASCII(.ascii	"fsp is already inited\000" )
	.space	2
.LC6:
	ASCII(.ascii	"pstFspInstCfg = NULL\000" )
	.space	3
.LC7:
	ASCII(.ascii	"This inst is not active\000" )
.LC8:
	ASCII(.ascii	"user set decode channel max resolution is (w=%d,h=%" )
	ASCII(.ascii	"d), this stream (w=%d,h=%d) can NOT be decoded!\012" )
	ASCII(.ascii	"\000" )
.LC9:
	ASCII(.ascii	"DFS, Wrong Partition State. State: 0x%x\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"DFS, Mem Element Fill Successed! Ready to Decode!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC11:
	ASCII(.ascii	"Fsp arrange failed, return %d\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"arrange ret %d, min = %d, actual = %d\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"LogicFrameID out of range\000" )
	.space	2
.LC14:
	ASCII(.ascii	"fsp.c, line %d: pstLogicFs->PmvIdc out of range(=%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"FSP_GetRef: InstID out of range\000" )
.LC16:
	ASCII(.ascii	"FSP_GetRef: LogicFrameID out of range\000" )
	.space	2
.LC17:
	ASCII(.ascii	"FSP_SetDisplay: LogicTick=%d, DispTick=%d!\012\000" )
.LC18:
	ASCII(.ascii	"pstVoQue is NULL\000" )
	.space	3
.LC19:
	ASCII(.ascii	"PhyFsID out of range\000" )
	.space	3
.LC20:
	ASCII(.ascii	"DecFsAddrTab is NULL\012\000" )
	.space	2
.LC21:
	ASCII(.ascii	"DecFsNum is NULL\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"PmvAddrTab is NULL\012\000" )
.LC23:
	ASCII(.ascii	"PmvNum is NULL\012\000" )
.LC24:
	ASCII(.ascii	"FSP_IsFsLeak: fsp is not inited \012\000" )
	.space	2
.LC25:
	ASCII(.ascii	"no logic frame store!!!\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"%s no decode phy fs\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"no pmv memory\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"%s no free frame record position.\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"%s no free dec fs record position.\012\000" )
.LC30:
	ASCII(.ascii	"%s InstID %d out of range\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	s_pFspInst, %object
	.size	s_pFspInst, 128
s_pFspInst:
	.space	128
	.type	MemArrange.13666, %object
	.size	MemArrange.13666, 1232
MemArrange.13666:
	.space	1232
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
