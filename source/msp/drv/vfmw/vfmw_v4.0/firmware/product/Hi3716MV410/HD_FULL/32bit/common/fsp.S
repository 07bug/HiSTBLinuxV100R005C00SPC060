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
	.global	FSP_Init
	.type	FSP_Init, %function
FSP_Init:
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
	ldr	r4, .L5
	mov	r2, #64
	mov	r1, #0
	ldr	r0, .L5+4
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #4224
	mov	r1, #0
	ldr	r0, .L5+8
	blx	r3
	ldr	r3, .L5+8
	mvn	r1, #0
	add	r2, r3, #4224
.L2:
	strh	r1, [r3, #2]	@ movhi
	add	r3, r3, #264
	cmp	r3, r2
	bne	.L2
	ldr	lr, .L5+12
	mov	r3, #0
	ldr	ip, [r4, #48]
	mov	r1, r3
	mov	r2, #16
	ldr	r0, .L5+16
	str	r3, [lr, #-3896]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	ip
.L6:
	.align	2
.L5:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LANCHOR0+64
	.word	.LANCHOR1
	.word	.LANCHOR1-3892
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L12
	ldr	r3, .L14
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #4]
	cmp	r2, #1
	bne	.L13
	ldrb	r2, [r1]	@ zero_extendqisi2
	mov	r0, #0
	strb	r2, [r3, #1]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L13:
	ldr	ip, .L14+4
	mov	r2, #238
	ldr	r3, .L14+8
.L11:
	ldr	r1, .L14+12
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L12:
	ldr	ip, .L14+4
	mov	r2, #237
	ldr	r3, .L14+16
	b	.L11
.L15:
	.align	2
.L14:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	.word	.LC0
	UNWIND(.fnend)
	.size	FSP_ConfigAttribute, .-FSP_ConfigAttribute
	.align	2
	.global	FSP_ClearContext
	.type	FSP_ClearContext, %function
FSP_ClearContext:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 560
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #564)
	sub	sp, sp, #564
	subs	r4, r0, #0
	beq	.L33
	ldr	r5, .L35
	mov	r2, #544
	mov	r1, #0
	sub	r0, fp, #588
	ldr	r3, [r5, #48]
	blx	r3
	ldrsb	r0, [r4]
	bl	VCTRL_GetChanVoQue
	cmp	r0, #0
	beq	.L32
	ldrh	r3, [r0, #4]
	ldrh	r2, [r0, #6]
	cmp	r2, r3
	beq	.L32
	cmp	r3, #63
	bls	.L34
.L32:
	ldrb	r7, [r4]	@ zero_extendqisi2
.L20:
	add	r6, r4, #20
	ldrb	r8, [r4, #10]	@ zero_extendqisi2
	ldrb	r10, [r4, #1]	@ zero_extendqisi2
	mov	r2, #16
	ldr	r9, [r4, #4]
	mov	r1, r6
	ldr	r3, [r5, #52]
	sub	r0, fp, #604
	blx	r3
	ldr	r3, [r5, #48]
	movw	r2, #22296
	mov	r1, #0
	mov	r0, r4
	blx	r3
	strb	r10, [r4, #1]
	str	r9, [r4, #4]
	sub	r1, fp, #604
	strb	r8, [r4, #10]
	mov	r0, r6
	strb	r7, [r4]
	mov	r2, #16
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r0, [fp, #-416]
	cmp	r0, #0
	beq	.L18
	ldr	r2, .L35
	mvn	r3, #540
	sub	r1, fp, #588
	ldr	r5, [r2, #52]
	sub	r2, fp, #44
	ldrsb	r0, [r2, r3]
	mov	r2, #544
	mov	r3, r0, asl #9
	add	r0, r3, r0, lsl #5
	add	r0, r0, #72
	add	r0, r4, r0
	blx	r5
	mov	r0, #0
.L18:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L34:
	add	r0, r0, r3, lsl #2
	ldrb	r7, [r4]	@ zero_extendqisi2
	ldr	r2, [r0, #12]
	sxtb	r3, r7
	ldr	r1, [r2, #196]
	cmp	r3, #15
	cmpls	r1, #31
	bhi	.L20
	ldr	r2, .L35+4
	ldr	r3, [r2, r3, asl #2]
	cmp	r3, #0
	beq	.L20
	mov	r2, r1, asl #9
	add	r1, r2, r1, lsl #5
	add	r1, r1, #72
	adds	r1, r3, r1
	beq	.L20
	ldr	r3, [r5, #52]
	mov	r2, #544
	sub	r0, fp, #588
	blx	r3
	b	.L32
.L33:
	ldr	ip, .L35
	mov	r2, #264
	ldr	r3, .L35+8
	ldr	r1, .L35+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L18
.L36:
	.align	2
.L35:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	.LC3
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_ClearContext, .-FSP_ClearContext
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
	cmp	r0, #15
	mov	r6, r0
	bhi	.L42
	ldr	r3, .L44
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L43
	ldr	r5, [r4, #4]
	cmp	r5, #0
	bne	.L41
	ldr	r3, .L44+4
	movw	r2, #22296
	mov	r1, r5
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
	add	r3, r4, #20480
	mov	r2, #1
	mov	r0, r5
	str	r2, [r4, #4]
	str	r5, [r3, #1800]
	strb	r6, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L41:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L42:
	ldr	ip, .L44+4
	mov	r2, #324
	ldr	r3, .L44+8
	mov	r0, #0
	ldr	r1, .L44+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L43:
	ldr	ip, .L44+4
	mov	r0, r4
	ldr	r3, .L44+16
	movw	r2, #325
	ldr	r1, .L44+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L45:
	.align	2
.L44:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	.word	.LC4
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
	cmp	r0, #15
	bhi	.L51
	ldr	r3, .L53
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L52
	ldr	r3, [r0, #4]
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [r0, #4]
	ldmfd	sp, {fp, sp, pc}
.L51:
	ldr	ip, .L53+4
	movw	r2, #349
	ldr	r3, .L53+8
	mov	r0, #0
.L50:
	ldr	r1, .L53+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L52:
	ldr	ip, .L53+4
	movw	r2, #350
	ldr	r3, .L53+16
	b	.L50
.L54:
	.align	2
.L53:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
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
	ldr	r5, .L66
	mov	r4, #0
	b	.L57
.L56:
	add	r4, r4, #1
	cmp	r4, #16
	beq	.L65
.L57:
	ldr	r3, [r5, #4]!
	cmp	r3, #0
	beq	.L56
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L56
	mov	r0, r4
	add	r4, r4, #1
	bl	FSP_DisableInstance
	cmp	r4, #16
	bne	.L57
.L65:
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L67:
	.align	2
.L66:
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
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	mov	r7, r0
	bhi	.L89
	ldr	r3, .L94
	ldr	r8, [r3, r0, asl #2]
	cmp	r8, #0
	beq	.L90
	ldr	r6, .L94+4
	add	r4, r8, #17408
	add	r5, r8, #19712
	ldr	r10, .L94+8
	add	r4, r4, #142
	add	r5, r5, #14
	mov	r9, r6
	b	.L78
.L75:
	ldrsb	r3, [r4]
	cmp	r3, #0
	bne	.L91
.L73:
	add	r4, r4, #68
	cmp	r4, r5
	beq	.L92
.L78:
	ldr	r1, [r4, #10]
	cmp	r1, #0
	beq	.L73
	ldr	r3, [r6, #-3896]
	cmp	r3, #0
	beq	.L73
	ldrsb	r3, [r4, #-2]
	cmp	r3, #0
	beq	.L75
	ldr	r3, [r9, #-3880]
	cmp	r3, #0
	beq	.L93
	mov	r2, #0
	mov	r0, r7
	blx	r3
	ldrsb	r3, [r4]
	cmp	r3, #0
	beq	.L73
.L91:
	ldr	r3, [r6, #-3884]
	add	r4, r4, #68
	ldr	r1, [r4, #-58]
	cmp	r3, #0
	moveq	r0, r3
	ldreq	r1, .L94+12
	ldreq	r3, [r10, #68]
	movne	r0, r7
	blx	r3
	cmp	r4, r5
	bne	.L78
.L92:
	mov	r0, r8
	bl	FSP_ClearContext
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L89:
	ldr	ip, .L94+8
	movw	r2, #370
	ldr	r3, .L94+16
	mov	r0, #0
	ldr	r1, .L94+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L93:
	mov	r0, r3
	ldr	r1, .L94+24
	ldr	r3, [r10, #68]
	blx	r3
	b	.L75
.L90:
	ldr	ip, .L94+8
	mov	r0, r8
	ldr	r3, .L94+28
	movw	r2, #371
	ldr	r1, .L94+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L95:
	.align	2
.L94:
	.word	.LANCHOR0
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC6
	.word	.LC0
	.word	.LC1
	.word	.LC5
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_ResetInstance, .-FSP_ResetInstance
	.align	2
	.global	FSP_EmptyInstance
	.type	FSP_EmptyInstance, %function
FSP_EmptyInstance:
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
	cmp	r0, #15
	mov	r9, r0
	bhi	.L127
	ldr	r3, .L132
	ldr	r7, [r3, r0, asl #2]
	cmp	r7, #0
	beq	.L128
	ldr	r10, .L132+4
	mov	r2, #17408
	mov	r1, #0
	add	r0, r7, #72
	ldr	r3, [r10, #48]
	blx	r3
	ldrsb	r3, [r7, #10]
	cmp	r3, #0
	ble	.L110
	add	r4, r7, #17408
	ldr	r8, .L132+8
	mov	r6, #0
	add	r4, r4, #200
	mov	r5, r6
.L109:
	ldr	r1, [r4, #-48]
	cmp	r1, #0
	beq	.L104
	ldr	r3, [r8, #-3896]
	cmp	r3, #0
	beq	.L104
	ldrsb	r3, [r4, #-60]
	cmp	r3, #0
	bne	.L129
.L106:
	ldrsb	r3, [r4, #-58]
	cmp	r3, #0
	bne	.L130
.L104:
	strb	r5, [r4, #-60]
	add	r6, r6, #1
	strb	r5, [r4]
	add	r4, r4, #68
	strb	r5, [r4, #-126]
	str	r5, [r4, #-72]
	ldrsb	r3, [r7, #10]
	cmp	r3, r6
	bgt	.L109
.L110:
	ldrsb	r0, [r7, #11]
	cmp	r0, #0
	addgt	r3, r7, #19712
	movgt	r1, #0
	addgt	r3, r3, #12
	movgt	r2, r1
	ble	.L102
.L113:
	add	r1, r1, #1
	strb	r2, [r3]
	cmp	r0, r1
	strb	r2, [r3, #60]
	strb	r2, [r3, #2]
	add	r3, r3, #68
	str	r2, [r3, #-12]
	bne	.L113
.L102:
	ldrsb	r1, [r7, #13]
	cmp	r1, #0
	addgt	r2, r7, #22016
	movgt	r3, #0
	addgt	r2, r2, #24
	movgt	r0, r3
	ble	.L112
.L114:
	add	r3, r3, #1
	str	r0, [r2], #12
	cmp	r3, r1
	bne	.L114
.L112:
	mov	r0, #0
	str	r0, [r7, #16]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L130:
	ldr	r3, [r8, #-3884]
	ldr	r1, [r4, #-48]
	cmp	r3, #0
	moveq	r0, r3
	ldreq	r1, .L132+12
	ldreq	r3, [r10, #68]
	movne	r0, r9
	blx	r3
	b	.L104
.L129:
	ldr	r3, .L132+8
	ldr	r3, [r3, #-3880]
	cmp	r3, #0
	beq	.L131
	mov	r2, #0
	mov	r0, r9
	blx	r3
	b	.L106
.L127:
	ldr	ip, .L132+4
	movw	r2, #445
	ldr	r3, .L132+16
	mov	r0, #0
	ldr	r1, .L132+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L128:
	ldr	ip, .L132+4
	mov	r0, r7
	ldr	r3, .L132+24
	movw	r2, #446
	ldr	r1, .L132+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L131:
	mov	r0, r3
	ldr	r1, .L132+28
	ldr	r3, [r10, #68]
	blx	r3
	b	.L106
.L133:
	.align	2
.L132:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC6
	.word	.LC0
	.word	.LC1
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	FSP_EmptyInstance, .-FSP_EmptyInstance
	.align	2
	.global	FSP_ConfigInstance
	.type	FSP_ConfigInstance, %function
FSP_ConfigInstance:
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
	cmp	r0, #15
	mov	r5, r1
	bhi	.L144
	cmp	r1, #0
	beq	.L145
	ldr	r3, .L146
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L138
	ldr	r3, [r4, #4]
	cmp	r3, #1
	bne	.L138
	mov	r0, r4
	bl	FSP_ClearContext
	ldr	r3, .L146+4
	mov	r1, r5
	add	r0, r4, #36
	mov	r2, #32
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L138:
	ldr	ip, .L146+4
	movw	r2, #583
	ldr	r3, .L146+8
.L143:
	ldr	r1, .L146+12
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L144:
	ldr	ip, .L146+4
	mov	r2, #580
	ldr	r3, .L146+16
	b	.L143
.L145:
	ldr	ip, .L146+4
	mov	r0, r1
	ldr	r3, .L146+20
	movw	r2, #581
	ldr	r1, .L146+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L147:
	.align	2
.L146:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC8
	.word	.LC1
	.word	.LC0
	.word	.LC7
	UNWIND(.fnend)
	.size	FSP_ConfigInstance, .-FSP_ConfigInstance
	.align	2
	.global	FSP_ConfigFrameBuf
	.type	FSP_ConfigFrameBuf, %function
FSP_ConfigFrameBuf:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 872
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #900)
	sub	sp, sp, #900
	mov	r8, r2
	ldr	r2, .L221
	mov	r5, r0
	mov	r7, r1
	sub	r0, fp, #856
	mov	r1, #0
	str	r3, [fp, #-908]
	ldr	r4, [r2, #48]
	mov	r2, #812
	blx	r4
	cmp	r5, #15
	bhi	.L209
	ldr	r3, .L221+4
	ldr	r4, [r3, r5, asl #2]
	cmp	r4, #0
	beq	.L210
	ldr	r6, .L221+8
	ldr	r0, [r6, r5, asl #2]
	add	r3, r0, #229376
	ldr	r9, [r3, #736]
	cmp	r9, #0
	beq	.L211
	ldr	r1, [r4, #44]
	ldr	ip, [r4, #48]
	mul	lr, ip, r1
.L155:
	ldr	r2, [r0, #144]
	ldr	r3, [r0, #148]
	mul	r9, r3, r2
	cmp	r9, lr
	blt	.L212
	ldr	r3, [r0, #1404]
	ldrsb	r9, [r4, #40]
	cmp	r3, #1
	add	r3, r0, #225280
	beq	.L213
.L158:
	ldr	r2, [r3, #3292]
	ldr	r1, .L221+12
	cmp	r9, r2
	ldr	r10, [r1, #48]
	movne	r2, #1
	moveq	r2, #0
	str	r2, [r3, #3312]
	ldrsb	r2, [r4, #40]
	cmp	r10, #0
	str	r2, [r3, #3292]
	beq	.L162
	ldr	r3, [r4, #48]
	sub	ip, fp, #856
	ldr	r2, [r4, #44]
	mov	lr, #40
	str	ip, [sp, #16]
	mov	r1, r8
	str	r5, [sp, #12]
	mov	r0, r7
	ldrsb	ip, [r4, #39]
	str	lr, [sp, #4]
	ldr	r7, .L221+8
	str	ip, [sp, #8]
	ldrsb	ip, [r4, #43]
	str	ip, [sp]
	blx	r10
	ldr	r3, [r6, r5, asl #2]
	add	r3, r3, #229376
	ldr	r3, [r3, #664]
	cmp	r3, #20
	movge	r3, #20
	strb	r3, [r4, #13]
	cmp	r0, #2
	mov	r8, r0
	beq	.L214
	cmp	r0, #0
	bne	.L165
	ldr	r3, [fp, #-436]
	mov	lr, #1
	ldr	r2, .L221
	mov	r0, #31
	ldr	r1, .L221+16
	strb	r3, [r4, #9]
	ldr	r3, [r7, r5, asl #2]
	ldr	r2, [r2, #68]
	add	ip, r3, #229376
	str	r8, [r3, #1444]
	str	lr, [ip, #712]
	blx	r2
	ldr	r3, [fp, #-436]
	ldr	r2, .L221
	cmp	r9, r3
	bgt	.L215
	ldrsb	r3, [r4, #1]
	strb	r8, [r4, #11]
	cmp	r3, #0
	strb	r8, [r4, #12]
	bne	.L216
.L168:
	ldr	r3, [fp, #-436]
	cmp	r3, #32
	movge	r3, #32
	strb	r3, [r4, #10]
.L169:
	ldr	r3, .L221
	mov	r0, #8
	ldr	r3, [r3, #12]
	blx	r3
	ldr	r2, [fp, #-52]
	cmp	r2, #0
	beq	.L217
	ldr	r1, [fp, #-856]
	add	r3, r4, #20480
	str	r3, [fp, #-880]
	sub	r8, fp, #596
	ldr	r10, [r3, #1804]
	mov	r7, #0
	str	r1, [fp, #-864]
	ldr	r1, [fp, #-452]
	add	r2, r2, r10
	ldr	r3, [fp, #-464]
	add	r2, r2, #1
	str	r2, [fp, #-904]
	str	r1, [fp, #-888]
	ldr	r1, [r4, #44]
	ldr	r2, [fp, #-448]
	str	r3, [fp, #-876]
	str	r1, [fp, #-868]
	ldr	r1, [r4, #48]
	ldr	r3, [fp, #-456]
	str	r2, [fp, #-892]
	str	r1, [fp, #-872]
	ldr	r1, [fp, #-440]
	ldr	r2, [fp, #-444]
	ldr	r9, [r6, r5, asl #2]
	str	r3, [fp, #-884]
	mov	r3, r10, asl #6
	add	r3, r3, r10, lsl #2
	str	r1, [fp, #-900]
	sub	r1, fp, #856
	str	r2, [fp, #-896]
	add	r9, r9, #229376
	add	r2, r10, #1
	add	r3, r4, r3
	sub	r10, r1, r10, asl #3
	str	r4, [fp, #-912]
	b	.L173
.L172:
	mov	r1, #1
	str	r1, [r0]
	ldr	r1, [fp, #-880]
	str	r2, [r1, #1804]
	add	r2, r2, #1
	ldr	r1, [fp, #-904]
	cmp	r2, r1
	beq	.L218
.L173:
	add	ip, r3, #17408
	sub	lr, r2, #1
	add	r3, r3, #68
	str	lr, [ip, #144]
	mov	r5, ip
	mov	r1, ip
	ldr	ip, [r10, r2, asl #3]
	mov	r4, r1
	mov	lr, r5
	add	r0, r1, #204
	add	r1, r1, #152
	str	ip, [r1]
	mov	ip, r5
	ldr	r6, [r8, #4]!
	str	r6, [r5, #156]
	ldr	r6, [fp, #-864]
	str	r6, [r4, #160]
	ldr	r4, [fp, #-876]
	str	r4, [lr, #164]
	mov	lr, r5
	ldr	r4, [fp, #-884]
	str	r4, [ip, #168]
	mov	ip, r5
	ldr	r4, [fp, #-888]
	str	r4, [r5, #172]
	mov	r4, r5
	ldr	r5, [fp, #-868]
	str	r5, [lr, #176]
	ldr	r5, [fp, #-872]
	str	r5, [ip, #180]
	mov	ip, lr
	ldr	r5, [fp, #-892]
	str	r5, [r4, #184]
	mov	r4, lr
	ldr	r5, [fp, #-896]
	str	r5, [lr, #188]
	ldr	r5, [fp, #-900]
	str	r5, [ip, #192]
	add	ip, lr, #142
	strb	r7, [r4, #140]
	strb	r7, [lr, #141]
	strb	r7, [lr, #142]
	ldr	lr, [r9, #728]
	cmp	lr, #1
	bne	.L172
	ldr	lr, [r1]
	ldr	r1, [r9, #716]
	cmp	lr, r1
	bcc	.L172
	ldr	r4, [r9, #724]
	add	r1, r1, r4
	cmp	lr, r1
	movcc	r1, #4
	strccb	r1, [ip]
	b	.L172
.L211:
	mov	r0, r5
	bl	VCTRL_GetChanCapLevel
	cmp	r0, #32
	bhi	.L153
	ldr	lr, .L221+20
	mov	r3, r0, asl #5
	sub	r3, r3, r0, asl #2
	ldr	r1, [r4, #44]
	add	r2, lr, r3
	ldr	ip, [r4, #48]
	ldr	r3, [lr, r3]
	ldr	r10, [r2, #4]
	mul	lr, ip, r1
	mul	r2, r10, r3
	cmp	r0, #25
	cmpne	lr, r2
	ble	.L204
	ldrsb	r2, [r4, #39]
	cmp	r2, #1
	bne	.L185
.L204:
	ldr	r0, [r6, r5, asl #2]
	b	.L155
.L212:
	stmia	sp, {r1, ip}
	mov	r0, #0
	ldr	r1, .L221
	ldr	r4, [r1, #68]
	ldr	r1, .L221+24
	blx	r4
	ldr	r3, .L221+28
	ldr	r4, [r3]
	cmp	r4, #0
	mvneq	r0, #0
	beq	.L198
	mov	r3, #0
	mov	r0, r5
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
.L198:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L214:
	ldr	r3, [fp, #-436]
	mov	r2, #1
	strb	r3, [r4, #9]
	ldr	r3, [r7, r5, asl #2]
	str	r2, [r3, #1444]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L213:
	ldr	r2, [r3, #3272]
	bics	r1, r2, #2
	beq	.L158
	cmp	r2, #1
	moveq	r0, #0
	beq	.L198
	mov	r3, #0
	strb	r3, [r4, #9]
	ldr	r3, [r6, r5, asl #2]
	mov	r0, #31
	ldr	r2, .L221
	add	r3, r3, #225280
	ldr	r1, .L221+32
	ldr	r4, [r2, #68]
	ldr	r2, [r3, #3272]
	blx	r4
	mvn	r0, #0
	b	.L198
.L162:
	add	r0, r0, #229376
	mvn	r8, #0
	ldr	r3, [r0, #664]
	cmp	r3, #20
	movge	r3, #20
	strb	r3, [r4, #13]
.L165:
	mov	r3, #0
	ldr	r1, .L221
	strb	r3, [r4, #9]
	mov	r2, r8
	ldr	ip, [r6, r5, asl #2]
	mov	r0, r3
	ldr	r4, [r1, #68]
	ldr	r1, .L221+36
	str	r3, [ip, #1444]
	blx	r4
	mvn	r0, #0
	b	.L198
.L216:
	ldr	r3, [r7, r5, asl #2]
	ldr	r3, [r3, #1404]
	cmp	r3, #1
	beq	.L168
	ldrsb	r3, [r4, #40]
	ldr	r2, [fp, #-436]
	add	r3, r3, #4
	cmp	r3, r2
	movge	r3, r2
	strb	r3, [r4, #10]
	b	.L169
.L153:
	ldrsb	r3, [r4, #39]
	cmp	r3, #1
	bne	.L184
	ldr	r1, [r4, #44]
	ldr	ip, [r4, #48]
	ldr	r0, [r6, r5, asl #2]
	mul	lr, ip, r1
	b	.L155
.L218:
	ldr	r4, [fp, #-912]
.L171:
	ldr	r10, [fp, #-880]
	mov	r5, #1
	mov	lr, #0
	strb	r5, [r4, #12]
	mov	ip, r5
	sub	r6, fp, #44
	str	lr, [r10, #1424]
	mov	r0, lr
	ldrsb	r7, [r4, #10]
	mov	r2, lr
	str	r5, [r10, #1484]
	mov	r1, lr
	ldr	r5, [fp, #-864]
	mov	r3, r4
	add	r6, r6, r7, lsl #3
	ldr	r8, [fp, #-456]
	ldr	r9, [fp, #-452]
	str	r5, [r10, #1440]
	ldr	r5, [fp, #-868]
	ldr	r6, [r6, #-804]
	strb	lr, [r10, #1420]
	str	r5, [r10, #1456]
	ldr	r5, [fp, #-872]
	strb	lr, [r10, #1421]
	strb	lr, [r10, #1422]
	str	r5, [r10, #1460]
	ldr	r5, [fp, #-464]
	str	r6, [r10, #1432]
	str	r8, [r10, #1448]
	str	r5, [r10, #1444]
	ldr	r5, [fp, #-448]
	str	r9, [r10, #1452]
	str	r5, [r10, #1464]
	ldr	r5, [fp, #-444]
	str	r5, [r10, #1468]
	ldr	r5, [fp, #-440]
	str	r5, [r10, #1472]
	strb	lr, [r4, #11]
	ldr	lr, [fp, #-452]
	ldr	r10, [fp, #-464]
	ldr	r9, [fp, #-456]
	str	lr, [fp, #-868]
	ldr	lr, [fp, #-444]
	ldr	r6, [fp, #-440]
	ldr	r8, [fp, #-448]
	str	lr, [fp, #-872]
	str	r6, [fp, #-876]
	b	.L177
.L219:
	add	r0, r7, r2
	add	lr, r3, #19712
	sxtab	r0, r0, ip
	sub	r5, fp, #44
	mov	ip, lr
	str	r2, [lr, #16]
	add	r0, r5, r0, lsl #3
.L205:
	ldr	r0, [r0, #-804]
	mov	r5, ip
	add	r2, r2, #1
	add	r3, r3, #68
	cmp	r2, #32
	str	r0, [ip, #24]
	mov	r0, ip
	ldr	r6, [fp, #-864]
	str	r10, [r5, #36]
	str	r9, [r5, #40]
	str	r6, [r5, #32]
	ldr	lr, [fp, #-868]
	str	lr, [ip, #44]
	mov	lr, ip
	ldr	r5, [r4, #60]
	str	r5, [r0, #48]
	mov	r0, ip
	ldr	r6, [r4, #64]
	mov	r5, ip
	str	r6, [lr, #52]
	str	r8, [ip, #56]
	ldr	r6, [fp, #-872]
	str	r6, [r0, #60]
	ldr	r6, [fp, #-876]
	strb	r1, [r5, #12]
	str	r6, [r5, #64]
	strb	r1, [ip, #13]
	strb	r1, [ip, #14]
	beq	.L176
	ldrb	r0, [r4, #11]	@ zero_extendqisi2
	ldrb	ip, [r4, #12]	@ zero_extendqisi2
.L177:
	sxtb	r0, r0
	cmp	r0, r2
	bhi	.L219
	sxtab	r0, r7, ip
	add	lr, r3, #19712
	sub	r5, fp, #44
	mov	ip, lr
	add	r0, r5, r0, lsl #3
	str	r1, [lr, #16]
	b	.L205
.L176:
	ldr	r3, [fp, #-56]
	cmp	r3, #20
	movge	r3, #20
	strb	r3, [r4, #13]
	ldr	lr, [fp, #-48]
	cmp	lr, #0
	beq	.L182
	ldr	r3, [fp, #-880]
	sub	r0, fp, #856
	mov	r6, #0
	mov	r5, #1
	ldr	r2, [r3, #1808]
	add	lr, r2, lr
	mov	r3, r2, asl #2
	mov	ip, r2, asl #4
	rsb	r1, r3, ip
	add	r1, r1, #22016
	add	r1, r1, #24
	add	r1, r4, r1
.L181:
	rsb	ip, r3, ip
	add	r2, r2, #1
	ldr	r3, [r0, #556]
	add	ip, r4, ip
	add	ip, ip, #22016
	cmp	r2, lr
	add	r0, r0, #12
	add	r1, r1, #12
	str	r3, [r1, #-12]
	mov	r3, r2, asl #2
	str	r6, [ip, #32]
	mov	ip, r2, asl #4
	str	r5, [r1, #-8]
	bne	.L181
	ldr	r3, [fp, #-880]
	str	r2, [r3, #1808]
.L182:
	ldr	r1, [fp, #-60]
	add	r3, r4, #16384
	ldr	r0, [fp, #-880]
	mov	r2, #0
	ldr	r5, [fp, #-464]
	mov	lr, #1
	ldr	r6, [fp, #-448]
	str	r1, [r0, #1556]
	ldr	r1, [fp, #-864]
	ldr	r0, [fp, #-456]
	ldr	ip, [r3, #1176]
	str	r1, [r3, #1116]
	ldr	r1, [fp, #-452]
	str	r5, [r3, #1120]
	str	r2, [r3, #1100]
	str	ip, [r3, #1108]
	str	r0, [r3, #1124]
	str	r1, [r3, #1128]
	ldr	r1, [r4, #44]
	ldr	r5, [fp, #-444]
	str	r1, [r3, #1132]
	ldr	r0, [r4, #48]
	strb	r2, [r3, #1096]
	strb	r2, [r3, #1097]
	strb	r2, [r3, #1098]
	ldr	r2, [fp, #-440]
	str	r0, [r3, #1136]
	str	r6, [r3, #1140]
	str	r5, [r3, #1144]
	str	lr, [r3, #1160]
	str	r2, [r3, #1148]
	ldr	r2, [r4, #20]
	cmp	r1, r2
	beq	.L220
.L179:
	str	r1, [r4, #20]
	str	r0, [r4, #24]
	str	r7, [r4, #28]
	ldr	r3, [r3, #1244]
	rsb	r3, ip, r3
	str	r3, [r4, #32]
.L183:
	ldr	r3, [fp, #-852]
	mov	r0, #8
	ldr	r2, [fp, #-908]
	str	r3, [r2]
	ldr	r3, .L221
	ldr	r3, [r3, #16]
	blx	r3
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L220:
	ldr	r2, [r4, #24]
	cmp	r0, r2
	bne	.L179
	ldr	r2, [r4, #28]
	cmp	r7, r2
	bne	.L179
	b	.L183
.L217:
	ldr	r3, [fp, #-856]
	str	r3, [fp, #-864]
	add	r3, r4, #20480
	str	r3, [fp, #-880]
	ldr	r3, [r4, #44]
	str	r3, [fp, #-868]
	ldr	r3, [r4, #48]
	str	r3, [fp, #-872]
	b	.L171
.L209:
	ldr	r3, .L221
	movw	r2, #942
	mov	r0, #0
	ldr	r1, .L221+40
	ldr	r4, [r3, #68]
	ldr	r3, .L221+44
	blx	r4
	mvn	r0, #0
	b	.L198
.L185:
	stmib	sp, {r1, ip}
	mov	r2, r0
	ldr	r1, .L221
	mov	r0, r9
	str	r10, [sp]
	ldr	r5, [r1, #68]
	ldr	r1, .L221+48
	blx	r5
.L156:
	mov	r3, #0
	mvn	r0, #0
	strb	r3, [r4, #9]
	b	.L198
.L184:
	ldr	r3, .L221
	mov	r2, r0
	ldr	r1, .L221+52
	mov	r0, r9
	ldr	r3, [r3, #68]
	blx	r3
	b	.L156
.L215:
	str	r3, [sp]
	mov	r0, r8
	ldr	r4, [r2, #68]
	mov	r3, r9
	mov	r2, r8
	ldr	r1, .L221+56
	blx	r4
	mvn	r0, #0
	b	.L198
.L210:
	ldr	r3, .L221
	mov	r0, r4
	movw	r2, #943
	ldr	r1, .L221+40
	ldr	r5, [r3, #68]
	ldr	r3, .L221+60
	blx	r5
	mvn	r0, #0
	b	.L198
.L222:
	.align	2
.L221:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	g_vdm_hal_fun_ptr
	.word	.LC13
	.word	CapItem
	.word	.LC11
	.word	g_event_report
	.word	.LC12
	.word	.LC14
	.word	.LC1
	.word	.LC0
	.word	.LC10
	.word	.LC9
	.word	.LC15
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_ConfigFrameBuf, .-FSP_ConfigFrameBuf
	.align	2
	.global	FindLeastTickPhyFs
	.type	FindLeastTickPhyFs, %function
FindLeastTickPhyFs:
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
	cmp	r1, #0
	mov	r2, r0
	mov	r0, #0
	ble	.L227
	mvn	lr, #0
	mov	r3, r0
.L226:
	ldr	ip, [r2, #56]
	add	r2, r2, #64
	cmp	ip, lr
	movcc	r0, r3
	add	r3, r3, #1
	movcc	lr, ip
	cmp	r3, r1
	bne	.L226
	ldmfd	sp, {fp, sp, pc}
.L227:
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	FindLeastTickPhyFs, .-FindLeastTickPhyFs
	.align	2
	.global	FSP_FirstFsCheck
	.type	FSP_FirstFsCheck, %function
FSP_FirstFsCheck:
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
	ldr	lr, .L242
	ldr	r2, [lr, r0, asl #2]
	cmp	r2, #0
	beq	.L240
	mov	r3, r0, asl #8
	add	r3, r3, r0, lsl #3
	add	r3, lr, r3
	add	r3, r3, #64
	ldrsh	r4, [r3, #2]
	cmn	r4, #1
	beq	.L237
	ldrh	r3, [r3, #4]
	cmp	r3, r4
	beq	.L237
	ldr	r6, [r2, #4]
	add	ip, r2, #16384
	ldr	r5, [r2, #32]
	cmp	r6, #1
	ldr	r2, [ip, #1244]
	ldr	r6, [ip, #1176]
	beq	.L241
.L237:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L241:
	and	r3, r3, #63
	cmp	r4, r3
	beq	.L237
	rsb	r6, r6, r2
	mov	r2, r0, asl #6
	add	r6, r6, r1
	add	r0, r2, r0, lsl #1
.L233:
	add	r2, r0, r3
	add	r3, r3, #1
	and	r3, r3, #63
	add	r2, lr, r2, lsl #2
	ldr	r2, [r2, #72]
	add	ip, r2, r5
	cmp	ip, r1
	bcc	.L232
	cmp	r2, r6
	bls	.L238
.L232:
	cmp	r4, r3
	bne	.L233
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L238:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L240:
	ldr	ip, .L242+4
	mov	r0, r2
	ldr	r3, .L242+8
	mov	r2, #1488
	ldr	r1, .L242+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L243:
	.align	2
.L242:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_FirstFsCheck, .-FSP_FirstFsCheck
	.align	2
	.global	FSP_NewLogicFs
	.type	FSP_NewLogicFs, %function
FSP_NewLogicFs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	cmp	r0, #15
	mov	r8, r0
	mov	r9, r1
	bhi	.L297
	ldr	r4, .L306
	ldr	r0, [r4, r0, asl #2]
	cmp	r0, #0
	beq	.L298
	ldr	r7, .L306+4
	mov	r0, #3
	ldr	r3, [r7, #12]
	blx	r3
	ldr	r5, [r4, r8, asl #2]
	mov	r2, #0
	mov	r3, r5
.L250:
	ldrsb	r1, [r3, #72]
	cmp	r1, #0
	bne	.L248
	ldrsb	r1, [r3, #73]
	cmp	r1, #0
	beq	.L299
.L248:
	add	r2, r2, #1
	add	r3, r3, #544
	cmp	r2, #32
	bne	.L250
.L251:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r1, .L306+8
	blx	r3
	ldr	r3, [r7, #16]
	mov	r0, #3
	blx	r3
	mvn	r0, #0
.L290:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L299:
	mov	r10, r2, asl #5
	mov	r6, r2, asl #9
	add	r4, r10, r6
	add	r3, r5, r4
	add	r4, r4, #72
	add	ip, r3, #72
	adds	r4, r5, r4
	strb	r2, [ip, #3]
	strb	r1, [ip, #2]
	beq	.L251
	add	lr, r3, #592
	add	r0, r3, #600
	cmp	r9, #0
	str	r1, [r3, #592]
	str	r1, [lr, #4]
	str	r1, [r3, #600]
	str	r1, [r0, #4]
	beq	.L252
	ldrsb	r0, [r5, #10]
	cmp	r0, #0
	addgt	r3, r5, #17408
	movgt	r2, r1
	addgt	r3, r3, #204
	bgt	.L257
	b	.L294
.L256:
	add	r2, r2, #1
	add	r3, r3, #68
	cmp	r2, r0
	beq	.L300
.L257:
	ldr	r1, [r3]
	cmp	r1, #1
	bne	.L256
	ldrsb	r1, [r3, #-64]
	cmp	r1, #0
	bne	.L256
	ldrsb	r1, [r3, #-62]
	cmp	r1, #0
	bne	.L256
	mov	r9, r2, asl #6
	add	r3, r10, r6
	add	r9, r9, r2, lsl #2
	add	r3, r5, r3
	add	r9, r5, r9
	add	r9, r9, #17408
	add	r9, r9, #140
	str	r9, [r3, #592]
	b	.L254
.L252:
	add	r1, r5, #20480
	add	r2, r5, #17408
	add	r2, r2, #72
	str	r2, [r3, #592]
	str	r2, [lr, #4]
	mov	lr, #1
	str	r2, [r3, #600]
	ldr	r3, [r1, #1560]
	str	r3, [r0, #4]
	ldrb	r3, [r5, #13]	@ zero_extendqisi2
	strb	lr, [ip, #2]
	sub	r3, r3, #1
	strb	r3, [ip, #4]
.L255:
	add	r6, r10, r6
	mov	lr, #1
	add	r3, r5, r6
	add	r0, r6, #80
	add	r0, r5, r0
	add	r8, r3, #72
	ldr	r6, [r3, #596]
	mov	r1, #0
	strb	lr, [r3, #73]
	mov	r2, #504
	strb	lr, [r6, #2]
	str	lr, [r3, #588]
	ldr	r6, [r3, #592]
	ldr	lr, [r5, #16]
	str	lr, [r3, #584]
	str	lr, [r6, #56]
	ldr	lr, [r3, #596]
	ldr	r6, [r3, #584]
	str	r6, [lr, #56]
	ldr	lr, [r5, #16]
	add	lr, lr, #1
	str	lr, [r5, #16]
	add	r5, r3, #592
	ldr	r10, [r7, #48]
	ldmia	r5, {r5, r6, r9}
	blx	r10
	ldrsb	r3, [r8, #3]
	str	r3, [r4, #204]
	ldr	r3, [r5, #36]
	str	r3, [r4, #172]
	ldr	r3, [r5, #40]
	str	r3, [r4, #176]
	ldr	r3, [r6, #20]
	str	r3, [r4, #200]
	ldr	r2, [r5, #12]
	str	r2, [r4, #112]
	mov	r0, r2
	ldr	r3, [r5, #44]
	add	r3, r3, r2
	str	r3, [r4, #116]
	bl	MEM_Phy2Vir
	str	r0, [r4, #40]
	ldr	r0, [r4, #116]
	bl	MEM_Phy2Vir
	str	r0, [r4, #44]
	ldr	r1, [r6, #12]
	str	r1, [r4, #96]
	ldr	r3, [r6, #44]
	add	r3, r1, r3
	str	r3, [r4, #100]
	ldr	r2, [r6, #20]
	add	r2, r2, r1
	str	r2, [r4, #104]
	ldr	r2, [r6, #20]
	add	r3, r3, r2
	str	r3, [r4, #108]
	ldr	r2, [r6, #12]
	str	r2, [r4, #128]
	mov	r0, r2
	ldr	r3, [r6, #44]
	add	r3, r3, r2
	str	r3, [r4, #132]
	bl	MEM_Phy2Vir
	str	r0, [r4, #56]
	ldr	r0, [r4, #132]
	bl	MEM_Phy2Vir
	str	r0, [r4, #60]
	ldr	r2, [r9, #12]
	str	r2, [r4, #120]
	mov	r0, r2
	ldr	r3, [r5, #44]
	add	r3, r3, r2
	str	r3, [r4, #124]
	bl	MEM_Phy2Vir
	str	r0, [r4, #48]
	ldr	r0, [r4, #124]
	bl	MEM_Phy2Vir
	ldr	ip, [r4, #112]
	ldr	r1, [r4, #40]
	str	r0, [r4, #52]
	ldr	r3, [r5, #24]
	str	r3, [r4, #152]
	ldr	r2, [r5, #28]
	add	r2, r2, ip
	str	r2, [r4, #140]
	ldr	r2, [r5, #28]
	ldr	r3, [r5, #32]
	add	r3, r2, r3
	add	r3, r3, ip
	str	r3, [r4, #148]
	ldr	r3, [r5, #28]
	add	r3, r1, r3
	str	r3, [r4, #136]
	ldr	r2, [r5, #28]
	ldr	r3, [r5, #32]
	add	r3, r3, r2
	add	r1, r1, r3
	str	r1, [r4, #144]
	ldr	r3, [r5, #16]
	str	r3, [r4, #284]
	ldr	r0, [r5, #16]
	bl	MEM_Phy2Vir
	ldr	r3, [r7, #16]
	str	r0, [r4, #64]
	mov	r0, #3
	blx	r3
	ldrsb	r0, [r8, #3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L300:
	add	r3, r10, r6
	add	r3, r5, r3
.L294:
	ldr	r9, [r3, #592]
.L254:
	cmp	r9, #0
	beq	.L301
.L258:
	add	r3, r10, r6
	add	r2, r5, #21760
	add	r3, r5, r3
	add	r2, r2, #140
	str	r2, [r3, #600]
	ldrsb	r0, [r5, #13]
	cmp	r0, #0
	ble	.L268
	add	r3, r5, #22016
	mov	r2, #0
	add	r3, r3, #28
	b	.L273
.L270:
	add	r2, r2, #1
	add	r3, r3, #12
	cmp	r2, r0
	beq	.L302
.L273:
	ldr	r1, [r3]
	cmp	r1, #1
	bne	.L270
	ldr	r1, [r3, #4]
	cmp	r1, #0
	bne	.L270
	mov	r1, r2, asl #4
	add	r3, r10, r6
	sub	r1, r1, r2, asl #2
	add	r3, r5, r3
	add	r1, r5, r1
	movw	ip, #22040
	strb	r2, [r3, #76]
	cmp	r2, r0
	ldr	r2, [r1, ip]
	add	ip, r5, #20480
	str	r2, [r3, #604]
	ldr	lr, [ip, #1556]
	str	lr, [r3, #608]
	bge	.L271
.L268:
	ldr	r3, .L306+12
	add	r9, r10, r6
	add	r9, r5, r9
	ldr	r2, [r3, #-3896]
	ldr	r1, [r9, #592]
	cmp	r2, #0
	str	r1, [r9, #596]
	beq	.L255
	mov	r0, r8
	str	r3, [fp, #-84]
	bl	VCTRL_GetImageWidth
	str	r0, [fp, #-80]
	mov	r0, r8
	bl	VCTRL_GetImageHeight
	ldr	r3, [fp, #-84]
	ldr	r2, [fp, #-80]
	ldr	r3, [r3, #-3888]
	subs	ip, r3, #0
	beq	.L303
	mov	r3, r0
	sub	r1, fp, #72
	mov	r0, r8
	blx	ip
	cmp	r0, #0
	bne	.L277
	ldr	r8, [fp, #-72]
	cmp	r8, #0
	beq	.L304
	ldr	r3, [r9, #592]
	movw	r0, #22040
	str	r8, [r3, #12]
	ldrsb	r1, [r9, #76]
	ldr	r2, [fp, #-56]
	mov	r3, r1, asl #4
	sub	r3, r3, r1, asl #2
	str	r2, [r9, #604]
	add	r3, r5, r3
	str	r2, [r3, r0]
	b	.L255
.L302:
	add	ip, r5, #20480
	cmp	r0, #0
	ldr	lr, [ip, #1556]
	ble	.L275
.L271:
	add	r2, r5, #22016
	mov	r3, #0
	add	r2, r2, #32
	mov	r1, r3
.L274:
	add	r3, r3, #1
	str	r1, [r2], #12
	cmp	r3, r0
	bne	.L274
.L275:
	add	r2, r10, r6
	mov	r1, #0
	add	r2, r5, r2
	mov	r0, r1
	ldr	r3, [r7, #68]
	strb	r1, [r2, #76]
	ldr	ip, [ip, #1560]
	ldr	r1, .L306+16
	str	lr, [r2, #608]
	str	ip, [r2, #604]
	blx	r3
	b	.L268
.L301:
	ldr	r3, [r7, #68]
	mov	r0, r9
	ldr	r2, .L306+20
	ldr	r1, .L306+24
	blx	r3
	ldrsb	r3, [r5, #10]
	cmp	r3, #0
	ble	.L263
	add	r3, r5, #17408
	str	r8, [fp, #-80]
	add	r3, r3, #140
	mov	r8, r4
	mov	r4, r3
.L262:
	ldrsb	r3, [r4, #2]
	mov	r0, #0
	ldrsb	r2, [r4], #68
	add	r9, r9, #1
	ldr	r1, .L306+28
	ldr	ip, [r7, #68]
	blx	ip
	ldrsb	r3, [r5, #10]
	cmp	r3, r9
	bgt	.L262
	mov	r4, r8
	ldr	r8, [fp, #-80]
.L263:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r1, .L306+32
	blx	r3
	ldrsb	r3, [r5, #9]
	ldr	r9, .L306+4
	cmp	r3, #0
	ble	.L305
	ldrsb	ip, [r5, #10]
	add	r3, r5, #17408
	add	r3, r3, #140
	cmp	ip, #0
	ble	.L264
	mov	lr, #0
	mvn	r0, #0
	mov	r2, lr
.L266:
	ldr	r1, [r3, #56]
	add	r3, r3, #64
	cmp	r1, r0
	movcc	lr, r2
	add	r2, r2, #1
	movcc	r0, r1
	cmp	ip, r2
	bne	.L266
	mov	r3, lr, asl #6
	add	r3, r3, lr, lsl #2
	add	r3, r5, r3
	add	r3, r3, #17408
	add	r3, r3, #140
.L264:
	add	r2, r10, r6
	add	r2, r5, r2
	str	r3, [r2, #592]
	b	.L258
.L303:
	mov	r0, ip
	ldr	r3, [r7, #68]
	ldr	r1, .L306+36
	blx	r3
.L277:
	ldr	r3, [r7, #16]
	mov	r0, #3
	blx	r3
	ldr	r3, [r7, #68]
	ldr	r1, .L306+40
	mov	r0, #0
	blx	r3
	mvn	r0, #0
	b	.L290
.L297:
	ldr	ip, .L306+4
	movw	r2, #1550
	ldr	r3, .L306+44
	mov	r0, #0
	ldr	r1, .L306+48
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L290
.L298:
	ldr	ip, .L306+4
	movw	r2, #1551
	ldr	r3, .L306+52
	ldr	r1, .L306+48
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L290
.L304:
	ldr	r3, [r7, #16]
	mov	r0, #3
	blx	r3
	ldr	r3, [r7, #68]
	mov	r0, r8
	ldr	r1, .L306+56
	blx	r3
	mvn	r0, #0
	b	.L290
.L305:
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r2, .L306+20
	ldr	r1, .L306+60
	blx	r3
	ldr	r3, [r9, #16]
	mov	r0, #3
	blx	r3
	mvn	r0, #0
	b	.L290
.L307:
	.align	2
.L306:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC16
	.word	.LANCHOR1
	.word	.LC21
	.word	.LANCHOR2
	.word	.LC17
	.word	.LC19
	.word	.LC18
	.word	.LC5
	.word	.LC22
	.word	.LC0
	.word	.LC1
	.word	.LC4
	.word	.LC23
	.word	.LC20
	UNWIND(.fnend)
	.size	FSP_NewLogicFs, .-FSP_NewLogicFs
	.align	2
	.global	FSP_RemovePmv
	.type	FSP_RemovePmv, %function
FSP_RemovePmv:
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
	cmp	r0, #15
	bhi	.L315
	cmp	r1, #31
	bhi	.L316
	ldr	r3, .L318
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L317
	mov	r2, r1, asl #5
	mov	r1, r1, asl #9
	add	r3, r2, r1
	add	r3, r0, r3
	ldr	ip, [r3, #588]
	cmp	ip, #2
	ldmnefd	sp, {r4, fp, sp, pc}
	ldrb	r3, [r3, #76]	@ zero_extendqisi2
	cmp	r3, #19
	bhi	.L313
	sxtb	r3, r3
	movw	lr, #22048
	mov	r4, #0
	mov	ip, r3, asl #4
	sub	r3, ip, r3, asl #2
	add	r3, r0, r3
	str	r4, [r3, lr]
.L313:
	add	r1, r2, r1
	mov	r3, #0
	add	r0, r0, r1
	str	r3, [r0, #588]
	ldmfd	sp, {r4, fp, sp, pc}
.L315:
	ldr	ip, .L318+4
	mov	r2, #1920
	ldr	r3, .L318+8
	mov	r0, #0
.L314:
	ldr	r1, .L318+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	bx	ip
.L316:
	ldr	ip, .L318+4
	movw	r2, #1921
	ldr	r3, .L318+16
	mov	r0, #0
	b	.L314
.L317:
	ldr	ip, .L318+4
	movw	r2, #1922
	ldr	r3, .L318+20
	b	.L314
.L319:
	.align	2
.L318:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	.word	.LC24
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #4)
	sub	sp, sp, #4
	cmp	r0, #15
	mov	r6, r2
	bhi	.L352
	cmp	r1, #31
	bhi	.L353
	ldr	ip, .L363
	ldr	r7, [ip, r0, asl #2]
	cmp	r7, #0
	beq	.L354
	mov	r8, r1, asl #5
	mov	r5, r1, asl #9
	add	r4, r8, r5
	uxtb	r9, r2
	add	r4, r7, r4
	ldrsb	r3, [r4, #74]
	strb	r9, [r4, #72]
	cmp	r3, #0
	ldmneib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, [r4, #592]
	cmp	r3, #0
	beq	.L326
	ldr	ip, [r3, #56]
	ldr	r1, [r4, #584]
	cmp	ip, r1
	beq	.L355
.L326:
	add	r3, r8, r5
	add	r3, r7, r3
	ldrb	r2, [r3, #76]	@ zero_extendqisi2
	cmp	r2, #19
	bhi	.L329
	cmp	r6, #1
	beq	.L356
	cmp	r6, #0
	bne	.L332
	ldr	r0, [r3, #588]
	cmp	r0, #2
	beq	.L357
.L339:
	add	r3, r8, r5
	add	r3, r7, r3
	ldr	r3, [r3, #596]
	cmp	r3, #0
	beq	.L343
	ldrsb	r2, [r3, #2]
	cmp	r2, #1
	moveq	r2, #0
	streqb	r2, [r3, #2]
.L343:
	add	r1, r8, r5
	add	r7, r7, r1
	str	r6, [r7, #592]
	ldmib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L352:
	ldr	ip, .L363+4
	movw	r2, #1954
	ldr	r3, .L363+8
	mov	r0, #0
.L351:
	ldr	r1, .L363+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L356:
	ldr	r1, [r3, #588]
	add	r3, r3, #584
	cmp	r1, #1
	beq	.L358
.L331:
	add	r3, r8, r5
	add	r3, r7, r3
	ldr	r2, [r3, #596]
	cmp	r2, #0
	beq	.L359
.L338:
	add	r3, r8, r5
	ldr	r0, [r2, #56]
	add	r3, r7, r3
	ldr	r1, [r3, #584]
	cmp	r6, #1
	cmpeq	r0, r1
	beq	.L360
.L335:
	cmp	r6, #0
	beq	.L343
	ldmib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L353:
	ldr	ip, .L363+4
	movw	r2, #1955
	ldr	r3, .L363+16
	mov	r0, #0
	b	.L351
.L329:
	ldr	r3, .L363+4
	sxtb	r2, r2
	ldr	r1, .L363+20
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	cmp	r6, #0
	beq	.L339
	b	.L331
.L355:
	ldrsb	r1, [r3]
	cmp	r2, r1
	beq	.L327
	ldr	r1, .L363+24
	ldr	ip, [r1, #-3896]
	cmp	ip, #0
	bne	.L361
.L327:
	strb	r9, [r3]
	b	.L326
.L358:
	sxtb	r2, r2
	movw	r0, #22048
	mov	r1, r2, asl #4
	sub	r2, r1, r2, asl #2
	mov	r1, #2
	add	r2, r7, r2
	str	r6, [r2, r0]
	str	r1, [r3, #4]
.L332:
	add	r3, r8, r5
	add	r3, r7, r3
	ldr	r2, [r3, #596]
	cmp	r2, #0
	bne	.L338
	b	.L335
.L361:
	ldr	r10, [r1, #-3880]
	ldr	r1, [r3, #12]
	cmp	r10, #0
	beq	.L362
	blx	r10
	ldr	r3, [r4, #592]
	b	.L327
.L357:
	sxtb	r2, r2
	movw	ip, #22048
	mov	r0, r2, asl #4
	sub	r2, r0, r2, asl #2
	add	r2, r7, r2
	str	r6, [r2, ip]
	str	r6, [r3, #604]
	str	r6, [r3, #588]
	b	.L339
.L354:
	ldr	ip, .L363+4
	mov	r0, r7
	ldr	r3, .L363+28
	movw	r2, #1956
	b	.L351
.L360:
	ldrsb	r1, [r2, #2]
	cmp	r1, #1
	moveq	r1, #2
	streqb	r1, [r2, #2]
	streqb	r1, [r3, #73]
	b	.L335
.L359:
	ldmib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L362:
	ldr	r3, .L363+4
	mov	r0, r10
	ldr	r1, .L363+32
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #592]
	b	.L327
.L364:
	.align	2
.L363:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	.word	.LC24
	.word	.LC25
	.word	.LANCHOR1
	.word	.LC4
	.word	.LC5
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L371
	cmp	r1, #31
	bhi	.L372
	ldr	r3, .L374
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L373
	mov	r0, r1, asl #9
	add	r1, r0, r1, lsl #5
	add	r3, r3, r1
	ldrsb	r0, [r3, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L371:
	ldr	ip, .L374+4
	movw	r2, #2075
	ldr	r3, .L374+8
.L370:
	ldr	r1, .L374+12
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L372:
	ldr	ip, .L374+4
	movw	r2, #2076
	ldr	r3, .L374+16
	b	.L370
.L373:
	ldr	ip, .L374+4
	mov	r0, r3
	movw	r2, #2077
	ldr	r3, .L374+20
	ldr	r1, .L374+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L375:
	.align	2
.L374:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC26
	.word	.LC1
	.word	.LC27
	.word	.LC28
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #4)
	sub	sp, sp, #4
	cmp	r0, #15
	mov	r6, r0
	mov	r10, r2
	bhi	.L403
	cmp	r1, #31
	bhi	.L404
	ldr	r5, .L409
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L405
	ldr	r8, .L409+4
	mov	r0, #3
	mov	r7, r1, asl #5
	mov	r4, r1, asl #9
	clz	r9, r2
	ldr	r3, [r8, #12]
	blx	r3
	ldr	r5, [r5, r6, asl #2]
	add	r3, r7, r4
	mov	r9, r9, lsr #5
	add	r3, r5, r3
	add	r2, r3, #72
	ldrsb	r1, [r3, #74]
	cmp	r1, #0
	cmpeq	r10, #0
	bne	.L380
	ldr	r3, [r3, #596]
	cmp	r3, #0
	beq	.L380
	ldrsb	r2, [r2, #1]
	cmp	r2, #0
	beq	.L380
	ldr	r2, .L409+8
	ldr	r1, [r2, #-3896]
	cmp	r1, #0
	bne	.L406
.L380:
	add	r1, r7, r4
	cmp	r9, #0
	add	r1, r5, r1
	add	ip, r1, #72
	movne	r3, #0
	ldrsb	r0, [ip, #2]
	moveq	r3, #3
	strb	r3, [ip, #1]
	cmp	r0, #0
	bne	.L387
	add	lr, r1, #592
	ldr	r3, [lr, #4]
	cmp	r3, #0
	beq	.L387
	ldr	r3, [r3, #56]
	ldr	r2, [r1, #584]
	cmp	r3, r2
	bne	.L407
	cmp	r9, #0
	strneb	r0, [ip, #1]
	moveq	r3, #3
	ldrne	r3, [lr, #4]
	streqb	r3, [ip, #1]
	ldreq	r2, [lr, #4]
	strneb	r0, [r3, #2]
	strne	r0, [lr, #4]
	streqb	r3, [r2, #2]
.L387:
	ldr	r3, [r8, #16]
	mov	r0, #3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L403:
	ldr	ip, .L409+4
	movw	r2, #2094
	ldr	r3, .L409+12
.L401:
	mov	r0, #0
.L402:
	ldr	r1, .L409+16
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L404:
	ldr	ip, .L409+4
	movw	r2, #2095
	ldr	r3, .L409+20
	b	.L401
.L407:
	ldr	r4, [r8, #68]
	ldr	r1, .L409+24
	blx	r4
	b	.L387
.L405:
	ldr	ip, .L409+4
	mov	r2, #2096
	ldr	r3, .L409+28
	b	.L402
.L406:
	ldr	r2, [r2, #-3884]
	ldr	r1, [r3, #12]
	cmp	r2, #0
	beq	.L408
	mov	r0, r6
	blx	r2
	b	.L380
.L408:
	mov	r0, r2
	ldr	r3, [r8, #68]
	ldr	r1, .L409+32
	blx	r3
	b	.L380
.L410:
	.align	2
.L409:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC0
	.word	.LC1
	.word	.LC24
	.word	.LC29
	.word	.LC4
	.word	.LC6
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
	cmp	r0, #15
	mov	r5, r0
	mov	r7, r1
	bhi	.L422
	cmp	r1, #0
	beq	.L423
	ldr	r3, .L426
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r6, r0, #17408
	addne	r4, r0, #80
	addne	r6, r6, #80
	bne	.L417
	b	.L424
.L416:
	add	r4, r4, #544
	cmp	r4, r6
	beq	.L425
.L417:
	mov	r2, #0
	ldr	r1, [r4, #196]
	mov	r0, r5
	bl	FSP_SetRef
	mov	r1, r4
	mov	r0, r7
	bl	IsImageInVoQueue
	cmp	r0, #0
	beq	.L416
	ldr	r1, [r4, #196]
	mov	r2, #0
	mov	r0, r5
	add	r4, r4, #544
	bl	FSP_SetDisplay
	cmp	r4, r6
	bne	.L417
.L425:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L422:
	ldr	ip, .L426+4
	mov	r2, #552
	ldr	r3, .L426+8
	mov	r0, #0
	ldr	r1, .L426+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L424:
	ldr	ip, .L426+4
	movw	r2, #554
	ldr	r3, .L426+16
	ldr	r1, .L426+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L423:
	ldr	ip, .L426+4
	mov	r0, r1
	ldr	r3, .L426+20
	movw	r2, #553
	ldr	r1, .L426+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L427:
	.align	2
.L426:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	.word	.LC4
	.word	.LC30
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L432
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L431
	mov	r0, r1, asl #9
	add	r1, r0, r1, lsl #5
	add	r3, r3, r1
	ldrsb	r0, [r3, #73]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L431:
	ldr	ip, .L432+4
	mov	r0, r3
	movw	r2, #2163
	ldr	r3, .L432+8
	ldr	r1, .L432+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L433:
	.align	2
.L432:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L442
	ldr	ip, .L445
	ldr	ip, [ip, r0, asl #2]
	cmp	ip, #0
	beq	.L443
	cmp	r1, #0
	bne	.L438
	ldrsb	r0, [ip, #10]
	cmp	r0, r2
	ble	.L441
	mov	lr, r2, asl #6
	mov	r0, r1
	add	r2, lr, r2, lsl #2
	add	ip, ip, r2
	add	ip, ip, #17408
	str	r3, [ip, #148]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L438:
	cmp	r1, #1
	beq	.L444
.L441:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L444:
	ldrsb	r1, [ip, #11]
	cmp	r2, r1
	bge	.L441
	mov	r1, r2, asl #6
	mov	r0, #0
	add	r2, r1, r2, lsl #2
	add	ip, ip, r2
	add	ip, ip, #19712
	str	r3, [ip, #20]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L442:
	ldr	ip, .L445+4
	movw	r2, #2179
	ldr	r3, .L445+8
	mov	r0, #0
	ldr	r1, .L445+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L443:
	ldr	lr, .L445+4
	mov	r0, ip
	ldr	r3, .L445+16
	movw	r2, #2180
	ldr	r1, .L445+12
	ldr	r4, [lr, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L446:
	.align	2
.L445:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L455
	ldr	r3, .L458
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L456
	cmp	r1, #0
	bne	.L451
	ldrsb	r3, [r0, #10]
	cmp	r3, r2
	ble	.L454
	mov	r3, r2, asl #6
	add	r2, r3, r2, lsl #2
	add	r0, r0, r2
	add	r0, r0, #17408
	add	r0, r0, #144
	ldr	r0, [r0, #4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L451:
	cmp	r1, #1
	beq	.L457
.L454:
	mov	r0, #2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L455:
	ldr	ip, .L458+4
	movw	r2, #2220
	ldr	r3, .L458+8
	mov	r0, #0
	ldr	r1, .L458+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L456:
	ldr	ip, .L458+4
	movw	r2, #2221
	ldr	r3, .L458+16
	ldr	r1, .L458+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L457:
	ldrsb	r3, [r0, #11]
	cmp	r2, r3
	bge	.L454
	mov	r3, r2, asl #6
	add	r2, r3, r2, lsl #2
	add	r0, r0, r2
	add	r0, r0, #19712
	add	r0, r0, #16
	ldr	r0, [r0, #4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L459:
	.align	2
.L458:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
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
	cmp	r0, #15
	cmpls	r1, #31
	mov	r4, r0
	mov	r5, r1
	ldmhifd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r6, .L470
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r2, #0
	bl	FSP_SetRef
	ldr	r2, [r6, r4, asl #2]
	mov	r3, r5, asl #9
	add	r3, r3, r5, lsl #5
	add	r3, r2, r3
	ldrsb	r3, [r3, #73]
	cmp	r3, #3
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r5
	mov	r0, r4
	mov	r2, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	FSP_SetDisplay
.L471:
	.align	2
.L470:
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
	cmp	r0, #15
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L475
	ldr	r3, .L476
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L475
	mov	r2, r1, asl #9
	add	r0, r2, r1, lsl #5
	add	r0, r0, #72
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L475:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L477:
	.align	2
.L476:
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
	cmp	r0, #15
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L481
	ldr	r3, .L482
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L481
	mov	r2, r1, asl #9
	add	r0, r2, r1, lsl #5
	add	r0, r0, #80
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L481:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L483:
	.align	2
.L482:
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
	cmp	r0, #15
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L486
	ldr	r3, .L488
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, r1, asl #9
	addne	r1, r3, r1, lsl #5
	addne	r0, r0, r1
	ldrne	r0, [r0, #592]
	ldmfd	sp, {fp, sp, pc}
.L486:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L489:
	.align	2
.L488:
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
	cmp	r0, #15
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L492
	ldr	r3, .L494
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, r1, asl #9
	addne	r1, r3, r1, lsl #5
	addne	r0, r0, r1
	ldrne	r0, [r0, #596]
	ldmfd	sp, {fp, sp, pc}
.L492:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L495:
	.align	2
.L494:
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
	cmp	r0, #15
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L498
	ldr	r3, .L500
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, r1, asl #9
	addne	r1, r3, r1, lsl #5
	addne	r0, r0, r1
	ldrne	r0, [r0, #604]
	ldmfd	sp, {fp, sp, pc}
.L498:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L501:
	.align	2
.L500:
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
	cmp	r0, #15
	bhi	.L513
	cmp	r2, #0
	beq	.L514
	cmp	r1, #0
	beq	.L515
	ldr	ip, .L517
	ldr	lr, [ip, r0, asl #2]
	cmp	lr, #0
	beq	.L516
	mov	lr, #0
	str	lr, [r1]
	ldr	r4, [ip, r0, asl #2]
	ldrsb	r4, [r4, #10]
	cmp	r4, lr
	str	r4, [r1]
	ldr	ip, [ip, r0, asl #2]
	add	ip, ip, #17408
	add	ip, ip, #140
	ldmlefd	sp, {r4, fp, sp, pc}
	sub	r2, r2, #4
	sub	r3, r3, #4
.L509:
	ldr	r0, [ip, #12]
	add	lr, lr, #1
	add	ip, ip, #68
	str	r0, [r2, #4]!
	ldr	r0, [ip, #-52]
	str	r0, [r3, #4]!
	ldr	r4, [r1]
	cmp	r4, lr
	bgt	.L509
	ldmfd	sp, {r4, fp, sp, pc}
.L513:
	ldr	ip, .L517+4
	movw	r2, #2379
	ldr	r3, .L517+8
	mov	r0, #0
.L512:
	ldr	r1, .L517+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	bx	ip
.L514:
	mov	r0, r2
	ldr	ip, .L517+4
	ldr	r3, .L517+16
	movw	r2, #2380
	b	.L512
.L515:
	ldr	ip, .L517+4
	mov	r0, r1
	ldr	r3, .L517+20
	movw	r2, #2381
	b	.L512
.L516:
	ldr	ip, .L517+4
	mov	r0, lr
	ldr	r3, .L517+24
	movw	r2, #2382
	b	.L512
.L518:
	.align	2
.L517:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	.word	.LC31
	.word	.LC32
	.word	.LC4
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
	cmp	r0, #15
	bhi	.L530
	cmp	r2, #0
	beq	.L531
	cmp	r1, #0
	beq	.L532
	ldr	ip, .L534
	ldr	r3, [ip, r0, asl #2]
	cmp	r3, #0
	beq	.L533
	mov	r3, #0
	str	r3, [r1]
	ldr	ip, [ip, r0, asl #2]
	ldrsb	r0, [ip, #13]
	str	r0, [r1]
	ldrsb	r1, [ip, #13]
	cmp	r1, r3
	ldmlefd	sp, {fp, sp, pc}
	add	r1, ip, #22016
	sub	r2, r2, #4
	add	r1, r1, #24
.L526:
	ldr	r0, [r1], #12
	add	r3, r3, #1
	str	r0, [r2, #4]!
	ldrsb	r0, [ip, #13]
	cmp	r0, r3
	bgt	.L526
	ldmfd	sp, {fp, sp, pc}
.L530:
	ldr	ip, .L534+4
	movw	r2, #2424
	ldr	r3, .L534+8
	mov	r0, #0
.L529:
	ldr	r1, .L534+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L531:
	mov	r0, r2
	ldr	ip, .L534+4
	ldr	r3, .L534+16
	movw	r2, #2425
	b	.L529
.L532:
	ldr	ip, .L534+4
	mov	r0, r1
	ldr	r3, .L534+20
	movw	r2, #2426
	b	.L529
.L533:
	mov	r0, r3
	ldr	ip, .L534+4
	ldr	r3, .L534+24
	movw	r2, #2427
	b	.L529
.L535:
	.align	2
.L534:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	.word	.LC33
	.word	.LC34
	.word	.LC4
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
	ldr	r3, .L539
	mov	ip, r1
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L538
	ldrb	lr, [r3, #10]	@ zero_extendqisi2
	add	r4, r3, #16384
	mov	r0, r1
	ldr	r5, .L539+4
	add	r1, r3, #17408
	mov	r2, #2176
	strb	lr, [ip, #1]
	add	r1, r1, #140
	ldr	lr, [r4, #1244]
	ldr	r4, [r4, #1176]
	rsb	lr, r4, lr
	str	lr, [ip, #2184]
	ldrb	lr, [r3, #11]	@ zero_extendqisi2
	strb	lr, [ip, #2]
	ldrb	lr, [r3, #12]	@ zero_extendqisi2
	strb	lr, [ip, #3]
	ldrb	lr, [r3]	@ zero_extendqisi2
	strb	lr, [ip, #4]
	ldrb	r3, [r3, #13]	@ zero_extendqisi2
	strb	r3, [r0], #8
	ldr	r3, [r5, #52]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L538:
	ldr	ip, .L539+4
	mov	r0, r3
	movw	r2, #2449
	ldr	r3, .L539+8
	ldr	r1, .L539+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	ip
.L540:
	.align	2
.L539:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LC1
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L552
	ldr	r3, .L554
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, r0
	movne	r0, #0
	beq	.L553
.L546:
	ldr	r2, [r3, #592]
	add	r3, r3, #544
	cmp	r2, #0
	beq	.L545
	ldr	r2, [r2, #12]
	cmp	r2, r1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
.L545:
	add	r0, r0, #1
	cmp	r0, #32
	bne	.L546
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L552:
	ldr	ip, .L554+4
	movw	r2, #2478
	ldr	r3, .L554+8
	mov	r0, #0
	ldr	r1, .L554+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L553:
	ldr	ip, .L554+4
	movw	r2, #2479
	ldr	r3, .L554+16
	ldr	r1, .L554+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L555:
	.align	2
.L554:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetLogicIdByPhyAddr, .-FSP_GetLogicIdByPhyAddr
	.align	2
	.global	FSP_PrintContext
	.type	FSP_PrintContext, %function
FSP_PrintContext:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #4)
	sub	sp, sp, #4
	cmp	r0, #15
	bhi	.L588
	ldr	r3, .L591
	ldr	r9, [r3, r0, asl #2]
	cmp	r9, #0
	beq	.L589
	ldr	r7, .L591+4
	mov	r0, #0
	ldr	r1, .L591+8
	mov	r5, r9
	mov	r6, #1
	ldr	r3, [r7, #68]
	blx	r3
	ldr	r4, [r7, #68]
	ldr	r3, [r9, #4]
	mov	r0, #0
	ldr	r2, .L591+12
	ldr	r1, .L591+16
	blx	r4
	ldr	r4, [r7, #68]
	ldr	r3, [r9, #44]
	mov	r0, #0
	ldr	r2, .L591+20
	ldr	r1, .L591+16
	blx	r4
	ldr	r4, [r7, #68]
	ldr	r3, [r9, #48]
	mov	r0, #0
	ldr	r2, .L591+24
	ldr	r1, .L591+16
	blx	r4
	ldr	r4, [r7, #68]
	ldr	r3, [r9, #60]
	mov	r0, #0
	ldr	r2, .L591+28
	ldr	r1, .L591+16
	blx	r4
	ldr	r4, [r7, #68]
	ldr	r3, [r9, #64]
	mov	r0, #0
	ldr	r2, .L591+32
	ldr	r1, .L591+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #40]
	mov	r0, #0
	ldr	r2, .L591+36
	ldr	r1, .L591+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #42]
	mov	r0, #0
	ldr	r2, .L591+40
	ldr	r1, .L591+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #43]
	mov	r0, #0
	ldr	r2, .L591+44
	ldr	r1, .L591+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #10]
	mov	r0, #0
	ldr	r2, .L591+48
	ldr	r1, .L591+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #11]
	mov	r0, #0
	ldr	r2, .L591+52
	ldr	r1, .L591+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #13]
	mov	r0, #0
	ldr	r2, .L591+56
	ldr	r1, .L591+16
	blx	r4
	ldr	r3, [r7, #68]
	mov	r2, #32
	ldr	r1, .L591+60
	mov	r0, #0
	mov	r4, #0
	blx	r3
	b	.L559
.L561:
	ldr	r8, [r7, #68]
	mov	r0, #0
	ldrsb	r3, [r5, #73]
	ldrsb	r2, [r5, #72]
	ldr	r1, .L591+64
	blx	r8
	cmp	r6, #31
	bgt	.L590
.L562:
	add	r4, r4, #1
	add	r6, r6, #1
	add	r5, r5, #544
.L559:
	cmp	r4, #0
	ldr	r10, .L591+4
	beq	.L560
	ands	r0, r4, #7
	bne	.L561
	ldr	r3, [r7, #68]
	ldr	r1, .L591+68
	blx	r3
	b	.L561
.L590:
	ldr	r3, [r10, #68]
	mov	r0, #0
	ldrsb	r2, [r9, #10]
	ldr	r1, .L591+72
	blx	r3
	ldrsb	r3, [r9, #10]
	cmp	r3, #0
	addgt	r5, r9, #17408
	addgt	r5, r5, #140
	movgt	r4, #0
	ble	.L569
.L566:
	ldrsb	r3, [r5, #2]
	mov	r0, #0
	ldrsb	r2, [r5]
	add	r4, r4, #1
	ldr	r6, [r7, #68]
	add	r5, r5, #68
	ldr	r1, .L591+64
	blx	r6
	ldrsb	r3, [r9, #10]
	cmp	r3, r4
	ble	.L569
	cmp	r4, #0
	beq	.L566
	ands	r0, r4, #7
	bne	.L566
	ldr	r3, [r10, #68]
	ldr	r1, .L591+68
	blx	r3
	b	.L566
.L569:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldrsb	r2, [r9, #11]
	ldr	r1, .L591+76
	blx	r3
	ldrsb	r3, [r9, #11]
	cmp	r3, #0
	ble	.L565
	add	r5, r9, #19712
	ldr	r8, .L591+4
	add	r5, r5, #12
	mov	r4, #0
.L572:
	ldrsb	r3, [r5, #2]
	mov	r0, #0
	ldrsb	r2, [r5]
	add	r4, r4, #1
	ldr	r6, [r7, #68]
	add	r5, r5, #68
	ldr	r1, .L591+64
	blx	r6
	ldrsb	r3, [r9, #11]
	cmp	r3, r4
	ble	.L565
	cmp	r4, #0
	beq	.L572
	ands	r0, r4, #7
	bne	.L572
	ldr	r3, [r8, #68]
	ldr	r1, .L591+68
	blx	r3
	b	.L572
.L565:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldrsb	r2, [r9, #13]
	ldr	r1, .L591+80
	blx	r3
	ldrsb	r3, [r9, #13]
	cmp	r3, #0
	ble	.L571
	add	r5, r9, #22016
	ldr	r6, .L591+4
	add	r5, r5, #32
	mov	r4, #0
.L575:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r2, [r5]
	add	r4, r4, #1
	ldr	r1, .L591+84
	add	r5, r5, #12
	blx	r3
	ldrsb	r3, [r9, #13]
	cmp	r3, r4
	ble	.L571
	cmp	r4, #0
	beq	.L575
	ands	r0, r4, #15
	bne	.L575
	ldr	r3, [r6, #68]
	ldr	r1, .L591+68
	blx	r3
	b	.L575
.L571:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r1, .L591+88
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L588:
	ldr	ip, .L591+4
	movw	r2, #2510
	ldr	r3, .L591+92
	mov	r0, #0
.L587:
	ldr	r1, .L591+96
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L589:
	ldr	ip, .L591+4
	mov	r0, r9
	ldr	r3, .L591+100
	movw	r2, #2511
	b	.L587
.L560:
	ldr	r8, [r7, #68]
	mov	r0, r4
	ldrsb	r3, [r5, #73]
	ldrsb	r2, [r5, #72]
	ldr	r1, .L591+64
	blx	r8
	b	.L562
.L592:
	.align	2
.L591:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC35
	.word	.LC36
	.word	.LC37
	.word	.LC38
	.word	.LC39
	.word	.LC40
	.word	.LC41
	.word	.LC42
	.word	.LC43
	.word	.LC44
	.word	.LC45
	.word	.LC46
	.word	.LC47
	.word	.LC48
	.word	.LC19
	.word	.LC18
	.word	.LC49
	.word	.LC50
	.word	.LC51
	.word	.LC53
	.word	.LC52
	.word	.LC0
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_PrintContext, .-FSP_PrintContext
	.align	2
	.global	FSP_IsFsLeak
	.type	FSP_IsFsLeak, %function
FSP_IsFsLeak:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r3, .L604
	mov	r5, r0
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L602
	ldrsb	r4, [r3, #10]
	cmp	r4, #0
	ble	.L596
	add	r3, r3, #17408
	mov	r2, #0
	add	r3, r3, #140
.L599:
	ldrsb	r1, [r3]
	cmp	r1, #0
	bne	.L597
	ldrsb	r1, [r3, #2]
	cmp	r1, #0
	beq	.L598
.L597:
	add	r2, r2, #1
	add	r3, r3, #68
	cmp	r4, r2
	bne	.L599
.L596:
	sub	r3, fp, #36
	sub	r2, fp, #32
	sub	r1, fp, #40
	mov	r0, r5
	mov	r6, #0
	str	r6, [fp, #-36]
	str	r6, [fp, #-32]
	str	r6, [fp, #-40]
	bl	VCTRL_GetChanImgNum
	ldr	r2, [fp, #-40]
	ldr	r3, [fp, #-32]
	ldr	r0, [fp, #-36]
	add	r1, r2, r3
	add	r1, r1, r0
	add	r1, r1, #2
	cmp	r4, r1
	bgt	.L603
.L600:
	mov	r0, #0
.L595:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L598:
	cmp	r4, r2
	bgt	.L600
	b	.L596
.L603:
	ldr	r1, .L604+4
	stmia	sp, {r0, r4}
	mov	r0, r6
	ldr	r4, [r1, #68]
	ldr	r1, .L604+8
	blx	r4
	mov	r0, r5
	bl	FSP_PrintContext
	mov	r0, #1
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L602:
	ldr	r3, .L604+4
	mov	r0, #1
	ldr	r1, .L604+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L595
.L605:
	.align	2
.L604:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC55
	.word	.LC54
	UNWIND(.fnend)
	.size	FSP_IsFsLeak, .-FSP_IsFsLeak
	.align	2
	.global	FSP_IsNewFsAvalible
	.type	FSP_IsNewFsAvalible, %function
FSP_IsNewFsAvalible:
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
	cmp	r0, #15
	mov	r6, r0
	bhi	.L625
	ldr	r3, .L630
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L626
	ldr	r3, .L630+4
	ldr	r2, [r3, #-3896]
	cmp	r2, #0
	beq	.L613
	ldr	r5, [r3, #-3892]
	cmp	r5, #0
	beq	.L627
	blx	r5
	cmp	r0, #0
	bne	.L628
.L613:
	ldrb	r1, [r4, #10]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L629
	sxtb	r1, r1
	cmp	r1, #0
	ble	.L614
	add	r3, r4, #17408
	mov	r2, #0
	add	r3, r3, #204
	b	.L617
.L615:
	add	r2, r2, #1
	add	r3, r3, #68
	cmp	r2, r1
	beq	.L614
.L617:
	ldr	r0, [r3]
	cmp	r0, #1
	bne	.L615
	ldrsb	ip, [r3, #-64]
	cmp	ip, #0
	bne	.L615
	ldrsb	ip, [r3, #-62]
	cmp	ip, #0
	bne	.L615
	cmp	r1, r2
	ldmgtfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L614:
	mov	r0, r6
	bl	FSP_IsFsLeak
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L629:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L628:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L627:
	ldr	r3, .L630+8
	mov	r0, r5
	ldr	r1, .L630+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L625:
	ldr	ip, .L630+8
	movw	r2, #1252
	ldr	r3, .L630+16
	mov	r0, #0
	ldr	r1, .L630+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L626:
	ldr	ip, .L630+8
	mov	r0, r4
	ldr	r3, .L630+24
	movw	r2, #1253
	ldr	r1, .L630+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L631:
	.align	2
.L630:
	.word	.LANCHOR0
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	.word	.LC0
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_IsNewFsAvalible, .-FSP_IsNewFsAvalible
	.align	2
	.global	FSP_IsFsInVO
	.type	FSP_IsFsInVO, %function
FSP_IsFsInVO:
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
	ldr	ip, .L646
	ldr	r2, [ip, r0, asl #2]
	cmp	r2, #0
	beq	.L641
	mov	r3, r0, asl #8
	add	r3, r3, r0, lsl #3
	add	r3, ip, r3
	add	r3, r3, #64
	ldrsh	lr, [r3, #2]
	cmn	lr, #1
	beq	.L641
	ldrh	r3, [r3, #4]
	cmp	r3, lr
	beq	.L641
	ldr	r2, [r2, #4]
	cmp	r2, #1
	beq	.L645
.L641:
	mov	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L645:
	and	r3, r3, #63
	cmp	lr, r3
	beq	.L641
	mov	r4, r0, asl #6
	add	r0, r4, r0, lsl #1
	add	r4, r0, r3
	add	r4, ip, r4, lsl #2
	ldr	r4, [r4, #72]
	cmp	r4, r1
	bne	.L635
	b	.L643
.L636:
	ldr	r2, [r2, #72]
	cmp	r2, r1
	beq	.L643
.L635:
	add	r3, r3, #1
	and	r3, r3, #63
	add	r2, r0, r3
	cmp	lr, r3
	add	r2, ip, r2, lsl #2
	bne	.L636
	b	.L641
.L643:
	mov	r0, #1
	ldmfd	sp, {r4, fp, sp, pc}
.L647:
	.align	2
.L646:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_IsFsInVO, .-FSP_IsFsInVO
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
	ldr	r3, .L656
	ldr	ip, [r3, r0, asl #2]
	add	r3, ip, #16896
	ldrsb	r3, [r3, #41]
	cmp	r3, #0
	beq	.L653
	add	r3, ip, #16384
	mov	r2, #30
	add	r3, r3, #9
	b	.L652
.L650:
	subs	r2, r2, #1
	bcc	.L655
.L652:
	ldrsb	r1, [r3]
	sub	r3, r3, #544
	cmp	r1, #0
	bne	.L650
.L651:
	mov	r3, r2, asl #9
	mov	r0, r2
	add	r2, r3, r2, lsl #5
	mov	r3, #0
	add	ip, ip, r2
	str	r3, [ip, #592]
	str	r3, [ip, #596]
	ldmfd	sp, {fp, sp, pc}
.L655:
	mov	r2, #0
	b	.L651
.L653:
	mov	r2, #31
	b	.L651
.L657:
	.align	2
.L656:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetNullLogicFs, .-FSP_GetNullLogicFs
	.align	2
	.global	FSP_SwitchNotify
	.type	FSP_SwitchNotify, %function
FSP_SwitchNotify:
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
	cmp	r0, #15
	ldmlsfd	sp, {fp, sp, pc}
	ldr	ip, .L660
	movw	r2, #2685
	ldr	r3, .L660+4
	mov	r0, #0
	ldr	r1, .L660+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L661:
	.align	2
.L660:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_SwitchNotify, .-FSP_SwitchNotify
	.align	2
	.global	FSP_GetFspType
	.type	FSP_GetFspType, %function
FSP_GetFspType:
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
	cmp	r0, #15
	bhi	.L666
	ldr	r3, .L668
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L667
	ldr	r0, [r0, #4]
	subs	r0, r0, #1
	mvnne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L666:
	ldr	ip, .L668+4
	movw	r2, #2716
	ldr	r3, .L668+8
	mov	r0, #0
	ldr	r1, .L668+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L667:
	ldr	ip, .L668+4
	movw	r2, #2717
	ldr	r3, .L668+16
	ldr	r1, .L668+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L669:
	.align	2
.L668:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L674
	ldr	r3, .L676
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L675
	ldrsb	r0, [r0, #9]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L674:
	ldr	ip, .L676+4
	movw	r2, #2734
	ldr	r3, .L676+8
	mov	r0, #0
	ldr	r1, .L676+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L675:
	ldr	ip, .L676+4
	movw	r2, #2735
	ldr	r3, .L676+16
	ldr	r1, .L676+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L677:
	.align	2
.L676:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetTotalValidFsNum, .-FSP_GetTotalValidFsNum
	.global	s_FspVoQue
	.global	s_pFspInst
	.section	.rodata
	.align	2
.LANCHOR2 = . + 0
	.type	__func__.13359, %object
	.size	__func__.13359, 15
__func__.13359:
	.ascii	"FSP_NewLogicFs\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"InstID out of range\000" )
.LC1:
	ASCII(.ascii	"fsp.c,L%d: %s\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"fsp instance not in used\000" )
	.space	3
.LC3:
	ASCII(.ascii	"pFspInst = NULL\000" )
.LC4:
	ASCII(.ascii	"fsp is not inited\000" )
	.space	2
.LC5:
	ASCII(.ascii	"%s : AllocFrame func null\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"%s : RleaseFrame func null\012\000" )
.LC7:
	ASCII(.ascii	"pstFspInstCfg = NULL\000" )
	.space	3
.LC8:
	ASCII(.ascii	"This inst is not active\000" )
.LC9:
	ASCII(.ascii	"eChanCapLevel = %d is not expected!\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"decode channel CapLevel is %d(w=%d,h=%d), this stre" )
	ASCII(.ascii	"am (w=%d,h=%d) can NOT be decoded!\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"user set decode channel max resolution is (w=%d,h=%" )
	ASCII(.ascii	"d), this stream (w=%d,h=%d) can NOT be decoded!\012" )
	ASCII(.ascii	"\000" )
.LC12:
	ASCII(.ascii	"DFS, Wrong Partition State. State: 0x%x\012\000" )
	.space	3
.LC13:
	ASCII(.ascii	"DFS, Mem Element Fill Successed! Ready to Decode!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC14:
	ASCII(.ascii	"Fsp arrange failed, return %d\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"arrange ret %d, min = %d, actual = %d\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"no logic frame store!!!\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"%s no decode phy fs\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"%d%d \000" )
	.space	2
.LC20:
	ASCII(.ascii	"%s Not partition yet!\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"no pmv memory\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"FSP_AllocFrame failed\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"invalid stFrameInfo PhyAddr\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"LogicFrameID out of range\000" )
	.space	2
.LC25:
	ASCII(.ascii	"fsp.c, line %d: pstLogicFs->PmvIdc out of range(=%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"FSP_GetRef: InstID out of range\000" )
.LC27:
	ASCII(.ascii	"FSP_GetRef: LogicFrameID out of range\000" )
	.space	2
.LC28:
	ASCII(.ascii	"FSP_GetRef: Fsp is not inited\000" )
	.space	2
.LC29:
	ASCII(.ascii	"FSP_SetDisplay: LogicTick=%d, DispTick=%d!\012\000" )
.LC30:
	ASCII(.ascii	"pstVoQue is NULL\000" )
	.space	3
.LC31:
	ASCII(.ascii	"DecFsAddrTab is NULL\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"DecFsNum is NULL\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"PmvAddrTab is NULL\012\000" )
.LC34:
	ASCII(.ascii	"PmvNum is NULL\012\000" )
.LC35:
	ASCII(.ascii	"FSP CONTEXT:\012\000" )
	.space	2
.LC36:
	ASCII(.ascii	"FspInstState\000" )
	.space	3
.LC37:
	ASCII(.ascii	"%-35s :%d\012\000" )
	.space	1
.LC38:
	ASCII(.ascii	"DecFsWidth\000" )
	.space	1
.LC39:
	ASCII(.ascii	"DecFsHeight\000" )
.LC40:
	ASCII(.ascii	"DispFsWidth\000" )
.LC41:
	ASCII(.ascii	"DispFsHeight\000" )
	.space	3
.LC42:
	ASCII(.ascii	"ExpectedDecFsNum\000" )
	.space	3
.LC43:
	ASCII(.ascii	"ExpectedDispFsNum\000" )
	.space	2
.LC44:
	ASCII(.ascii	"ExpectedPmvNum\000" )
	.space	1
.LC45:
	ASCII(.ascii	"DecFsNum\000" )
	.space	3
.LC46:
	ASCII(.ascii	"DispFsNum\000" )
	.space	2
.LC47:
	ASCII(.ascii	"PmvNum\000" )
	.space	1
.LC48:
	ASCII(.ascii	"logic fs: %d\012\000" )
	.space	2
.LC49:
	ASCII(.ascii	"\012dec fs: %d\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"\012disp fs: %d\012\000" )
	.space	2
.LC51:
	ASCII(.ascii	"\012pmv: %d\012\000" )
	.space	2
.LC52:
	ASCII(.ascii	"\012\012\000" )
	.space	1
.LC53:
	ASCII(.ascii	"%d \000" )
.LC54:
	ASCII(.ascii	"FSP_IsFsLeak: fsp is not inited \012\000" )
	.space	2
.LC55:
	ASCII(.ascii	"No free fs: ref=%d,read=%d,new=%d,total=%d\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
.LANCHOR1 = . + 8184
	.type	s_pFspInst, %object
	.size	s_pFspInst, 64
s_pFspInst:
	.space	64
	.type	s_FspVoQue, %object
	.size	s_FspVoQue, 4224
s_FspVoQue:
	.space	4224
	.type	g_IsFrameIntfValid, %object
	.size	g_IsFrameIntfValid, 4
g_IsFrameIntfValid:
	.space	4
	.type	g_FspFrameIntf, %object
	.size	g_FspFrameIntf, 16
g_FspFrameIntf:
	.space	16
	.ident	"GCC: (gcc-4.9.4 + glibc-2.27 Build by czyong Mon Jul  2 18:10:52 CST 2018) 4.9.4"
	.section	.note.GNU-stack,"",%progbits
