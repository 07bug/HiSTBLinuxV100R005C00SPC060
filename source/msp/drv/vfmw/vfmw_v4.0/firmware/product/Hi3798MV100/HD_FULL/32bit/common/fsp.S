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
	add	r6, r4, #40
	ldrb	r8, [r4, #10]	@ zero_extendqisi2
	ldrb	r10, [r4, #1]	@ zero_extendqisi2
	mov	r2, #16
	ldr	r9, [r4, #4]
	mov	r1, r6
	ldr	r3, [r5, #52]
	sub	r0, fp, #604
	blx	r3
	ldr	r3, [r5, #48]
	movw	r2, #21880
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
	add	r0, r0, #88
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
	add	r1, r1, #88
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
	movw	r2, #21880
	mov	r1, r5
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
	add	r3, r4, #20480
	mov	r2, #1
	mov	r0, r5
	str	r2, [r4, #4]
	str	r5, [r3, #1388]
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
	add	r5, r8, #19456
	ldr	r10, .L94+8
	add	r4, r4, #154
	add	r5, r5, #154
	mov	r9, r6
	b	.L78
.L75:
	ldrsb	r3, [r4]
	cmp	r3, #0
	bne	.L91
.L73:
	add	r4, r4, #64
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
	add	r4, r4, #64
	ldr	r1, [r4, #-54]
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
	add	r0, r7, #88
	ldr	r3, [r10, #48]
	blx	r3
	ldrsb	r3, [r7, #10]
	cmp	r3, #0
	ble	.L110
	add	r4, r7, #17408
	ldr	r8, .L132+8
	mov	r5, #0
	add	r4, r4, #208
	mov	r6, r5
.L109:
	ldr	r1, [r4, #-44]
	cmp	r1, #0
	beq	.L104
	ldr	r3, [r8, #-3896]
	cmp	r3, #0
	beq	.L104
	ldrsb	r3, [r4, #-56]
	cmp	r3, #0
	bne	.L129
.L106:
	ldrsb	r3, [r4, #-54]
	cmp	r3, #0
	bne	.L130
.L104:
	strb	r6, [r4, #-56]
	add	r5, r5, #1
	strb	r6, [r4, #-54]
	str	r6, [r4], #64
	ldrsb	r3, [r7, #10]
	cmp	r3, r5
	bgt	.L109
.L110:
	ldrsb	r0, [r7, #11]
	cmp	r0, #0
	addgt	r3, r7, #19456
	movgt	r2, #0
	addgt	r3, r3, #152
	movgt	r1, r2
	ble	.L102
.L113:
	add	r2, r2, #1
	strb	r1, [r3]
	cmp	r0, r2
	strb	r1, [r3, #2]
	str	r1, [r3, #56]
	add	r3, r3, #64
	bne	.L113
.L102:
	ldrsb	r2, [r7, #13]
	cmp	r2, #0
	addgt	r2, r2, #13
	addgt	r3, r7, #13
	addgt	r2, r7, r2
	movgt	r1, #0
	ble	.L112
.L114:
	strb	r1, [r3, #1]!
	cmp	r3, r2
	bne	.L114
.L112:
	mov	r0, #0
	str	r0, [r7, #36]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L130:
	ldr	r3, [r8, #-3884]
	ldr	r1, [r4, #-44]
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
	add	r0, r4, #56
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
	.global	FSP_PartitionFsMemory
	.type	FSP_PartitionFsMemory, %function
FSP_PartitionFsMemory:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 600
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #628)
	sub	sp, sp, #628
	ldr	r7, .L226
	mov	r5, r0
	str	r1, [fp, #-616]
	mov	r10, r2
	sub	r0, fp, #608
	ldr	r4, [r7, #48]
	mov	r2, #564
	mov	r1, #0
	str	r3, [fp, #-632]
	blx	r4
	cmp	r5, #15
	bhi	.L215
	ldr	r3, .L226+4
	ldr	r4, [r3, r5, asl #2]
	cmp	r4, #0
	beq	.L216
	ldr	r6, .L226+8
	ldr	r0, [r6, r5, asl #2]
	add	r3, r0, #229376
	ldr	r8, [r3, #72]
	cmp	r8, #0
	beq	.L217
	ldr	r1, [r4, #64]
	ldr	ip, [r4, #68]
	mul	lr, ip, r1
.L155:
	ldr	r2, [r0, #144]
	ldr	r3, [r0, #148]
	mul	r8, r3, r2
	cmp	r8, lr
	blt	.L218
	ldr	r3, [r0, #1404]
	add	r0, r0, #225280
	ldrsb	r8, [r4, #60]
	cmp	r3, #1
	beq	.L219
.L158:
	ldr	r3, [r0, #2876]
	ldr	r2, .L226+12
	cmp	r8, r3
	ldr	r9, [r2, #48]
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r0, #2896]
	ldrsb	r3, [r4, #60]
	cmp	r9, #0
	str	r3, [r0, #2876]
	beq	.L192
	ldr	r3, [r4, #68]
	sub	ip, fp, #608
	ldr	r2, [r4, #64]
	mov	lr, #40
	str	ip, [sp, #16]
	mov	r1, r10
	str	r5, [sp, #12]
	ldrsb	ip, [r4, #59]
	str	lr, [sp, #4]
	ldr	r0, [fp, #-616]
	str	ip, [sp, #8]
	ldrsb	ip, [r4, #63]
	str	ip, [sp]
	blx	r9
	cmp	r0, #2
	mov	r9, r0
	beq	.L220
	cmp	r0, #0
	bne	.L162
	ldr	r3, [fp, #-316]
	ldr	r10, .L226+8
	strb	r3, [r4, #9]
	ldr	r3, [r6, r5, asl #2]
	ldr	r2, [r3, #1404]
	str	r0, [r3, #1444]
	cmp	r2, #1
	beq	.L221
.L166:
	ldr	r3, [r7, #68]
	mov	r0, #31
	ldr	r1, .L226+16
	blx	r3
	ldr	r3, [fp, #-316]
	ldr	r1, .L226
	cmp	r8, r3
	bgt	.L222
	ldrsb	r2, [r4, #1]
	mov	r3, #0
	strb	r3, [r4, #11]
	cmp	r2, r3
	strb	r3, [r4, #12]
	bne	.L223
.L172:
	ldr	r0, [fp, #-316]
	cmp	r0, #40
	movge	r0, #40
	uxtb	r0, r0
	strb	r0, [r4, #10]
.L173:
	ldr	r5, [fp, #-328]
	sub	ip, fp, #44
	add	r3, r4, #17408
	ldr	lr, [fp, #-608]
	ldr	r1, [ip, #-556]!
	mov	r2, #0
	str	r5, [fp, #-616]
	sxtb	r0, r0
	ldr	r5, [fp, #-324]
	add	r3, r3, #168
	ldr	r7, [r4, #64]
	ldr	r6, [r4, #68]
	str	r5, [fp, #-620]
	ldr	r10, [fp, #-344]
	ldr	r9, [fp, #-336]
	ldr	r8, [fp, #-332]
	ldr	r5, [fp, #-320]
	str	r1, [fp, #-624]
	mov	r1, r2
	str	r4, [fp, #-628]
.L176:
	cmp	r0, r2
	strgt	r2, [r3, #-12]
	add	r2, r2, #1
	strle	r1, [r3, #-12]
	ldrgt	r4, [ip]
	add	r3, r3, #64
	ldrle	r4, [fp, #-624]
	add	ip, ip, #4
	strgt	r4, [r3, #-68]
	ldrgt	r4, [ip, #124]
	str	lr, [r3, #-60]
	str	r10, [r3, #-56]
	str	r9, [r3, #-52]
	str	r8, [r3, #-48]
	str	r7, [r3, #-44]
	str	r6, [r3, #-40]
	strgt	r4, [r3, #-64]
	strle	r4, [r3, #-68]
	cmp	r2, #32
	ldr	r4, [fp, #-616]
	str	r4, [r3, #-36]
	ldr	r4, [fp, #-620]
	str	r5, [r3, #-28]
	strb	r1, [r3, #-80]
	str	r4, [r3, #-32]
	strb	r1, [r3, #-79]
	strb	r1, [r3, #-78]
	bne	.L176
	ldr	r4, [fp, #-628]
	mov	ip, #1
	mov	r5, #0
	add	r3, r4, #20480
	str	r3, [fp, #-640]
	strb	ip, [r4, #12]
	mov	r2, r5
	mov	r8, r3
	sub	r3, fp, #44
	add	r3, r3, r0, lsl #2
	ldr	r10, [fp, #-344]
	str	r5, [r8, #1180]
	ldr	r1, [r3, #-556]
	add	r3, r4, #16384
	str	lr, [r8, #1196]
	mov	r9, r3
	str	r3, [fp, #-636]
	str	r1, [r8, #1188]
	mov	r3, r5
	str	r10, [r9, #1200]
	mov	r1, r5
	ldr	r10, [fp, #-336]
	str	r10, [r9, #1204]
	ldr	r10, [fp, #-332]
	str	r10, [r9, #1208]
	str	r6, [r8, #1216]
	ldr	r6, [fp, #-328]
	str	r7, [r8, #1212]
	strb	r5, [r8, #1176]
	str	r6, [r8, #1220]
	ldr	r6, [fp, #-324]
	strb	r5, [r8, #1177]
	strb	r5, [r8, #1178]
	str	r6, [r8, #1224]
	ldr	r6, [fp, #-320]
	str	r6, [r8, #1228]
	strb	r5, [r4, #11]
	ldr	r5, [fp, #-328]
	ldr	r8, [fp, #-344]
	ldr	r7, [fp, #-336]
	str	r5, [fp, #-616]
	ldr	r5, [fp, #-324]
	ldr	r6, [fp, #-332]
	str	r5, [fp, #-620]
	ldr	r5, [fp, #-320]
	ldr	r9, [fp, #-608]
	str	r5, [fp, #-624]
	str	r9, [fp, #-628]
	b	.L180
.L224:
	add	r0, r2, r0
	add	r3, r4, r2, lsl #6
	sxtab	ip, r0, ip
	add	r9, r3, #19456
	sub	r10, fp, #44
	add	ip, r10, ip, lsl #2
	mov	r0, r9
	str	r2, [r9, #156]
.L212:
	ldr	ip, [ip, #-556]
	mov	r10, r0
	add	r2, r2, #1
	cmp	r2, #32
	str	ip, [r0, #164]
	add	ip, r3, #17408
	str	lr, [r10, #172]
	mov	r9, ip
	str	r8, [ip, #176]
	str	r7, [r9, #180]
	add	ip, r3, #19456
	str	r6, [r9, #184]
	ldr	lr, [r4, #80]
	mov	r0, ip
	mov	r10, ip
	str	lr, [ip, #188]
	ldr	r5, [r4, #84]
	str	r5, [r0, #192]
	ldr	r5, [fp, #-616]
	str	r5, [r10, #196]
	ldr	r5, [fp, #-620]
	str	r5, [r10, #200]
	ldr	r5, [fp, #-624]
	str	r5, [r10, #204]
	strb	r1, [ip, #152]
	strb	r1, [ip, #153]
	strb	r1, [ip, #154]
	beq	.L179
	ldrb	r3, [r4, #11]	@ zero_extendqisi2
	ldr	lr, [fp, #-628]
	ldrb	ip, [r4, #12]	@ zero_extendqisi2
	ldrsb	r0, [r4, #10]
.L180:
	sxtb	r3, r3
	cmp	r3, r2
	bgt	.L224
	add	r3, r4, r2, lsl #6
	sxtab	ip, r0, ip
	add	r9, r3, #19456
	sub	r5, fp, #44
	add	ip, r5, ip, lsl #2
	mov	r0, r9
	str	r1, [r9, #156]
	b	.L212
.L179:
	ldr	r3, [fp, #-56]
	add	r1, r4, #21760
	mov	r2, #0
	add	r1, r1, #28
	cmp	r3, #20
	sub	ip, fp, #180
	add	r0, r4, #14
	mov	lr, r2
	movge	r3, #20
	uxtb	r3, r3
	strb	r3, [r4, #13]
	b	.L184
.L225:
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
.L184:
	sxtb	r3, r3
	add	ip, ip, #4
	cmp	r3, r2
	add	r2, r2, #1
	add	r1, r1, #4
	add	r0, r0, #1
	ldrgt	r3, [ip, #-4]
	ldrle	r3, [fp, #-180]
	cmp	r2, #20
	str	r3, [r1, #-4]
	strb	lr, [r0, #-1]
	bne	.L225
	ldr	r5, [fp, #-636]
	mov	r3, #0
	ldr	r2, [fp, #-60]
	ldr	r1, [fp, #-640]
	ldr	lr, [fp, #-608]
	ldr	ip, [fp, #-344]
	str	r2, [r1, #1304]
	ldr	r1, [fp, #-336]
	ldr	r2, [fp, #-332]
	ldr	r0, [r5, #1188]
	str	lr, [r5, #1132]
	str	ip, [r5, #1136]
	str	r3, [r5, #1116]
	str	r0, [r5, #1124]
	str	r1, [r5, #1140]
	str	r2, [r5, #1144]
	ldr	r2, [r4, #64]
	ldr	lr, [fp, #-328]
	ldr	ip, [fp, #-324]
	str	r2, [r5, #1148]
	ldr	r1, [r4, #68]
	strb	r3, [r5, #1112]
	strb	r3, [r5, #1113]
	strb	r3, [r5, #1114]
	ldr	r3, [fp, #-320]
	str	r1, [r5, #1152]
	str	lr, [r5, #1156]
	str	ip, [r5, #1160]
	str	r3, [r5, #1164]
	ldr	r3, [r4, #40]
	cmp	r2, r3
	beq	.L185
	ldrsb	r3, [r4, #10]
.L186:
	str	r3, [r4, #48]
	ldr	r3, [fp, #-636]
	str	r2, [r4, #40]
	str	r1, [r4, #44]
	ldr	r3, [r3, #1252]
	rsb	r3, r0, r3
	str	r3, [r4, #52]
.L188:
	ldr	r3, [fp, #-604]
	mov	r0, #0
	ldr	r2, [fp, #-632]
	str	r3, [r2]
.L206:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L217:
	mov	r0, r5
	bl	VCTRL_GetChanCapLevel
	cmp	r0, #32
	bhi	.L153
	ldr	r2, .L226+20
	mov	r3, r0, asl #5
	sub	r3, r3, r0, asl #2
	ldr	r1, [r4, #64]
	add	lr, r2, r3
	ldr	ip, [r4, #68]
	ldr	r2, [r2, r3]
	ldr	r9, [lr, #4]
	mul	lr, ip, r1
	mul	r3, r9, r2
	cmp	r0, #25
	cmpne	lr, r3
	ble	.L210
	ldrsb	r3, [r4, #59]
	cmp	r3, #1
	bne	.L190
.L210:
	ldr	r0, [r6, r5, asl #2]
	b	.L155
.L218:
	stmia	sp, {r1, ip}
	mov	r0, #0
	ldr	r4, [r7, #68]
	ldr	r1, .L226+24
	blx	r4
	ldr	r3, .L226+28
	ldr	r4, [r3]
	cmp	r4, #0
	mvneq	r0, #0
	beq	.L206
	mov	r3, #0
	mov	r0, r5
	mov	r2, r3
	mov	r1, #102
	blx	r4
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L220:
	ldr	r3, [fp, #-316]
	mov	r2, #1
	strb	r3, [r4, #9]
	ldr	r3, [r6, r5, asl #2]
	str	r2, [r3, #1444]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L219:
	ldr	r3, [r0, #2860]
	bics	r2, r3, #2
	beq	.L158
	cmp	r3, #1
	moveq	r0, #0
	beq	.L206
	mov	r3, #0
	strb	r3, [r4, #9]
	ldr	r3, [r6, r5, asl #2]
	mov	r0, #31
	ldr	r4, [r7, #68]
	add	r3, r3, #225280
	ldr	r1, .L226+32
	ldr	r2, [r3, #2860]
	blx	r4
	mvn	r0, #0
	b	.L206
.L192:
	mvn	r9, #0
.L162:
	mov	r3, #0
	strb	r3, [r4, #9]
	ldr	ip, [r6, r5, asl #2]
	mov	r2, r9
	ldr	r4, [r7, #68]
	mov	r0, r3
	ldr	r1, .L226+36
	str	r3, [ip, #1444]
	blx	r4
	mvn	r0, #0
	b	.L206
.L223:
	ldr	r3, [r6, r5, asl #2]
	ldr	r3, [r3, #1404]
	cmp	r3, #1
	beq	.L172
	ldrsb	r0, [r4, #60]
	ldr	r3, [fp, #-316]
	add	r0, r0, #4
	cmp	r0, r3
	movge	r0, r3
	uxtb	r0, r0
	strb	r0, [r4, #10]
	b	.L173
.L153:
	ldrsb	r3, [r4, #59]
	cmp	r3, #1
	bne	.L189
	ldr	r1, [r4, #64]
	ldr	ip, [r4, #68]
	ldr	r0, [r6, r5, asl #2]
	mul	lr, ip, r1
	b	.L155
.L185:
	ldr	r3, [r4, #44]
	cmp	r1, r3
	ldrsb	r3, [r4, #10]
	bne	.L186
	ldr	ip, [r4, #48]
	cmp	r3, ip
	bne	.L186
	b	.L188
.L221:
	ldr	r3, [r7]
	blx	r3
	ldr	r3, [r10, r5, asl #2]
	add	r3, r3, #229376
	ldr	r1, [r3, #20]
	ldr	r2, [r3, #24]
	ldr	ip, [r3, #28]
	cmp	r1, r2
	rsb	lr, r1, r0
	rsbls	r0, r1, r2
	ldr	r2, .L226+40
	movhi	r0, r9
	cmp	r1, ip
	str	lr, [r3, #40]
	rsbls	r1, r1, ip
	str	r0, [r3, #32]
	movhi	r1, #0
	str	r1, [r3, #36]
	ldr	r3, [r2]
	cmp	lr, r3
	strhi	lr, [r2]
	b	.L166
.L215:
	ldr	r4, [r7, #68]
	movw	r2, #617
	ldr	r3, .L226+44
	mov	r0, #0
	ldr	r1, .L226+48
	blx	r4
	mvn	r0, #0
	b	.L206
.L189:
	mov	r2, r0
	ldr	r3, [r7, #68]
	mov	r0, r8
	ldr	r1, .L226+52
	blx	r3
.L156:
	mov	r3, #0
	mvn	r0, #0
	strb	r3, [r4, #9]
	b	.L206
.L190:
	str	r1, [sp, #4]
	mov	r3, r2
	str	ip, [sp, #8]
	mov	r2, r0
	str	r9, [sp]
	mov	r0, r8
	ldr	r5, [r7, #68]
	ldr	r1, .L226+56
	blx	r5
	b	.L156
.L222:
	mov	r2, #0
	str	r3, [sp]
	mov	r0, r2
	ldr	r4, [r1, #68]
	mov	r3, r8
	ldr	r1, .L226+60
	blx	r4
	mvn	r0, #0
	b	.L206
.L216:
	ldr	r5, [r7, #68]
	mov	r0, r4
	ldr	r3, .L226+64
	movw	r2, #618
	ldr	r1, .L226+48
	blx	r5
	mvn	r0, #0
	b	.L206
.L227:
	.align	2
.L226:
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
	.word	g_u32DFSMaxAllocTime
	.word	.LC0
	.word	.LC1
	.word	.LC9
	.word	.LC10
	.word	.LC15
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_PartitionFsMemory, .-FSP_PartitionFsMemory
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
	ble	.L232
	mvn	lr, #0
	mov	r3, r0
.L231:
	ldr	ip, [r2, #56]
	add	r2, r2, #64
	cmp	ip, lr
	movcc	r0, r3
	add	r3, r3, #1
	movcc	lr, ip
	cmp	r3, r1
	bne	.L231
	ldmfd	sp, {fp, sp, pc}
.L232:
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
	ldr	lr, .L247
	ldr	r2, [lr, r0, asl #2]
	cmp	r2, #0
	beq	.L245
	mov	r3, r0, asl #8
	add	r3, r3, r0, lsl #3
	add	r3, lr, r3
	add	r3, r3, #64
	ldrsh	r4, [r3, #2]
	cmn	r4, #1
	beq	.L242
	ldrh	r3, [r3, #4]
	cmp	r3, r4
	beq	.L242
	ldr	r6, [r2, #4]
	add	ip, r2, #16384
	ldr	r5, [r2, #52]
	cmp	r6, #1
	ldr	r2, [ip, #1252]
	ldr	r6, [ip, #1188]
	beq	.L246
.L242:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L246:
	and	r3, r3, #63
	cmp	r4, r3
	beq	.L242
	rsb	r6, r6, r2
	mov	r2, r0, asl #6
	add	r6, r6, r1
	add	r0, r2, r0, lsl #1
.L238:
	add	r2, r0, r3
	add	r3, r3, #1
	and	r3, r3, #63
	add	r2, lr, r2, lsl #2
	ldr	r2, [r2, #72]
	add	ip, r2, r5
	cmp	ip, r1
	bcc	.L237
	cmp	r2, r6
	bls	.L243
.L237:
	cmp	r4, r3
	bne	.L238
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L243:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L245:
	ldr	ip, .L247+4
	mov	r0, r2
	ldr	r3, .L247+8
	mov	r2, #1488
	ldr	r1, .L247+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L248:
	.align	2
.L247:
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
	bhi	.L305
	ldr	r4, .L315
	ldr	r0, [r4, r0, asl #2]
	cmp	r0, #0
	beq	.L306
	ldr	r7, .L315+4
	mov	r0, #3
	ldr	r3, [r7, #12]
	blx	r3
	ldr	r5, [r4, r8, asl #2]
	mov	r2, #0
	mov	r3, r5
.L255:
	ldrsb	r1, [r3, #88]
	cmp	r1, #0
	bne	.L253
	ldrsb	r0, [r3, #89]
	cmp	r0, #0
	beq	.L307
.L253:
	add	r2, r2, #1
	add	r3, r3, #544
	cmp	r2, #32
	bne	.L255
.L256:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r1, .L315+8
	blx	r3
	ldr	r3, [r7, #16]
	mov	r0, #3
	blx	r3
	mvn	r0, #0
.L297:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L307:
	mov	r10, r2, asl #5
	mov	r6, r2, asl #9
	add	r4, r10, r6
	add	r3, r5, r4
	add	r4, r4, #88
	add	ip, r3, #88
	adds	r4, r5, r4
	strb	r2, [ip, #3]
	strb	r0, [ip, #2]
	beq	.L256
	add	r1, r3, #608
	add	lr, r3, #616
	cmp	r9, #0
	str	r0, [r3, #608]
	str	r0, [r1, #4]
	str	r0, [r3, #616]
	str	r0, [lr, #4]
	beq	.L257
	ldrsb	r1, [r5, #10]
	cmp	r1, #0
	addgt	r3, r5, #17408
	addgt	r3, r3, #152
	ble	.L301
.L262:
	ldrsb	r2, [r3]
	cmp	r2, #0
	bne	.L261
	ldrsb	r2, [r3, #2]
	cmp	r2, #0
	beq	.L308
.L261:
	add	r0, r0, #1
	add	r3, r3, #64
	cmp	r0, r1
	bne	.L262
	add	r3, r10, r6
	add	r3, r5, r3
.L301:
	ldr	r9, [r3, #608]
.L259:
	cmp	r9, #0
	beq	.L309
.L263:
	add	r3, r10, r6
	add	r2, r5, #21504
	add	r3, r5, r3
	add	r2, r2, #152
	add	r0, r3, #616
	str	r2, [r3, #616]
	ldrsb	r2, [r5, #13]
	cmp	r2, #0
	ble	.L273
	ldrsb	r1, [r5, #14]
	cmp	r1, #0
	addne	r1, r5, #14
	movne	r3, #0
	bne	.L277
	b	.L310
.L280:
	ldrsb	r0, [r1, #1]!
	cmp	r0, #0
	beq	.L311
.L277:
	add	r3, r3, #1
	cmp	r3, r2
	bne	.L280
	add	r1, r5, #20480
	cmp	r2, #0
	ldr	ip, [r1, #1304]
	ble	.L282
.L278:
	add	r2, r2, #13
	add	r3, r5, #13
	add	r2, r5, r2
	mov	r0, #0
.L281:
	strb	r0, [r3, #1]!
	cmp	r3, r2
	bne	.L281
.L282:
	add	r2, r10, r6
	mov	lr, #0
	add	r2, r5, r2
	mov	r0, lr
	ldr	r3, [r7, #68]
	strb	lr, [r2, #92]
	ldr	lr, [r1, #1308]
	str	ip, [r2, #624]
	ldr	r1, .L315+12
	str	lr, [r2, #620]
	blx	r3
.L273:
	ldr	r3, .L315+16
	add	r9, r10, r6
	add	r9, r5, r9
	ldr	r2, [r3, #-3896]
	ldr	r1, [r9, #608]
	cmp	r2, #0
	str	r1, [r9, #612]
	beq	.L260
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
	beq	.L312
	mov	r3, r0
	sub	r1, fp, #72
	mov	r0, r8
	blx	ip
	cmp	r0, #0
	bne	.L284
	ldr	r8, [fp, #-72]
	cmp	r8, #0
	beq	.L313
	ldr	r3, [r9, #608]
	str	r8, [r3, #12]
	ldrsb	r3, [r9, #92]
	ldr	r2, [fp, #-56]
	add	r3, r3, #5440
	add	r3, r3, #6
	str	r2, [r9, #620]
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	b	.L260
.L257:
	add	r0, r5, #20480
	add	r2, r5, #17408
	add	r2, r2, #88
	str	r2, [r3, #608]
	str	r2, [r1, #4]
	mov	r1, #1
	str	r2, [r3, #616]
	ldr	r3, [r0, #1308]
	str	r3, [lr, #4]
	ldrb	r3, [r5, #13]	@ zero_extendqisi2
	strb	r1, [ip, #2]
	sub	r3, r3, #1
	strb	r3, [ip, #4]
.L260:
	add	r6, r10, r6
	mov	lr, #1
	add	r3, r5, r6
	add	r0, r6, #96
	add	r0, r5, r0
	add	r8, r3, #88
	ldr	r6, [r3, #612]
	mov	r1, #0
	strb	lr, [r3, #89]
	mov	r2, #504
	strb	lr, [r6, #2]
	str	lr, [r3, #604]
	ldr	r6, [r3, #608]
	ldr	lr, [r5, #36]
	str	lr, [r3, #600]
	str	lr, [r6, #56]
	ldr	lr, [r3, #612]
	ldr	r6, [r3, #600]
	str	r6, [lr, #56]
	ldr	lr, [r5, #36]
	add	lr, lr, #1
	str	lr, [r5, #36]
	add	r5, r3, #608
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
.L308:
	add	r3, r10, r6
	add	r0, r5, r0, lsl #6
	add	r3, r5, r3
	add	r9, r0, #17408
	add	r9, r9, #152
	str	r9, [r3, #608]
	b	.L259
.L311:
	add	ip, r3, #5440
	add	r0, r10, r6
	add	ip, ip, #6
	add	r0, r5, r0
	cmp	r3, r2
	add	r1, r5, #20480
	add	ip, r5, ip, lsl #2
	strb	r3, [r0, #92]
	ldr	r3, [ip, #4]
	str	r3, [r0, #620]
	ldr	ip, [r1, #1304]
	str	ip, [r0, #624]
	blt	.L273
	b	.L278
.L309:
	ldr	r3, [r7, #68]
	mov	r0, r9
	ldr	r2, .L315+20
	ldr	r1, .L315+24
	blx	r3
	ldrsb	r3, [r5, #10]
	cmp	r3, #0
	ble	.L268
	add	r3, r5, #17408
	str	r8, [fp, #-80]
	add	r3, r3, #152
	mov	r8, r4
	mov	r4, r3
.L267:
	ldrsb	r3, [r4, #2]
	mov	r0, #0
	ldrsb	r2, [r4], #64
	add	r9, r9, #1
	ldr	r1, .L315+28
	ldr	ip, [r7, #68]
	blx	ip
	ldrsb	r3, [r5, #10]
	cmp	r3, r9
	bgt	.L267
	mov	r4, r8
	ldr	r8, [fp, #-80]
.L268:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r1, .L315+32
	blx	r3
	ldrsb	r3, [r5, #9]
	ldr	r9, .L315+4
	cmp	r3, #0
	ble	.L314
	ldrsb	ip, [r5, #10]
	add	r3, r5, #17408
	add	r3, r3, #152
	cmp	ip, #0
	ble	.L269
	mov	lr, #0
	mvn	r0, #0
	mov	r2, lr
.L271:
	ldr	r1, [r3, #56]
	add	r3, r3, #64
	cmp	r1, r0
	movcc	lr, r2
	add	r2, r2, #1
	movcc	r0, r1
	cmp	ip, r2
	bne	.L271
	add	r3, r5, lr, lsl #6
	add	r3, r3, #17408
	add	r3, r3, #152
.L269:
	add	r2, r10, r6
	add	r2, r5, r2
	str	r3, [r2, #608]
	b	.L263
.L312:
	mov	r0, ip
	ldr	r3, [r7, #68]
	ldr	r1, .L315+36
	blx	r3
.L284:
	ldr	r3, [r7, #16]
	mov	r0, #3
	blx	r3
	ldr	r3, [r7, #68]
	ldr	r1, .L315+40
	mov	r0, #0
	blx	r3
	mvn	r0, #0
	b	.L297
.L305:
	ldr	ip, .L315+4
	movw	r2, #1550
	ldr	r3, .L315+44
	mov	r0, #0
	ldr	r1, .L315+48
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L297
.L310:
	add	r2, r5, #20480
	strb	r1, [r3, #92]
	ldr	r1, [r2, #1308]
	str	r1, [r0, #4]
	ldr	r2, [r2, #1304]
	str	r2, [r3, #624]
	b	.L273
.L306:
	ldr	ip, .L315+4
	movw	r2, #1551
	ldr	r3, .L315+52
	ldr	r1, .L315+48
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	b	.L297
.L313:
	ldr	r3, [r7, #16]
	mov	r0, #3
	blx	r3
	ldr	r3, [r7, #68]
	mov	r0, r8
	ldr	r1, .L315+56
	blx	r3
	mvn	r0, #0
	b	.L297
.L314:
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r2, .L315+20
	ldr	r1, .L315+60
	blx	r3
	ldr	r3, [r9, #16]
	mov	r0, #3
	blx	r3
	mvn	r0, #0
	b	.L297
.L316:
	.align	2
.L315:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC16
	.word	.LC21
	.word	.LANCHOR1
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
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #15
	bhi	.L324
	cmp	r1, #31
	bhi	.L325
	ldr	r3, .L327
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L326
	mov	r2, r1, asl #5
	mov	r1, r1, asl #9
	add	r3, r2, r1
	add	r3, r0, r3
	ldr	ip, [r3, #604]
	cmp	ip, #2
	ldmnefd	sp, {fp, sp, pc}
	ldrb	r3, [r3, #92]	@ zero_extendqisi2
	add	r1, r2, r1
	cmp	r3, #19
	sxtabls	r3, r0, r3
	add	r0, r0, r1
	movls	ip, #0
	strlsb	ip, [r3, #14]
	mov	r3, #0
	str	r3, [r0, #604]
	ldmfd	sp, {fp, sp, pc}
.L324:
	ldr	ip, .L327+4
	mov	r2, #1920
	ldr	r3, .L327+8
	mov	r0, #0
.L323:
	ldr	r1, .L327+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L325:
	ldr	ip, .L327+4
	movw	r2, #1921
	ldr	r3, .L327+16
	mov	r0, #0
	b	.L323
.L326:
	ldr	ip, .L327+4
	movw	r2, #1922
	ldr	r3, .L327+20
	b	.L323
.L328:
	.align	2
.L327:
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
	bhi	.L361
	cmp	r1, #31
	bhi	.L362
	ldr	ip, .L372
	ldr	r7, [ip, r0, asl #2]
	cmp	r7, #0
	beq	.L363
	mov	r8, r1, asl #5
	mov	r5, r1, asl #9
	add	r4, r8, r5
	uxtb	r9, r2
	add	r4, r7, r4
	ldrsb	r3, [r4, #90]
	strb	r9, [r4, #88]
	cmp	r3, #0
	ldmneib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, [r4, #608]
	cmp	r3, #0
	beq	.L335
	ldr	ip, [r3, #56]
	ldr	r1, [r4, #600]
	cmp	ip, r1
	beq	.L364
.L335:
	add	r3, r8, r5
	add	r3, r7, r3
	ldrb	r2, [r3, #92]	@ zero_extendqisi2
	cmp	r2, #19
	bhi	.L338
	cmp	r6, #1
	beq	.L365
	cmp	r6, #0
	bne	.L341
	ldr	r0, [r3, #604]
	cmp	r0, #2
	beq	.L366
.L348:
	add	r3, r8, r5
	add	r3, r7, r3
	ldr	r3, [r3, #612]
	cmp	r3, #0
	beq	.L352
	ldrsb	r2, [r3, #2]
	cmp	r2, #1
	moveq	r2, #0
	streqb	r2, [r3, #2]
.L352:
	add	r1, r8, r5
	add	r7, r7, r1
	str	r6, [r7, #608]
	ldmib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L361:
	ldr	ip, .L372+4
	movw	r2, #1954
	ldr	r3, .L372+8
	mov	r0, #0
.L360:
	ldr	r1, .L372+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L365:
	ldr	r1, [r3, #604]
	add	r3, r3, #600
	cmp	r1, #1
	beq	.L367
.L340:
	add	r3, r8, r5
	add	r3, r7, r3
	ldr	r2, [r3, #612]
	cmp	r2, #0
	beq	.L368
.L347:
	add	r3, r8, r5
	ldr	r0, [r2, #56]
	add	r3, r7, r3
	ldr	r1, [r3, #600]
	cmp	r6, #1
	cmpeq	r0, r1
	beq	.L369
.L344:
	cmp	r6, #0
	beq	.L352
	ldmib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L362:
	ldr	ip, .L372+4
	movw	r2, #1955
	ldr	r3, .L372+16
	mov	r0, #0
	b	.L360
.L338:
	ldr	r3, .L372+4
	sxtb	r2, r2
	ldr	r1, .L372+20
	mov	r0, #0
	ldr	r3, [r3, #68]
	blx	r3
	cmp	r6, #0
	beq	.L348
	b	.L340
.L364:
	ldrsb	r1, [r3]
	cmp	r2, r1
	beq	.L336
	ldr	r1, .L372+24
	ldr	ip, [r1, #-3896]
	cmp	ip, #0
	bne	.L370
.L336:
	strb	r9, [r3]
	b	.L335
.L367:
	sxtab	r2, r7, r2
	mov	r1, #2
	strb	r6, [r2, #14]
	str	r1, [r3, #4]
.L341:
	add	r3, r8, r5
	add	r3, r7, r3
	ldr	r2, [r3, #612]
	cmp	r2, #0
	bne	.L347
	b	.L344
.L370:
	ldr	r10, [r1, #-3880]
	ldr	r1, [r3, #12]
	cmp	r10, #0
	beq	.L371
	blx	r10
	ldr	r3, [r4, #608]
	b	.L336
.L366:
	sxtab	r2, r7, r2
	strb	r6, [r2, #14]
	str	r6, [r3, #620]
	str	r6, [r3, #604]
	b	.L348
.L363:
	ldr	ip, .L372+4
	mov	r0, r7
	ldr	r3, .L372+28
	movw	r2, #1956
	b	.L360
.L369:
	ldrsb	r1, [r2, #2]
	cmp	r1, #1
	moveq	r1, #2
	streqb	r1, [r2, #2]
	streqb	r1, [r3, #89]
	b	.L344
.L368:
	ldmib	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L371:
	ldr	r3, .L372+4
	mov	r0, r10
	ldr	r1, .L372+32
	ldr	r3, [r3, #68]
	blx	r3
	ldr	r3, [r4, #608]
	b	.L336
.L373:
	.align	2
.L372:
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
	bhi	.L380
	cmp	r1, #31
	bhi	.L381
	ldr	r3, .L383
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L382
	mov	r0, r1, asl #9
	add	r1, r0, r1, lsl #5
	add	r3, r3, r1
	ldrsb	r0, [r3, #88]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L380:
	ldr	ip, .L383+4
	movw	r2, #2075
	ldr	r3, .L383+8
.L379:
	ldr	r1, .L383+12
	mov	r0, #0
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L381:
	ldr	ip, .L383+4
	movw	r2, #2076
	ldr	r3, .L383+16
	b	.L379
.L382:
	ldr	ip, .L383+4
	mov	r0, r3
	movw	r2, #2077
	ldr	r3, .L383+20
	ldr	r1, .L383+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L384:
	.align	2
.L383:
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
	bhi	.L412
	cmp	r1, #31
	bhi	.L413
	ldr	r5, .L418
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L414
	ldr	r8, .L418+4
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
	add	r2, r3, #88
	ldrsb	r1, [r3, #90]
	cmp	r1, #0
	cmpeq	r10, #0
	bne	.L389
	ldr	r3, [r3, #612]
	cmp	r3, #0
	beq	.L389
	ldrsb	r2, [r2, #1]
	cmp	r2, #0
	beq	.L389
	ldr	r2, .L418+8
	ldr	r1, [r2, #-3896]
	cmp	r1, #0
	bne	.L415
.L389:
	add	r1, r7, r4
	cmp	r9, #0
	add	r1, r5, r1
	add	ip, r1, #88
	movne	r3, #0
	ldrsb	r0, [ip, #2]
	moveq	r3, #3
	strb	r3, [ip, #1]
	cmp	r0, #0
	bne	.L396
	add	lr, r1, #608
	ldr	r3, [lr, #4]
	cmp	r3, #0
	beq	.L396
	ldr	r3, [r3, #56]
	ldr	r2, [r1, #600]
	cmp	r3, r2
	bne	.L416
	cmp	r9, #0
	strneb	r0, [ip, #1]
	moveq	r3, #3
	ldrne	r3, [lr, #4]
	streqb	r3, [ip, #1]
	ldreq	r2, [lr, #4]
	strneb	r0, [r3, #2]
	strne	r0, [lr, #4]
	streqb	r3, [r2, #2]
.L396:
	ldr	r3, [r8, #16]
	mov	r0, #3
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L412:
	ldr	ip, .L418+4
	movw	r2, #2094
	ldr	r3, .L418+12
.L410:
	mov	r0, #0
.L411:
	ldr	r1, .L418+16
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L413:
	ldr	ip, .L418+4
	movw	r2, #2095
	ldr	r3, .L418+20
	b	.L410
.L416:
	ldr	r4, [r8, #68]
	ldr	r1, .L418+24
	blx	r4
	b	.L396
.L414:
	ldr	ip, .L418+4
	mov	r2, #2096
	ldr	r3, .L418+28
	b	.L411
.L415:
	ldr	r2, [r2, #-3884]
	ldr	r1, [r3, #12]
	cmp	r2, #0
	beq	.L417
	mov	r0, r6
	blx	r2
	b	.L389
.L417:
	mov	r0, r2
	ldr	r3, [r8, #68]
	ldr	r1, .L418+32
	blx	r3
	b	.L389
.L419:
	.align	2
.L418:
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
	bhi	.L431
	cmp	r1, #0
	beq	.L432
	ldr	r3, .L435
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r6, r0, #17408
	addne	r4, r0, #96
	addne	r6, r6, #96
	bne	.L426
	b	.L433
.L425:
	add	r4, r4, #544
	cmp	r4, r6
	beq	.L434
.L426:
	mov	r2, #0
	ldr	r1, [r4, #196]
	mov	r0, r5
	bl	FSP_SetRef
	mov	r1, r4
	mov	r0, r7
	bl	IsImageInVoQueue
	cmp	r0, #0
	beq	.L425
	ldr	r1, [r4, #196]
	mov	r2, #0
	mov	r0, r5
	add	r4, r4, #544
	bl	FSP_SetDisplay
	cmp	r4, r6
	bne	.L426
.L434:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L431:
	ldr	ip, .L435+4
	mov	r2, #552
	ldr	r3, .L435+8
	mov	r0, #0
	ldr	r1, .L435+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L433:
	ldr	ip, .L435+4
	movw	r2, #554
	ldr	r3, .L435+16
	ldr	r1, .L435+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L432:
	ldr	ip, .L435+4
	mov	r0, r1
	ldr	r3, .L435+20
	movw	r2, #553
	ldr	r1, .L435+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L436:
	.align	2
.L435:
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
	ldr	r3, .L441
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L440
	mov	r0, r1, asl #9
	add	r1, r0, r1, lsl #5
	add	r3, r3, r1
	ldrsb	r0, [r3, #89]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L440:
	ldr	ip, .L441+4
	mov	r0, r3
	movw	r2, #2163
	ldr	r3, .L441+8
	ldr	r1, .L441+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L442:
	.align	2
.L441:
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
	bhi	.L451
	ldr	ip, .L454
	ldr	r0, [ip, r0, asl #2]
	cmp	r0, #0
	beq	.L452
	cmp	r1, #0
	bne	.L447
	ldrsb	ip, [r0, #10]
	cmp	ip, r2
	ble	.L450
	add	r2, r0, r2, lsl #6
	movw	ip, #17568
	mov	r0, r1
	str	r3, [r2, ip]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L447:
	cmp	r1, #1
	beq	.L453
.L450:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L453:
	ldrsb	r1, [r0, #11]
	cmp	r2, r1
	bge	.L450
	add	r2, r0, r2, lsl #6
	movw	r1, #19616
	mov	r0, #0
	str	r3, [r2, r1]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L451:
	ldr	ip, .L454+4
	movw	r2, #2179
	ldr	r3, .L454+8
	mov	r0, #0
	ldr	r1, .L454+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L452:
	ldr	ip, .L454+4
	movw	r2, #2180
	ldr	r3, .L454+16
	ldr	r1, .L454+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L455:
	.align	2
.L454:
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
	bhi	.L464
	ldr	r3, .L467
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L465
	cmp	r1, #0
	bne	.L460
	ldrsb	r3, [r0, #10]
	cmp	r3, r2
	ble	.L463
	add	r0, r0, r2, lsl #6
	movw	r3, #17568
	ldr	r0, [r0, r3]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L460:
	cmp	r1, #1
	beq	.L466
.L463:
	mov	r0, #2
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L464:
	ldr	ip, .L467+4
	movw	r2, #2220
	ldr	r3, .L467+8
	mov	r0, #0
	ldr	r1, .L467+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L465:
	ldr	ip, .L467+4
	movw	r2, #2221
	ldr	r3, .L467+16
	ldr	r1, .L467+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L466:
	ldrsb	r3, [r0, #11]
	cmp	r2, r3
	bge	.L463
	add	r0, r0, r2, lsl #6
	movw	r3, #19616
	ldr	r0, [r0, r3]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L468:
	.align	2
.L467:
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
	ldr	r6, .L479
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r2, #0
	bl	FSP_SetRef
	ldr	r2, [r6, r4, asl #2]
	mov	r3, r5, asl #9
	add	r3, r3, r5, lsl #5
	add	r3, r2, r3
	ldrsb	r3, [r3, #89]
	cmp	r3, #3
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r5
	mov	r0, r4
	mov	r2, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	FSP_SetDisplay
.L480:
	.align	2
.L479:
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
	bhi	.L484
	ldr	r3, .L485
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L484
	mov	r2, r1, asl #9
	add	r0, r2, r1, lsl #5
	add	r0, r0, #88
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L484:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L486:
	.align	2
.L485:
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
	bhi	.L490
	ldr	r3, .L491
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L490
	mov	r2, r1, asl #9
	add	r0, r2, r1, lsl #5
	add	r0, r0, #96
	add	r0, r3, r0
	ldmfd	sp, {fp, sp, pc}
.L490:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L492:
	.align	2
.L491:
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
	bhi	.L495
	ldr	r3, .L497
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, r1, asl #9
	addne	r1, r3, r1, lsl #5
	addne	r0, r0, r1
	ldrne	r0, [r0, #608]
	ldmfd	sp, {fp, sp, pc}
.L495:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L498:
	.align	2
.L497:
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
	bhi	.L501
	ldr	r3, .L503
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, r1, asl #9
	addne	r1, r3, r1, lsl #5
	addne	r0, r0, r1
	ldrne	r0, [r0, #612]
	ldmfd	sp, {fp, sp, pc}
.L501:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L504:
	.align	2
.L503:
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
	bhi	.L507
	ldr	r3, .L509
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, r1, asl #9
	addne	r1, r3, r1, lsl #5
	addne	r0, r0, r1
	ldrne	r0, [r0, #620]
	ldmfd	sp, {fp, sp, pc}
.L507:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L510:
	.align	2
.L509:
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
	bhi	.L522
	cmp	r2, #0
	beq	.L523
	cmp	r1, #0
	beq	.L524
	ldr	ip, .L526
	ldr	lr, [ip, r0, asl #2]
	cmp	lr, #0
	beq	.L525
	mov	lr, #0
	str	lr, [r1]
	ldr	r4, [ip, r0, asl #2]
	ldrsb	r4, [r4, #10]
	cmp	r4, lr
	str	r4, [r1]
	ldr	ip, [ip, r0, asl #2]
	add	ip, ip, #17408
	add	ip, ip, #152
	ldmlefd	sp, {r4, fp, sp, pc}
	sub	r2, r2, #4
	sub	r3, r3, #4
.L518:
	ldr	r0, [ip, #12]
	add	lr, lr, #1
	add	ip, ip, #64
	str	r0, [r2, #4]!
	ldr	r0, [ip, #-48]
	str	r0, [r3, #4]!
	ldr	r4, [r1]
	cmp	r4, lr
	bgt	.L518
	ldmfd	sp, {r4, fp, sp, pc}
.L522:
	ldr	ip, .L526+4
	movw	r2, #2379
	ldr	r3, .L526+8
	mov	r0, #0
.L521:
	ldr	r1, .L526+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	bx	ip
.L523:
	mov	r0, r2
	ldr	ip, .L526+4
	ldr	r3, .L526+16
	movw	r2, #2380
	b	.L521
.L524:
	ldr	ip, .L526+4
	mov	r0, r1
	ldr	r3, .L526+20
	movw	r2, #2381
	b	.L521
.L525:
	ldr	ip, .L526+4
	mov	r0, lr
	ldr	r3, .L526+24
	movw	r2, #2382
	b	.L521
.L527:
	.align	2
.L526:
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
	bhi	.L539
	cmp	r2, #0
	beq	.L540
	cmp	r1, #0
	beq	.L541
	ldr	ip, .L543
	ldr	r3, [ip, r0, asl #2]
	cmp	r3, #0
	beq	.L542
	mov	r3, #0
	str	r3, [r1]
	ldr	ip, [ip, r0, asl #2]
	ldrsb	r0, [ip, #13]
	str	r0, [r1]
	ldrsb	r1, [ip, #13]
	cmp	r1, r3
	ldmlefd	sp, {fp, sp, pc}
	add	r1, ip, #21760
	sub	r2, r2, #4
	add	r1, r1, #24
.L535:
	ldr	r0, [r1, #4]!
	add	r3, r3, #1
	str	r0, [r2, #4]!
	ldrsb	r0, [ip, #13]
	cmp	r0, r3
	bgt	.L535
	ldmfd	sp, {fp, sp, pc}
.L539:
	ldr	ip, .L543+4
	movw	r2, #2424
	ldr	r3, .L543+8
	mov	r0, #0
.L538:
	ldr	r1, .L543+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L540:
	mov	r0, r2
	ldr	ip, .L543+4
	ldr	r3, .L543+16
	movw	r2, #2425
	b	.L538
.L541:
	ldr	ip, .L543+4
	mov	r0, r1
	ldr	r3, .L543+20
	movw	r2, #2426
	b	.L538
.L542:
	mov	r0, r3
	ldr	ip, .L543+4
	ldr	r3, .L543+24
	movw	r2, #2427
	b	.L538
.L544:
	.align	2
.L543:
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
	ldr	r3, .L548
	mov	ip, r1
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L547
	ldrb	lr, [r3, #10]	@ zero_extendqisi2
	add	r4, r3, #16384
	mov	r0, r1
	ldr	r5, .L548+4
	add	r1, r3, #17408
	mov	r2, #2048
	strb	lr, [ip, #1]
	add	r1, r1, #152
	ldr	lr, [r4, #1252]
	ldr	r4, [r4, #1188]
	rsb	lr, r4, lr
	str	lr, [ip, #2056]
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
.L547:
	ldr	ip, .L548+4
	mov	r0, r3
	movw	r2, #2449
	ldr	r3, .L548+8
	ldr	r1, .L548+12
	ldr	ip, [ip, #68]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	ip
.L549:
	.align	2
.L548:
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
	bhi	.L561
	ldr	r3, .L563
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, r0
	movne	r0, #0
	beq	.L562
.L555:
	ldr	r2, [r3, #608]
	add	r3, r3, #544
	cmp	r2, #0
	beq	.L554
	ldr	r2, [r2, #12]
	cmp	r2, r1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
.L554:
	add	r0, r0, #1
	cmp	r0, #32
	bne	.L555
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L561:
	ldr	ip, .L563+4
	movw	r2, #2478
	ldr	r3, .L563+8
	mov	r0, #0
	ldr	r1, .L563+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L562:
	ldr	ip, .L563+4
	movw	r2, #2479
	ldr	r3, .L563+16
	ldr	r1, .L563+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L564:
	.align	2
.L563:
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
	bhi	.L597
	ldr	r3, .L600
	ldr	r9, [r3, r0, asl #2]
	cmp	r9, #0
	beq	.L598
	ldr	r7, .L600+4
	mov	r0, #0
	ldr	r1, .L600+8
	mov	r5, r9
	mov	r6, #1
	ldr	r3, [r7, #68]
	blx	r3
	ldr	r4, [r7, #68]
	ldr	r3, [r9, #4]
	mov	r0, #0
	ldr	r2, .L600+12
	ldr	r1, .L600+16
	blx	r4
	ldr	r4, [r7, #68]
	ldr	r3, [r9, #64]
	mov	r0, #0
	ldr	r2, .L600+20
	ldr	r1, .L600+16
	blx	r4
	ldr	r4, [r7, #68]
	ldr	r3, [r9, #68]
	mov	r0, #0
	ldr	r2, .L600+24
	ldr	r1, .L600+16
	blx	r4
	ldr	r4, [r7, #68]
	ldr	r3, [r9, #80]
	mov	r0, #0
	ldr	r2, .L600+28
	ldr	r1, .L600+16
	blx	r4
	ldr	r4, [r7, #68]
	ldr	r3, [r9, #84]
	mov	r0, #0
	ldr	r2, .L600+32
	ldr	r1, .L600+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #60]
	mov	r0, #0
	ldr	r2, .L600+36
	ldr	r1, .L600+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #62]
	mov	r0, #0
	ldr	r2, .L600+40
	ldr	r1, .L600+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #63]
	mov	r0, #0
	ldr	r2, .L600+44
	ldr	r1, .L600+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #10]
	mov	r0, #0
	ldr	r2, .L600+48
	ldr	r1, .L600+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #11]
	mov	r0, #0
	ldr	r2, .L600+52
	ldr	r1, .L600+16
	blx	r4
	ldr	r4, [r7, #68]
	ldrsb	r3, [r9, #13]
	mov	r0, #0
	ldr	r2, .L600+56
	ldr	r1, .L600+16
	blx	r4
	ldr	r3, [r7, #68]
	mov	r2, #32
	ldr	r1, .L600+60
	mov	r0, #0
	mov	r4, #0
	blx	r3
	b	.L568
.L570:
	ldr	r8, [r7, #68]
	mov	r0, #0
	ldrsb	r3, [r5, #89]
	ldrsb	r2, [r5, #88]
	ldr	r1, .L600+64
	blx	r8
	cmp	r6, #31
	bgt	.L599
.L571:
	add	r4, r4, #1
	add	r6, r6, #1
	add	r5, r5, #544
.L568:
	cmp	r4, #0
	ldr	r10, .L600+4
	beq	.L569
	ands	r0, r4, #7
	bne	.L570
	ldr	r3, [r7, #68]
	ldr	r1, .L600+68
	blx	r3
	b	.L570
.L599:
	ldr	r3, [r10, #68]
	mov	r0, #0
	ldrsb	r2, [r9, #10]
	ldr	r1, .L600+72
	blx	r3
	ldrsb	r3, [r9, #10]
	cmp	r3, #0
	addgt	r5, r9, #17408
	addgt	r5, r5, #152
	movgt	r4, #0
	ble	.L578
.L575:
	ldrsb	r3, [r5, #2]
	mov	r0, #0
	ldrsb	r2, [r5]
	add	r4, r4, #1
	ldr	r6, [r7, #68]
	add	r5, r5, #64
	ldr	r1, .L600+64
	blx	r6
	ldrsb	r3, [r9, #10]
	cmp	r3, r4
	ble	.L578
	cmp	r4, #0
	beq	.L575
	ands	r0, r4, #7
	bne	.L575
	ldr	r3, [r10, #68]
	ldr	r1, .L600+68
	blx	r3
	b	.L575
.L578:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldrsb	r2, [r9, #11]
	ldr	r1, .L600+76
	blx	r3
	ldrsb	r3, [r9, #11]
	cmp	r3, #0
	ble	.L574
	add	r5, r9, #19456
	ldr	r8, .L600+4
	add	r5, r5, #152
	mov	r4, #0
.L581:
	ldrsb	r3, [r5, #2]
	mov	r0, #0
	ldrsb	r2, [r5]
	add	r4, r4, #1
	ldr	r6, [r7, #68]
	add	r5, r5, #64
	ldr	r1, .L600+64
	blx	r6
	ldrsb	r3, [r9, #11]
	cmp	r3, r4
	ble	.L574
	cmp	r4, #0
	beq	.L581
	ands	r0, r4, #7
	bne	.L581
	ldr	r3, [r8, #68]
	ldr	r1, .L600+68
	blx	r3
	b	.L581
.L574:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldrsb	r2, [r9, #13]
	ldr	r1, .L600+80
	blx	r3
	ldrsb	r3, [r9, #13]
	cmp	r3, #0
	addgt	r5, r9, #13
	movgt	r4, #0
	ldrgt	r6, .L600+4
	ble	.L580
.L584:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldrsb	r2, [r5, #1]!
	add	r4, r4, #1
	ldr	r1, .L600+84
	blx	r3
	ldrsb	r3, [r9, #13]
	cmp	r3, r4
	ble	.L580
	cmp	r4, #0
	beq	.L584
	ands	r0, r4, #15
	bne	.L584
	ldr	r3, [r6, #68]
	ldr	r1, .L600+68
	blx	r3
	b	.L584
.L580:
	ldr	r3, [r7, #68]
	mov	r0, #0
	ldr	r1, .L600+88
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	r3
.L597:
	ldr	ip, .L600+4
	movw	r2, #2510
	ldr	r3, .L600+92
	mov	r0, #0
.L596:
	ldr	r1, .L600+96
	ldr	ip, [ip, #68]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	bx	ip
.L598:
	ldr	ip, .L600+4
	mov	r0, r9
	ldr	r3, .L600+100
	movw	r2, #2511
	b	.L596
.L569:
	ldr	r8, [r7, #68]
	mov	r0, r4
	ldrsb	r3, [r5, #89]
	ldrsb	r2, [r5, #88]
	ldr	r1, .L600+64
	blx	r8
	b	.L571
.L601:
	.align	2
.L600:
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
	ldr	r3, .L613
	mov	r5, r0
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L611
	ldrsb	r4, [r3, #10]
	cmp	r4, #0
	ble	.L605
	add	r3, r3, #17408
	mov	r2, #0
	add	r3, r3, #152
.L608:
	ldrsb	r1, [r3]
	cmp	r1, #0
	bne	.L606
	ldrsb	r1, [r3, #2]
	cmp	r1, #0
	beq	.L607
.L606:
	add	r2, r2, #1
	add	r3, r3, #64
	cmp	r4, r2
	bne	.L608
.L605:
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
	bgt	.L612
.L609:
	mov	r0, #0
.L604:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L607:
	cmp	r4, r2
	bgt	.L609
	b	.L605
.L612:
	ldr	r1, .L613+4
	stmia	sp, {r0, r4}
	mov	r0, r6
	ldr	r4, [r1, #68]
	ldr	r1, .L613+8
	blx	r4
	mov	r0, r5
	bl	FSP_PrintContext
	mov	r0, #1
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L611:
	ldr	r3, .L613+4
	mov	r0, #1
	ldr	r1, .L613+12
	ldr	r3, [r3, #68]
	blx	r3
	mvn	r0, #0
	b	.L604
.L614:
	.align	2
.L613:
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
	bhi	.L633
	ldr	r3, .L637
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L634
	ldr	r3, .L637+4
	ldr	r2, [r3, #-3896]
	cmp	r2, #0
	beq	.L622
	ldr	r5, [r3, #-3892]
	cmp	r5, #0
	beq	.L635
	blx	r5
	cmp	r0, #0
	bne	.L636
.L622:
	ldrb	r0, [r4, #10]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L629
	sxtb	r0, r0
	cmp	r0, #0
	ble	.L623
	add	r3, r4, #17408
	mov	r2, #0
	add	r3, r3, #152
.L626:
	ldrsb	r1, [r3]
	cmp	r1, #0
	bne	.L624
	ldrsb	r1, [r3, #2]
	cmp	r1, #0
	beq	.L625
.L624:
	add	r2, r2, #1
	add	r3, r3, #64
	cmp	r2, r0
	bne	.L626
.L623:
	mov	r0, r6
	bl	FSP_IsFsLeak
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L625:
	cmp	r0, r2
	ble	.L623
.L629:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L636:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L635:
	ldr	r3, .L637+8
	mov	r0, r5
	ldr	r1, .L637+12
	ldr	r3, [r3, #68]
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L633:
	ldr	ip, .L637+8
	movw	r2, #1252
	ldr	r3, .L637+16
	mov	r0, #0
	ldr	r1, .L637+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L634:
	ldr	ip, .L637+8
	mov	r0, r4
	ldr	r3, .L637+24
	movw	r2, #1253
	ldr	r1, .L637+20
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L638:
	.align	2
.L637:
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
	ldr	ip, .L653
	ldr	r2, [ip, r0, asl #2]
	cmp	r2, #0
	beq	.L648
	mov	r3, r0, asl #8
	add	r3, r3, r0, lsl #3
	add	r3, ip, r3
	add	r3, r3, #64
	ldrsh	lr, [r3, #2]
	cmn	lr, #1
	beq	.L648
	ldrh	r3, [r3, #4]
	cmp	r3, lr
	beq	.L648
	ldr	r2, [r2, #4]
	cmp	r2, #1
	beq	.L652
.L648:
	mov	r0, #0
	ldmfd	sp, {r4, fp, sp, pc}
.L652:
	and	r3, r3, #63
	cmp	lr, r3
	beq	.L648
	mov	r4, r0, asl #6
	add	r0, r4, r0, lsl #1
	add	r4, r0, r3
	add	r4, ip, r4, lsl #2
	ldr	r4, [r4, #72]
	cmp	r4, r1
	bne	.L642
	b	.L650
.L643:
	ldr	r2, [r2, #72]
	cmp	r2, r1
	beq	.L650
.L642:
	add	r3, r3, #1
	and	r3, r3, #63
	add	r2, r0, r3
	cmp	lr, r3
	add	r2, ip, r2, lsl #2
	bne	.L643
	b	.L648
.L650:
	mov	r0, #1
	ldmfd	sp, {r4, fp, sp, pc}
.L654:
	.align	2
.L653:
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
	ldr	r3, .L663
	ldr	ip, [r3, r0, asl #2]
	add	r3, ip, #16896
	ldrsb	r3, [r3, #57]
	cmp	r3, #0
	beq	.L660
	add	r3, ip, #16384
	mov	r2, #30
	add	r3, r3, #25
	b	.L659
.L657:
	subs	r2, r2, #1
	bcc	.L662
.L659:
	ldrsb	r1, [r3]
	sub	r3, r3, #544
	cmp	r1, #0
	bne	.L657
.L658:
	mov	r3, r2, asl #9
	mov	r0, r2
	add	r2, r3, r2, lsl #5
	mov	r3, #0
	add	ip, ip, r2
	str	r3, [ip, #608]
	str	r3, [ip, #612]
	ldmfd	sp, {fp, sp, pc}
.L662:
	mov	r2, #0
	b	.L658
.L660:
	mov	r2, #31
	b	.L658
.L664:
	.align	2
.L663:
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
	ldr	ip, .L667
	movw	r2, #2685
	ldr	r3, .L667+4
	mov	r0, #0
	ldr	r1, .L667+8
	ldr	ip, [ip, #68]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L668:
	.align	2
.L667:
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
	bhi	.L673
	ldr	r3, .L675
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L674
	ldr	r0, [r0, #4]
	subs	r0, r0, #1
	mvnne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L673:
	ldr	ip, .L675+4
	movw	r2, #2716
	ldr	r3, .L675+8
	mov	r0, #0
	ldr	r1, .L675+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L674:
	ldr	ip, .L675+4
	movw	r2, #2717
	ldr	r3, .L675+16
	ldr	r1, .L675+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L676:
	.align	2
.L675:
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
	bhi	.L681
	ldr	r3, .L683
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L682
	ldrsb	r0, [r0, #9]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L681:
	ldr	ip, .L683+4
	movw	r2, #2734
	ldr	r3, .L683+8
	mov	r0, #0
	ldr	r1, .L683+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L682:
	ldr	ip, .L683+4
	movw	r2, #2735
	ldr	r3, .L683+16
	ldr	r1, .L683+12
	ldr	r4, [ip, #68]
	blx	r4
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L684:
	.align	2
.L683:
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
	.type	__func__.13347, %object
	.size	__func__.13347, 15
__func__.13347:
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
